#include <qqtdebug.h>


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
    timer.start();

    //process
    eventloop.exec();

    //clear
    if ( timer.isActive() )
        timer.stop();

}


QQtBlock::QQtBlock ( QObject* parent ) : QObject ( parent ), m_lock ( 0 ) {}

bool QQtBlock::lock ( int millsecond )
{
    //m_lock++;
    m_lock = 1;

    timer.restart();

    while ( timer.elapsed() < millsecond )
    {
        if ( m_lock <= 0 )
            break;

        QApplication::processEvents();
    }

    if ( timer.elapsed() >= millsecond )
        return false;

    return true;
}

void QQtBlock::unlock()
{
    //m_lock--;
    m_lock = 0;
}

bool QQtBlock::isLocked()
{
    if ( m_lock <= 0 )
        return false;

    return true;
}

QQtBlockSignal::QQtBlockSignal ( QObject* parent ) : QQtBlock ( parent )
{

}

void QQtBlockSignal::addsignal ( const QObject* obj, const char* signal )
{

    QQtSignalObject o0;
    o0.obj = obj;
    o0.signal = signal;

    if ( mSignalList.contains ( o0 ) )
        return;
    mSignalList.push_back ( o0 );

    connect ( obj, signal, this, SLOT ( slotSignalComing() ) );
}

void QQtBlockSignal::slotSignalComing()
{
    unlock();
}
