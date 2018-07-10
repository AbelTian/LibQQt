#ifndef QQTAUDIOEFFECT_H
#define QQTAUDIOEFFECT_H


#include <qqtwavaudiomanager.h>

#include <qqtcore.h>
#include <qqt-local.h>
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
    ~QQtWavSoundEffect() {
        stop();
    }

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

    //设置读文件的时钟快慢（硬盘快，时钟快，每次读的少；硬盘慢，时钟慢，每次读的多）
    //默认使用 macOS SSD 20ms
    //Windows上，机械硬盘，可能会延迟，可以设置100ms。
    void setTimerInterval ( int millSecond = 20 ) {
        mWavInput.setTimerInterval ( millSecond );
    }

private slots:
    void readyRead();

private:
    //不需要额外初始化的地方
    //mingw32 5.3 静态成员不准导出？作为静态类这块编译出现错误
    //error: definition of static data member 'QQtWavSoundEffect::msInstance' of dllimport'd class
    //这个已经查出来了，在qqt_header.pri有一个WIN64的宏缺失，导致QQT_STATIC_LIBRARY缺失，引发QQt在QQTSHAREDEXPORT=import下编译，所以引发这个变量重新定义的错误，而报错是在导入的类里面定义了静态成员，也就是说导入类不准许静态成员的定义初始化代码出现，引入类的静态成员在自己的实现文件里出现了定义。变量重定义了。
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
QQTSHARED_EXPORT QQtWavSoundEffect* QQtWavSound ( QString localFile = "" );

/**
 * @brief The QQtAudioEffect class
 * QSound、QSoundEffect是不能指定输出设备的。
 * 用于播放音效文件，接受指定输出设备。
 *
 * 请不要用来播放大文件，会全部读入内存，然后逐渐删除。
 * 尝试用QQt的，需要切掉wav文件的44头。
 * 现在更新为用QQt的，QQtAudioEffect目标支持多种格式的音效文件。
 * 未实现
 *
 * lame是编码器，解码器用mpg123
 */
class QQTSHARED_EXPORT QQtSoundEffect : public QQtAudioManager
{
    Q_OBJECT
public:
    explicit QQtSoundEffect ( QObject* parent = nullptr ) : QQtAudioManager ( parent ) {

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
