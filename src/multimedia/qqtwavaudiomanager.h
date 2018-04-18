#ifndef QQTWAVAUDIOMANAGER_H
#define QQTWAVAUDIOMANAGER_H

#include <QObject>
#include <qqtcore.h>
#include <qqt-local.h>

#include <QMimeType>
#include <QMimeData>
#include <QMimeDatabase>

#include <QSound>
#include <QSoundEffect>

#include <qqtaudiomanager.h>

//设计思路：QQtWavAudioInput和QQtWavAudioOutput两边都是内存和wav文件，为内存服务。

/**
 * @brief The QQtWavAudioInput class
 * QQtWavAudioInput具备QAudioInput的能力，可以把wav文件的音频帧，通过readyRead输出。
 * 每次/10ms一帧，通过QIODevice readyRead发射给用户。
 * 升级目标：QQtAudioInput里支持的设备比较广泛，文件类型比较多。
 *
 * 原理，设置Sourcefile，返回QIODevice，进行读取。一次加载，逐渐读取。
 *
 * 不要使用大文件。
 * Qt 中有一个 QBuffer 类，可以将 QByteArray 包装成一个 QIODevice。QMemIODevice = QBuffer
 * 如果来的是个QByteArray，那么，用QBuffer封装，
 * 在 open 函数中调用 QIODevice::open(mode)
 * 要解析wav，用自定义程序，还是用开源Library（libsndfile）？自定义程序
 * 要播放wav，是用wav的音频格式来设定输出设备，还是用个输出设备支持的音频格式，wav里选取进行使用？使用wav的。
 *
 * 尝试用QAudioDecoder，解码器不支持x-wav，defaultServiceProvider::requestService(): no service found for - "org.qt-project.qt.audiodecode"
 * 为什么QSoundEffect支持那么多wav格式？("audio/x-wav", "audio/wav", "audio/wave", "audio/x-pn-wav")
 * QAudioDecoder保存了一个提交，#5643241
 * QWavAudioEffect保存了一个提交，#5f43622
 */
class QQTSHARED_EXPORT QQtWavAudioInput : public QObject
{
    Q_OBJECT

public:
    explicit QQtWavAudioInput ( QObject* parent = nullptr );
    //自动解析格式，和文件大小
    QIODevice* setSourceFile ( const QString& localFile );
    QString sourceFile() { return mSourceFile; }

    //读取用。这个是个内部公用的，并不是临时的。碰巧了。
    QIODevice* device() { return &mBytesBuffer; }

    //设置读文件的时钟快慢（硬盘快，时钟快，每次读的少；硬盘慢，时钟慢，每次读的多）
    //采样间隔 10-100ms default: macOS SSD 20 ms
    //windows 机械硬盘 100ms, windows 机械硬盘 is slower than macOS SSD.
    int timerInterval() const { return mTimerInterval; }
    void setTimerInterval ( int millSecond = 20 );
    //可以频繁开启，tip：用完一定要关闭，系统会自动关闭。
    //已经检查测试，没有文件设备漏开关问题。
    void start();
    void stop();

    //每次修改SourceFile，这些都会改变。在不改变SourceFile的时候是内部使用的值。
    const QAudioFormat& format() { return mFormat; }
    int fileTotalSize();
    int fileHeaderSize();
    int fileDataSize();
    int fileTailSize();

signals:

public slots:

private slots:
    void slotTimeout();

private:
    QString mSourceFile;
    //用于保存文件全部Bytes
    QByteArray mFileBytes;
    //用于和Buffer联系，给用户提供每次读取的帧。
    QByteArray mBytes;
    QBuffer mBytesBuffer;

    //每次设置新Source，会改变这些值。
    QAudioFormat mFormat;
    int mFileDataSize;
    int mFileHeaderSize;
    int mFileTailSize;
    int mFileTotalSize;
    //这三个不准公开出来啊。
    int mSampleRate;
    int mSampleSize;
    int mChannelCount;

    QTimer* mTimer;
    int mTimerInterval;

public:
protected:
    bool anlysisWavFileHeader_C ( QString localFile );

public:
protected:
    // 解析wav文件的头信息;
    bool anlysisWavFileHeader ( QString fileName );
};

class QQTSHARED_EXPORT QQtWavAudioOutput : public QObject
{
    Q_OBJECT

public:
    explicit QQtWavAudioOutput ( QObject* parent = nullptr );

    QIODevice* setSourceFile ( const QString& localFile );
    QString sourceFile() { return mSourceFile; }

    //写入用
    QIODevice* device() { return &mBytesBuffer; }

    //用户务必设置format，默认值为2 16 44100
    QAudioFormat& format();

    void start();

    void stop();

protected:
    bool addWavHeader ( QIODevice& outputDevice, int& headerSize );
    bool addWavTail ( QIODevice& outputDevice );

private:
    QString mSourceFile;
    QAudioFormat mFormat;

    QBuffer mBytesBuffer;
    QByteArray mFileBytes;
};

class QQTSHARED_EXPORT QQtWavAudioManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtWavAudioManager ( QObject* parent = nullptr );

    ~QQtWavAudioManager();

    //设置输入或者输出wav文件
    void setInputSourceFile ( const QString& localFile );
    QString inputSourceFile();
    void setOutputSourceFile ( const QString& localFile );
    QString outputSourceFile();

    //获取输入文件的音频流格式
    const QAudioFormat& inputAudioFormat();
    //获取输出音频流的音频格式，可以设置，输出保存的时候使用。
    QAudioFormat& outputAudioFormat();

    //每次修改SourceFile，这些都会改变。
    int inputFileTotalSize();
    int inputFileHeaderSize();
    int inputFileDataSize();
    int inputFileTailSize();


    QQtWavAudioInput* inputManager();
    //如果输入，从这里读取帧
    QIODevice* inputDevice();

    QQtWavAudioOutput* outputManager();
    //如果输出，从这里写入帧，提前设置好格式哦...
    QIODevice* outputDevice();

    void startInput();
    void stopInput();

    void startOutput();
    void stopOutput();

    //这两个是方便函数，一般都用这几个进行读写，不使用上边的。
    QByteArray readAll();
    QByteArray read ( qint64 maxlen );
    void write ( const QByteArray& bytes );

signals:
    void readyRead();
public slots:

private:

    QQtWavAudioInput* mInputManager;
    QQtWavAudioOutput* mOutputManager;

    QIODevice* mInputDevice;
    QIODevice* mOutputDevice;

    //这三个不准公开出来啊。
    int mSampleRate;
    int mSampleSize;
    int mChannelCount;
};

#endif // QQTWAVAUDIOMANAGER_H
