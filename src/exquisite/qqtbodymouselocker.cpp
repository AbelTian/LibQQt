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
    return d->getRect();
}

QRect QQtBodyMouseLocker::getContentRect ( QWidget* target )
{
    Q_D ( QQtBodyMouseLocker ) ;
    return d->getTargetRect ( target );
}

QRect QQtBodyMouseLocker::getSourceRect ( QWidget* target )
{
    Q_D ( QQtBodyMouseLocker ) ;
    return d->getSourceRect ( target );
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
            QMouseEvent* e = ( QMouseEvent* ) event;
            QWidget* target = qobject_cast<QWidget*> ( watched );
            QWidget& w = *target;

            if ( !target->isActiveWindow() )
            {
                event->ignore();
                return false;
            }

            QRect rectMustIn = QRect ( w.mapToGlobal ( w.rect().topLeft() ), w.mapToGlobal ( w.rect().bottomRight() ) );
            QMargins m_margins = w.contentsMargins();
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
            QRect rectMustNotIn = rectMustIn.adjusted ( m_margins.left(), m_margins.top(), m_margins.right(), m_margins.bottom() );
#else
            QRect rectMustNotIn = rectMustIn.marginsRemoved ( m_margins );
#endif
            QPoint cursorPos = QCursor::pos();

            //在content里面才能响应 [比较的时候不放大坐标]
            if ( rectMustIn.contains ( cursorPos ) && rectMustNotIn.contains ( cursorPos ) )
            {
                //设置的时候放大。Windows/Unix不一样。
                if ( d->getTargetRect ( target ) != d->getRect()  )
                    addWindow ( target );
            }
            //pline() << rectMustIn << rectMustNotIn << d->getRect() << cursorPos << e->globalPos();
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
