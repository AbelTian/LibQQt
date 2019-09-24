#include "qqtbodymouselocker_p.h"
#include "qqtbodymouselocker.h"

#include <QWidget>

QQtBodyMouseMouseLockerThreadHelper::QQtBodyMouseMouseLockerThreadHelper ( QObject* parent ) : QThread ( parent )
{
    workflag = false;
    target = 0;
}

QQtBodyMouseMouseLockerThreadHelper::~QQtBodyMouseMouseLockerThreadHelper()
{
}

void QQtBodyMouseMouseLockerThreadHelper::setTargetWidget ( QWidget* target )
{
    tex.lock();
    this->target = target;
    tex.unlock();
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
        tex.lock();
        bool lworkflag = workflag;
        tex.unlock();
        if ( !lworkflag )
            return;

        QWidget* target;
        tex.lock();
        target = this->target;
        tex.unlock();

        if ( !target )
            continue;

        //用户必须保证，手动，优先于UI释放本locker。
        if ( !target->isActiveWindow() )
            continue;

        //如果鼠标不在范围内不响应？NO。让用户给标题栏装个eventFilter？press关闭capture，realease开启capture？

        QWidget& w = *target;

        QPoint p0, p1;
        p0 = w.rect().topLeft();
        p1 = w.rect().bottomRight();
        p0 = w.mapToGlobal ( p0 );
        p1 = w.mapToGlobal ( p1 );
        QRect s = QRect ( p0, p1 );

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
        usleep ( 5 );
    }
}

QQtBodyMouseLockerPrivate::QQtBodyMouseLockerPrivate ( QQtBodyMouseLocker* q )
{
    q_ptr = q;
    helper = new QQtBodyMouseMouseLockerThreadHelper ( q );
    helper->startCapture();
}

QQtBodyMouseLockerPrivate::~QQtBodyMouseLockerPrivate()
{
    helper->stopCapture();
    delete helper;
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

    Q_Q ( QQtBodyMouseLocker );
    target->installEventFilter ( qobject_cast<QObject*> ( q ) );
    helper->setTargetWidget ( target );
}

void QQtBodyMouseLockerPrivate::removeWindow ( QWidget* target )
{
    Q_ASSERT ( target );

    Q_Q ( QQtBodyMouseLocker );
    target->removeEventFilter ( qobject_cast<QObject*> ( q ) );
    helper->setTargetWidget ( target );
}

void QQtBodyMouseLockerPrivate::focusInEvent ( QFocusEvent* event, QWidget* target )
{
}

void QQtBodyMouseLockerPrivate::focusOutEvent ( QFocusEvent* event, QWidget* target )
{
}

void QQtBodyMouseLockerPrivate::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    if ( target == 0 )
    {
        event->ignore();
        return;
    }

    if ( !target->isActiveWindow() )
    {
        event->ignore();
        return;
    }

    helper->setTargetWidget ( target );
    event->accept();
    return;
}
