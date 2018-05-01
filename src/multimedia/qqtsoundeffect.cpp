#include "qqtsoundeffect.h"


QQtWavSoundEffect* QQtWavSoundEffect::msInstance = NULL;

QQtWavSoundEffect* QQtWavSoundEffect::Instance ( QObject* parent )
{
    if ( !msInstance )
        msInstance = new QQtWavSoundEffect ( parent );

    return msInstance;
}

QQtWavSoundEffect::QQtWavSoundEffect ( QObject* parent ) : QObject ( parent )
{
    mVolume = 1;
    mIOInput = NULL;
    mLooping = 1;
    mLoops = 1;
}

void QQtWavSoundEffect::setOutputDevice ( const QAudioDeviceInfo& output )
{
    if ( output.isNull() )
        manager.outputDeviceInfo() = QQtAudioManager::defaultOutputDevice();
    else
        manager.outputDeviceInfo() = output;
}

void QQtWavSoundEffect::useDefaultOutputDevice()
{
    manager.outputDeviceInfo() = QQtAudioManager::defaultOutputDevice();
}

void QQtWavSoundEffect::useCustomOutputDevice ( const QAudioDeviceInfo& output )
{
    manager.outputDeviceInfo() = output;
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
QDebug& operator <<(QDebug& dbg, const QAudioFormat& fmt)
{
    return dbg;
}
#endif

void QQtWavSoundEffect::play ( QString localFile )
{
#if QT_VERSION > QT_VERSION_CHECK(5,0,0)

    //判断文件类型是否接受
    QMimeDatabase mimedb;
    QMimeType mimetype = mimedb.mimeTypeForFile ( localFile );

    if ( !QSoundEffect::supportedMimeTypes().contains ( mimetype.name(), Qt::CaseInsensitive ) )
    {
        pline() << "filename" << localFile << "mimetype" << mimetype.name()
                << QSoundEffect::supportedMimeTypes().contains ( mimetype.name(), Qt::CaseInsensitive ) ;
        pline() << "can't play file";
        return;
    }
#endif

    mSourceFile = localFile;

    stop();

    mIOInput = mWavInput.setSourceFile ( localFile );
    connect ( mIOInput, SIGNAL ( readyRead() ),
              this, SLOT ( readyRead() ) );

    QAudioDeviceInfo& usingOutput = manager.outputDeviceInfo();

    QAudioFormat fmt = mWavInput.format();

    //输出设备是否支持格式是否支持
    if ( !usingOutput.isFormatSupported ( fmt ) )
    {
        //当前使用设备是否支持
        pline() << "output cant support" << fmt;
        fmt = usingOutput.nearestFormat ( fmt ); //转换为最接近格式
        pline() << "use format" << fmt;
    }

    manager.outputAudioFormat() = fmt;

    manager.startOutput();
#if QT_VERSION > QT_VERSION_CHECK(5,0,0)

    //默认是静音的。
    manager.outputManager()->setVolume ( mVolume );
#endif

    //不响，音频输出设备接受顺序的间隔的输出，不接受一股脑输出。
    //manager.write ( bytes );
    //OK, 达到QSound效果。
    mWavInput.start();
}

void QQtWavSoundEffect::stop()
{
    //如果正在播放，先关闭
    if ( mIOInput )
    {
        mWavInput.stop();
        manager.stopOutput();
        disconnect ( mIOInput, SIGNAL ( readyRead() ),
                     this, SLOT ( readyRead() ) );
        mIOInput = NULL;
    }

    mLooping = 1;
    mDataSize = 0;
}

void QQtWavSoundEffect::setVolume ( qreal volume )
{
    mVolume = volume;
#if QT_VERSION > QT_VERSION_CHECK(5,0,0)

    manager.outputManager()->setVolume ( mVolume );
#endif
}

int QQtWavSoundEffect::loops() const { return mLoops; }

int QQtWavSoundEffect::loopsRemaining() const
{
    return mLoops - mLooping;
}

void QQtWavSoundEffect::setLoops ( int loops )
{
    mLoops = loops;
}

void QQtWavSoundEffect::readyRead()
{
    QByteArray bytes = mIOInput->readAll();
    //pline() << bytes.size();
    manager.write ( bytes );

    mDataSize += bytes.size();

    if ( mDataSize == mWavInput.fileDataSize() )
    {
        int loop = mLooping;

        if ( loop < loops() )
            play ( mSourceFile );

        mLooping = loop + 1;
    }
}

QQtWavSoundEffect* QQtWavSound ( QString localFile )
{
    if ( !localFile.isEmpty() )
        QQtWavSoundEffect::Instance ( )->play ( localFile );

    return QQtWavSoundEffect::Instance();
}

