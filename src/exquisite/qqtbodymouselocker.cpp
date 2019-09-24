#include "qqtbodymouselocker.h"
#include "qqtbodymouselocker_p.h"

#include <qqtcore.h>

QQtBodyMouseLocker::QQtBodyMouseLocker ( QObject* parent ) : QObject ( parent )
{
    d_ptr = new QQtBodyMouseLockerPrivate ( this );
}

QQtBodyMouseLocker::~QQtBodyMouseLocker()
{
    delete d_ptr;
}

void QQtBodyMouseLocker::startCapture()
{
    Q_D ( QQtBodyMouseLocker ) ;
    d->startCapture();
}

void QQtBodyMouseLocker::stopCapture()
{
    Q_D ( QQtBodyMouseLocker ) ;
    d->stopCapture();
}

void QQtBodyMouseLocker::addWindow ( QWidget* target )
{
    Q_ASSERT ( target );

    Q_D ( QQtBodyMouseLocker ) ;
    d->addWindow ( target );
}

void QQtBodyMouseLocker::removeWindow ( QWidget* target )
{
    Q_ASSERT ( target );

    Q_D ( QQtBodyMouseLocker ) ;
    d->addRect ( QRect ( 0, 0, 0, 0 ) );
}

void QQtBodyMouseLocker::addClipCursor ( const QRect globalRect )
{
    Q_D ( QQtBodyMouseLocker ) ;
    d->addRect ( globalRect );
}

QRect QQtBodyMouseLocker::getClipCursor()
{
    Q_D ( QQtBodyMouseLocker ) ;
    d->getRect();
}

QRect QQtBodyMouseLocker::getContentRect ( QWidget* target )
{
    Q_D ( QQtBodyMouseLocker ) ;
    d->getTargetRect ( target );
}

bool QQtBodyMouseLocker::eventFilter ( QObject* watched, QEvent* event )
{
    //过滤掉不是QWidget
    if ( !watched->inherits ( "QWidget" ) )
        return QObject::eventFilter ( watched, event );

    //修复 paint bug
    /*fix the parent handled bug terminally*/
    if ( event->type() == QEvent::Paint )
        return QObject::eventFilter ( watched, event );

    //不修复鼠标穿透。鼠标穿透依然锁定。
    //bool atti = ( ( QWidget* ) watched )->testAttribute ( Qt::WA_TransparentForMouseEvents );
    //if ( atti )
    //    return QObject::eventFilter ( watched, event );

    //鼠标mustin 和 mustnotin需要判断一下。

    //static int i = 0;
    //pline() << i++ << event->type() << watched->objectName();

    Q_D ( QQtBodyMouseLocker ) ;

    switch ( event->type() )
    {
        //用户自行添加，过滤标题栏
        //case QEvent::WindowActivate:

        //用户自行添加，如果需要
        //case QEvent::ContentsRectChange:
        //case QEvent::UpdateLater:
        //case QEvent::UpdateRequest:

        //用户自行添加，如果需要
        //case QEvent::Move:
        //case QEvent::Resize:

        case QEvent::MouseButtonPress:
        case QEvent::MouseMove:
        case QEvent::MouseButtonRelease:
        {
            //鼠标点击的时候使用
            QWidget* target = qobject_cast<QWidget*> ( watched );
            QRect rectMustIn = QRect ( target->mapToGlobal ( target->rect().topLeft() ),
                                       target->mapToGlobal ( target->rect().bottomRight() ) );
            QRect rectMustNotIn = d->getTargetRect ( target );
            QPoint cursorPos = QCursor::pos();
            //在content里面才能响应
            if ( rectMustIn.contains ( cursorPos ) && rectMustNotIn.contains ( cursorPos ) )
                if ( rectMustNotIn != d->getRect()  )
                    addWindow ( target );
            event->accept();
            return false;
        }

        case QEvent::WindowDeactivate:
        {
            //如果不是活动窗口，就失效。----很重要。
            d->addRect ( QRect ( 0, 0, 0, 0 ) );
            event->accept();
            return false;
        }
        default:
            break;
    }

    return QObject::eventFilter ( watched, event );

}

void QQtClipCursor ( const QRect globalRect )
{
    QQtBodyMouseMouseLockerThreadHelper::instance()->setTargetGlobalRect ( globalRect );
}

QRect QQtGetClipCursor()
{
    return QQtBodyMouseMouseLockerThreadHelper::instance()->getTargetGlobalRect();
}

void QQtClipCursorToWindow ( QWidget* target )
{
    QRect globalRect = QQtBodyMouseLockerPrivate::getTargetRect ( target );
    QQtClipCursor ( globalRect );
}
