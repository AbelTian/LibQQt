#include "qqtaudioeffect.h"

QQtAudioEffect::QQtAudioEffect ( QObject* parent ) : QQtAudioManager ( parent )
{

}

void QQtAudioEffect::play ( QString localFile )
{
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
    write ( bytes );

}
