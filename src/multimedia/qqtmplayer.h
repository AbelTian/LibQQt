#ifndef QQTMPLAYER_H
#define QQTMPLAYER_H

#include <QProcess>

#include "qqtcore.h"
#include <qqt-local.h>

/**
 * @brief The QQtMPlayer class
 * 使用mplayer为后台播放视频文件。
 * 在e-linux全屏和窗口内切换的时候有一些条件，有机会给出。
 */
class QQTSHARED_EXPORT QQtMPlayer : public QObject
{
    Q_OBJECT
public:
    explicit QQtMPlayer ( QObject* parent = 0 );

    void play ( QString filename, int wid = 0, int width = 20, int height = 20 );
    void pause();
    void stop();
    double timeLength();
    double timePos();
    int percent();
    void seekPos ( double second = 0 );
    void setVolume ( int v = 100 );
    void mute ( bool m = false );
    void setRect ( int x, int y, int width, int height );

signals:

public slots:

private:
    QProcess* app;
};

#endif // QQTMPLAYER_H
