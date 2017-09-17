#ifndef QQTMPLAYER_H
#define QQTMPLAYER_H

#include <QProcess>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQTPlayer : public QObject
{
    Q_OBJECT
public:
    explicit QQTPlayer(QObject *parent = 0);

    void play(QString filename, int wid = 0, int width = 20, int height = 20);
    void pause();
    void stop();
    double timeLength();
    double timePos();
    int percent();
    void seekPos(double second = 0);
    void setVolume(int v = 100);
    void mute(bool m = false);
    void setRect(int x, int y, int width, int height);

signals:

public slots:

private:
    QProcess* app;
};

#endif // QQTMPLAYER_H
