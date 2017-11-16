#include "qqtmplayer.h"
#include "qqtcore.h"

QQTPlayer::QQTPlayer(QObject* parent) :
    QObject(parent)
{
    app = new QProcess(this);
}

void QQTPlayer::play(QString filename, int wid, int width, int height)
{
    QString mppath = "mplayer";
    QStringList mpargs;
    mpargs << "-slave";
    mpargs << "-quiet";
    mpargs << "-idle";
    mpargs << "-zoom";
    mpargs << "-x";
    mpargs << QString("%1").arg(width);
    mpargs << "-y";
    mpargs << QString("%1").arg(height);
    mpargs << "-wid";
    mpargs << QString::number(wid);
    mpargs << filename;

    app->setProcessChannelMode(QProcess::SeparateChannels);
    app->start(mppath, mpargs, QIODevice::Truncate | QIODevice::ReadWrite);

    if (!app->waitForStarted(3000))
        pline() << "mpp start fail :(";

    pline() << "mpp start success :)";
}

void QQTPlayer::pause()
{
    char buf[256] = {0};
    sprintf(buf, "pause\n");
    app->write(buf);
}

void QQTPlayer::stop()
{
    char buf[256] = {0};
    sprintf(buf, "stop\n");
    app->write(buf);
    sprintf(buf, "quit\n");
    app->write(buf);
}

double QQTPlayer::timeLength()
{
    char buf[256] = {0};
    sprintf(buf, "get_time_length\n");
    app->write(buf);
    memset(buf, 0, 256);
    app->read(buf, 256);
    double length = 0;
    sscanf(buf, "ANS_LENGTH=%lf", &length);
    return length;
}

double QQTPlayer::timePos()
{
    char buf[256] = {0};
    sprintf(buf, "get_time_pos\n");
    app->write(buf);
    memset(buf, 0, 256);
    app->read(buf, 256);
    double pos = 0;
    sscanf(buf, "ANS_TIME_POSITION=%lf", &pos);
    return pos;
}

int QQTPlayer::percent()
{
    char buf[256] = {0};
    sprintf(buf, "get_percent\n");
    app->write(buf);
    memset(buf, 0, 256);
    app->read(buf, 256);
    int pos = 0;
    sscanf(buf, "ANS_PERCENT_POSITION=%d", &pos);
    return pos;
}

void QQTPlayer::seekPos(double second)
{
    char buf[256] = {0};
    sprintf(buf, "seek %lf\n", second);
    app->write(buf);
}

void QQTPlayer::setVolume(int v)
{
    char buf[256] = {0};
    sprintf(buf, "volume %d 1\n", v);
    app->write(buf);
}

void QQTPlayer::mute(bool m)
{
    char buf[256] = {0};
    sprintf(buf, "mute %d\n", m);
    app->write(buf);
}

void QQTPlayer::setRect(int x, int y, int width, int height)
{
    char buf[256] = {0};
    sprintf(buf, "change_rectangle 0 %d \n", width);
    app->write(buf);
    sprintf(buf, "change_rectangle 1 %d \n", height);
    app->write(buf);
    sprintf(buf, "change_rectangle 2 %d \n", x);
    app->write(buf);
    sprintf(buf, "change_rectangle 3 %d \n", y);
    app->write(buf);
}
