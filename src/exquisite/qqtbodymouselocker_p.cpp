#include "qqtbodymouselocker_p.h"
#include "qqtbodymouselocker.h"

#include <QWidget>

QQtBodyMouseMouseLockerThreadHelper::QQtBodyMouseMouseLockerThreadHelper ( QObject* parent ) : QThread ( parent )
{
    workflag = false;
    mGlobalRect = QRect ( 0, 0, 0, 0 );
    startCapture();
}

QQtBodyMouseMouseLockerThreadHelper::~QQtBodyMouseMouseLockerThreadHelper()
{
    stopCapture();
}

void QQtBodyMouseMouseLockerThreadHelper::setTargetGlobalRect ( QRect globalRect )
{
    tex.lock();
    mGlobalRect = globalRect;
    tex.unlock();
}

QRect QQtBodyMouseMouseLockerThreadHelper::getTargetGlobalRect()
{
    return mGlobalRect;
}

void QQtBodyMouseMouseLockerThreadHelper::startCapture()
{
    tex.lock();
    workflag = true;
    tex.unlock();
    start();
}

void QQtBodyMouseMouseLockerThreadHelper::stopCapture()
{
    tex.lock();
    workflag = false;
    tex.unlock();
    quit();
    wait();
}

void QQtBodyMouseMouseLockerThreadHelper::run()
{
    while ( 1 )
    {
        usleep ( 10 );

        tex.lock();
        bool lworkflag = workflag;
        tex.unlock();
        if ( !lworkflag )
            return;

        QRect globalRect;
        tex.lock();
        globalRect = this->mGlobalRect;
        tex.unlock();

        if ( globalRect == QRect ( 0, 0, 0, 0 ) )
            continue;

        QRect s = globalRect;

        int x = QCursor::pos().x();
        int y = QCursor::pos().y();

        int x1 = x, y1 = y;
        if ( x <= s.left() )
            x1 = s.left();
        if ( y <= s.top() )
            y1 = s.top();
        if ( x >= s.right() )
            x1 = s.right();
        if ( y >= s.bottom() )
            y1 = s.bottom();

        QCursor::setPos ( x1, y1 );
    }
}

QQtBodyMouseLockerPrivate::QQtBodyMouseLockerPrivate ( QQtBodyMouseLocker* q )
{
    q_ptr = q;
    helper = QQtBodyMouseMouseLockerThreadHelper::instance ( q );
}

QQtBodyMouseLockerPrivate::~QQtBodyMouseLockerPrivate()
{
}

void QQtBodyMouseLockerPrivate::addRect ( const QRect globalRect )
{
    helper->setTargetGlobalRect ( globalRect );
}

QRect QQtBodyMouseLockerPrivate::getRect()
{
    return helper->getTargetGlobalRect();
}

void QQtBodyMouseLockerPrivate::startCapture()
{
    helper->startCapture();
}

void QQtBodyMouseLockerPrivate::stopCapture()
{
    helper->stopCapture();
}

void QQtBodyMouseLockerPrivate::addWindow ( QWidget* target )
{
    Q_ASSERT ( target );

    QWidget& w = *target;

    QPoint p0, p1;
    p0 = w.rect().topLeft();
    p1 = w.rect().bottomRight();
    p0 = w.mapToGlobal ( p0 );
    p1 = w.mapToGlobal ( p1 );

    qreal ratio = 1; w.devicePixelRatioF();
    QRect r0 = QRect ( p0, p1 );
    QRect qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ),
                        QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );

    QRect rectMustIn = qr0;

    helper->setTargetGlobalRect ( rectMustIn );
}
