#include "qqtaudioeffect.h"

QQtAudioEffect::QQtAudioEffect ( QObject* parent ) : QQtAudioManager ( parent )
{
    connect ( &mDecoder, SIGNAL ( bufferReady() ),
              this, SLOT ( bufferReady() ) );
    connect ( &mDecoder, SIGNAL ( finished() ),
              this, SLOT ( finished() ) );
}

void QQtAudioEffect::play ( QString localFile )
{
    static QFile file ( localFile );
    file.open ( QFile::ReadOnly );
    outputAudioFormat() = defaultOutputDevice().preferredFormat();
    startDeviceToDefaultOutput ( &file );
    return;

    QStringList codecs;
    codecs << "audio/x-wav";

    //判断类型是否接受
    QMimeDatabase mimedb;
    QMimeType mimetype = mimedb.mimeTypeForFile ( localFile );
    pline() << "filename" << localFile << "mimetype" << mDecoder.hasSupport ( mimetype.name(), codecs ) << mimetype.name();
    if ( !mDecoder.hasSupport ( mimetype.name() ) )
    {
        pline() << "can't play file";
        //return;
    }

    //准备输出设备
    outputAudioFormat() = defaultOutputDevice().preferredFormat();
    startDefaultOutput();

    //decoder 设置文件和格式 和信号槽
    //在槽里面进行播放。
    mDecoder.setSourceFilename ( localFile );
    mDecoder.start();
}

void QQtAudioEffect::customPlay ( QString localFile )
{

    QByteArray bytes;
    QFile f ( localFile );
    f.open ( QFile::ReadOnly );
    bytes = f.readAll();
    f.close();

    if ( !outputAudioFormat().isValid()
         || !outputDeviceInfo().isNull() )
    {
        outputAudioFormat() = defaultOutputDevice().preferredFormat();
        outputDeviceInfo() = defaultOutputDevice();
    }
    startOutput();
    writeBytes ( bytes );

}

void QQtAudioEffect::bufferReady()
{
    pline();
    QAudioBuffer buf = mDecoder.read();
    QByteArray bytes = QByteArray ( ( const char* ) buf.constData(), buf.byteCount() );
    writeBytes ( bytes );
}

void QQtAudioEffect::finished()
{
    pline();
    mDecoder.stop();
    stopOutput();
}
