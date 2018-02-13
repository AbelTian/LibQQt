#ifndef QQTAUDIOEFFECT_H
#define QQTAUDIOEFFECT_H

#include <qqtcore.h>
#include <qqt-local.h>

#include <qqtwavaudiomanager.h>

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
