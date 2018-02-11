#ifndef QQTAUDIOEFFECT_H
#define QQTAUDIOEFFECT_H

#include <qqtaudiomanager.h>
#include <qqtcore.h>
#include <qqt-local.h>

#include <QAudio>
#include <QAudioBuffer>
#include <QAudioDecoder>

#include <QMimeType>
#include <QMimeData>
#include <QMimeDatabase>
/**
 * @brief The QQtAudioEffect class
 * QSound、QSoundEffect是不能指定输出设备的。
 * 用于播放音效文件，接受指定输出设备。
 * 请不要用来播放大文件
 * 尝试用QQt的，需要切掉wav文件的44头。
 * 尝试用QAudioDecoder，解码器不支持x-wav，defaultServiceProvider::requestService(): no service found for - "org.qt-project.qt.audiodecode"
 * 回头用QQt的。
 */
class QQTSHARED_EXPORT QQtAudioEffect : public QQtAudioManager
{
    Q_OBJECT
public:
    explicit QQtAudioEffect ( QObject* parent = nullptr ) ;

    void play ( QString localFile );
    //需要用户设置输出设备
    void customPlay ( QString localFile );

signals:

public slots:

private slots:
    void bufferReady();
    void finished();

private:
    QAudioDecoder mDecoder;
};

#endif // QQTAUDIOEFFECT_H
