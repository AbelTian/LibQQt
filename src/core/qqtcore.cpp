#include "qqtcore.h"


QByteArray &operator<<(QByteArray &l, const quint8 r)
{
    return l.append(r);
}


QByteArray &operator<<(QByteArray &l, const quint16 r)
{
    return l<<quint8(r>>8)<<quint8(r);
}


QByteArray &operator<<(QByteArray &l, const quint32 r)
{
    return l<<quint16(r>>16)<<quint16(r);
}


QByteArray &operator<<(QByteArray &l, const QByteArray &r)
{
    return l.append(r);
}


QByteArray &operator>>(QByteArray &l, quint8 &r)
{
    r = l.left(sizeof(quint8))[0];
    return l.remove(0, sizeof(quint8));
}


QByteArray &operator>>(QByteArray &l, quint16 &r)
{
    quint8 r0 = 0, r1 = 0;
    l >> r0 >> r1;
    r = ( r0 << 8 ) | r1;
    return l;
}


QByteArray &operator>>(QByteArray &l, quint32 &r)
{
    quint8 r0 = 0, r1 = 0, r2 = 0, r3 = 0;
    l >> r0 >> r1 >> r2 >> r3;
    r = ( r0 << 24 ) | ( r1 << 16 ) | ( r2 << 8 ) | r3;
    return l;
}


QByteArray &operator>>(QByteArray &l, QByteArray &r)
{
    r = l.left(r.size());
    return l.remove(0, r.size());
}

QByteArray &operator<<(QByteArray &l, const qint8 r)
{
    quint8 ubyte = quint8(r);
    l << ubyte;
    return l;
}

QByteArray &operator<<(QByteArray &l, const qint16 r)
{
    quint16 ubyte = quint16(r);
    l << ubyte;
    return l;
}

QByteArray &operator<<(QByteArray &l, const qint32 r)
{
    quint32 ubyte = quint32(r);
    l << ubyte;
    return l;
}

QByteArray &operator>>(QByteArray &l, qint8 r)
{
    quint8 ubyte = 0;
    l >> ubyte;
    r = qint8(ubyte);
    return l;
}

QByteArray &operator>>(QByteArray &l, qint16 r)
{
    quint16 ubyte = 0;
    l >> ubyte;
    r = qint16(ubyte);
    return l;
}

QByteArray &operator>>(QByteArray &l, qint32 r)
{
    quint32 ubyte = 0;
    l >> ubyte;
    r = qint32(ubyte);
    return l;
}

void QQTSleep(int millsecond)
{
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < millsecond)
    {
         QApplication::processEvents();
    }
}
