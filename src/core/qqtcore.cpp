#include "qqtcore.h"

QByteArray& operator<< ( QByteArray& l, const quint8& r )
{
    return l.append ( r );
}

QByteArray& operator<< ( QByteArray& l, const quint16& r )
{
    return l << quint8 ( r >> 8 ) << quint8 ( r );
}

QByteArray& operator<< ( QByteArray& l, const quint32& r )
{
    return l << quint16 ( r >> 16 ) << quint16 ( r );
}

QByteArray& operator<< ( QByteArray& l, const quint64& r )
{
    return l << quint32 ( r >> 32 ) << quint32 ( r );
}


QByteArray& operator<< ( QByteArray& l, const qint8& r )
{
    quint8 ubyte = quint8 ( r );
    l << ubyte;
    return l;
}

QByteArray& operator<< ( QByteArray& l, const qint16& r )
{
    quint16 ubyte = quint16 ( r );
    l << ubyte;
    return l;
}

QByteArray& operator<< ( QByteArray& l, const qint32& r )
{
    quint32 ubyte = quint32 ( r );
    l << ubyte;
    return l;
}

QByteArray& operator<< ( QByteArray& l, const qint64& r )
{
    quint64 ubyte = quint64 ( r );
    l << ubyte;
    return l;
}

QByteArray& operator<< ( QByteArray& l, const QByteArray& r )
{
    return l.append ( r );
}


QByteArray& operator>> ( QByteArray& l, quint8& r )
{
    r = l.left ( sizeof ( quint8 ) ) [0];
    return l.remove ( 0, sizeof ( quint8 ) );
}

QByteArray& operator>> ( QByteArray& l, quint16& r )
{
    quint8 r0 = 0, r1 = 0;
    l >> r0 >> r1;
    r = ( r0 << 8 ) | r1;
    return l;
}

QByteArray& operator>> ( QByteArray& l, quint32& r )
{
    quint8 r0 = 0, r1 = 0, r2 = 0, r3 = 0;
    l >> r0 >> r1 >> r2 >> r3;
    r = ( r0 << 24 ) | ( r1 << 16 ) | ( r2 << 8 ) | r3;
    return l;
}

QByteArray& operator>> ( QByteArray& l, quint64& r )
{
    quint8 r0 = 0, r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0;
    l >> r0 >> r1 >> r2 >> r3 >> r4 >> r5 >> r6 >> r7;
    r = ( ( quint64 ) r0 << 56 ) | ( ( quint64 ) r1 << 48 ) | ( ( quint64 ) r2 << 40 ) | ( ( quint64 ) r3 << 32 ) |
        ( r4 << 24 ) | ( r5 << 16 ) | ( r6 << 8 ) | r7;
    return l;
}


QByteArray& operator>> ( QByteArray& l, qint8& r )
{
    quint8 ubyte = 0;
    l >> ubyte;
    r = qint8 ( ubyte );
    return l;
}

QByteArray& operator>> ( QByteArray& l, qint16& r )
{
    quint16 ubyte = 0;
    l >> ubyte;
    r = qint16 ( ubyte );
    return l;
}

QByteArray& operator>> ( QByteArray& l, qint32& r )
{
    quint32 ubyte = 0;
    l >> ubyte;
    r = qint32 ( ubyte );
    return l;
}

QByteArray& operator>> ( QByteArray& l, qint64& r )
{
    quint64 ubyte = 0;
    l >> ubyte;
    r = qint64 ( ubyte );
    return l;
}


QByteArray& operator>> ( QByteArray& l, QByteArray& r )
{
    r = l.left ( r.size() );
    return l.remove ( 0, r.size() );
}


//不堵塞GUI睡眠。
void QQtSleep ( int millsecond )
{
    QElapsedTimer timer;
    timer.start();

    while ( timer.elapsed() < millsecond )
    {
        QApplication::processEvents();
    }
}

//0 不堵塞GUI。
//1 超时退出
//2 接收到信号，提前退出。
void QQtSleepSignal ( int millsecond, const QObject* obj, const char* signal )
{
    //initilizer
    QEventLoop eventloop;
    QObject::connect ( obj, signal, &eventloop, SLOT ( quit() ) );

    QTimer timer;
    timer.setSingleShot ( true );
    timer.setInterval ( millsecond );
    QObject::connect ( &timer, SIGNAL ( timeout() ), &eventloop, SLOT ( quit() ) );

    //process
    eventloop.exec();

    //clear
    if ( timer.isActive() )
        timer.stop();

}
