#ifndef QQTAUDIOEFFECT_H
#define QQTAUDIOEFFECT_H

#include <qqtaudiomanager.h>
#include <qqtcore.h>
#include <qqt-local.h>

#include <QMimeType>
#include <QMimeData>
#include <QMimeDatabase>

#include <QSound>
#include <QSoundEffect>

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
    QIODevice* setSourceFile ( QString localFile );

    //采样间隔 10-100ms default:20
    int timerInterval() const { return mTimerInterval; }
    void setTimerInterval ( int millSecond = 20 );
    //可以频繁开启，tip：用完一定要关闭，系统会自动关闭。
    //已经检查测试，没有文件设备漏开关问题。
    void start();
    void stop();

    const QAudioFormat& format() { return mFormat; }
    //每次修改SourceFile，这些都会改变。在不改变SourceFile的时候是内部使用的值。
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

/*
 * QQtWavSoundEffect = QSoundEffect + QSound +...
 * QQtWavSoundEffect支持从wav获取声音并输出，弥补QSoundEffect（+他的高级点的封装QSound）不能支持选择设备的缺失。
 *
 */
class QQTSHARED_EXPORT QQtWavSoundEffect : public QObject
{
    Q_OBJECT

public:
    //这样做的目的，在于使用一个实例去播放音效。
    //如果是个临时变量，函数执行返回了，但是还没播放完，甚至还没来得及开始呢，这时，播放不出来的。
    static QQtWavSoundEffect* Instance ( QObject* parent = nullptr );

    explicit QQtWavSoundEffect ( QObject* parent = nullptr );

    //设置设备以后，不需要每次都设置
    //更换设备不会引发播放更改，只会更改内部设备记录。调用play才会导致播放更改。
    void setOutputDevice ( const QAudioDeviceInfo& output = QAudioDeviceInfo() );

    void useDefaultOutputDevice();

    void useCustomOutputDevice ( const QAudioDeviceInfo& output );

    void play ( QString localFile );

    void stop();

    //设置声音以后，不需要每次都要设置。
    void setVolume ( qreal volume );

    //设置loop会保存下来，不需要每次设置。
    int loops() const;
    int loopsRemaining() const;
    void setLoops ( int loops );

private slots:
    void readyRead();

private:
    //不需要额外初始化的地方
    static QQtWavSoundEffect* msInstance;

    QQtWavAudioInput mWavInput;
    QIODevice* mIOInput;
    QQtAudioManager manager;
    QString mSourceFile;
    int mDataSize;
    //volume会被记住。
    qreal mVolume;
    int mLoops;
    int mLooping;
};

//在使用QQtWavSound等函数之前，调用类的instance函数，+parent 初始化一下实例。
//=QSound::play()
QQtWavSoundEffect* QQtWavSound ( QString localFile = "" );

/**
 * @brief The QQtAudioEffect class
 * QSound、QSoundEffect是不能指定输出设备的。
 * 用于播放音效文件，接受指定输出设备。
 *
 * 请不要用来播放大文件，会全部读入内存，然后逐渐删除。
 * 尝试用QQt的，需要切掉wav文件的44头。
 * 现在更新为用QQt的，QQtAudioEffect目标支持多种格式的音效文件。
 */
class QQTSHARED_EXPORT QQtAudioEffect : public QQtAudioManager
{
    Q_OBJECT
public:
    explicit QQtAudioEffect ( QObject* parent = nullptr ) : QQtAudioManager ( parent ) {

    }

    void play ( QString localFile ) {
        QByteArray bytes;
        QFile file ( localFile );
        file.open ( QFile::ReadOnly );
        bytes = file.readAll();
        file.close();
        QByteArray tmp ( 44, 'c' );
        bytes >> tmp;

        outputAudioFormat() = defaultOutputDevice().preferredFormat();
        startDefaultOutput();
        write ( bytes );
        return;
    }

    //需要用户设置输出设备
    void customPlay ( QString localFile ) {

        QByteArray bytes;
        QFile f ( localFile );
        f.open ( QFile::ReadOnly );
        bytes = f.readAll();
        f.close();

        if ( !outputAudioFormat().isValid()
             || !outputDeviceInfo().isNull() ) {
            outputAudioFormat() = defaultOutputDevice().preferredFormat();
            outputDeviceInfo() = defaultOutputDevice();
        }

        startOutput();
        write ( bytes );

    }

signals:

public slots:

private slots:

private:
};

#endif // QQTAUDIOEFFECT_H
