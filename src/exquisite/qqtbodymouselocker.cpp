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
    target->removeEventFilter ( this );
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

    static int i = 0;
    pline() << i++ << event->type() << watched->objectName();

    QWidget* target = qobject_cast<QWidget*> ( watched );
    QWidget& w = *target;

    QPoint p0, p1;
    p0 = w.rect().topLeft();
    p1 = w.rect().bottomRight();
    p0 = w.mapToGlobal ( p0 );
    p1 = w.mapToGlobal ( p1 );
    QRect r0 = QRect ( p0, p1 );

    qreal ratio = 1; w.devicePixelRatioF();
    QRect qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ),
                        QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );

    QRect globalRect = qr0;

    Q_D ( QQtBodyMouseLocker ) ;

    switch ( event->type() )
    {
#if 0
        //这两个有个bug，
        //FocusIn有bug，当从外部接触内部标题栏，FocusIN激发，鼠标摁住移动窗口只能在一个小范围移动。必须重新摁一次才能整体移动。
        //我的处理办法是，屏蔽掉这两个，已经满足要求，不必要这两个函数。

        //FocusIN激发的时候，摁住标题栏移动窗口时是否应当夺取鼠标？否定。
        //此处，禁止按照游戏窗口剥夺的思路，如果用户需要，那么自行添加功能。

        //激发时，如果是activeWindows，如果鼠标在frameGeometry外边，就截获。
        //                          如果在titleBar里面，press，必须move完成，release后，截获。
        case QEvent::FocusIn:
        {
            QFocusEvent* e = ( QFocusEvent* ) event;
            d->focusInEvent ( e, ( QWidget* ) watched );
            return false;
        }
        case QEvent::FocusOut:
        {
            QFocusEvent* e = ( QFocusEvent* ) event;
            d->focusOutEvent ( e, ( QWidget* ) watched );
            return false;
        }
#endif
#if 0
        //这一个就足够了?不论用polish还是windowactivate，都会是后添加的widget的消息起作用。哎呀。切换时有鼠标跳跃。
        case QEvent::Polish:
        {
            QWidget* target = qobject_cast<QWidget*> ( watched );
            //if ( target->isActiveWindow() )
            addWindow ( target );
            //pline() << target->isActiveWindow();
            //pline() << target->objectName();
            //经过测试，WindowsActivate比Press先发生
            //pline() << watched->objectName() << event->type();
            return false;
        }
#endif
#if 0
        //用于解决启动时获取鼠标
        //用于解决窗口从unactive到active状态切换的时候获取鼠标
        case QEvent::WindowActivate:
        {
            QWidget* target = qobject_cast<QWidget*> ( watched );
            //if ( target->isActiveWindow() )
            addWindow ( target );
            //pline() << target->isActiveWindow();
            //pline() << target->objectName();
            //经过测试，WindowsActivate比Press先发生
            //pline() << watched->objectName() << event->type();
            return false;
        }
#endif
#if 0
        //窗口不活动以后关闭捕获鼠标 省电
        case QEvent::WindowDeactivate:
        {
            //stopCapture();
            //QWidget* target = qobject_cast<QWidget*> ( watched );
            //if ( target->isActiveWindow() )
            //addWindow ( target );
            //pline() << target->isActiveWindow();
            //pline() << target->objectName();
            //经过测试，WindowsActivate比Press先发生
            //pline() << watched->objectName() << event->type();
            //startCapture();
            return false;
        }
#endif
#if 0
        //点击窗口时捕获鼠标
        //这一个还是有用的，用户设置了多个窗口锁定鼠标的时候，有这个才能实时响应鼠标点击动作进行捕获。尤其在tracking为false的时候。
        case QEvent::MouseButtonPress:
        {
            QWidget* target = qobject_cast<QWidget*> ( watched );
            addWindow ( target );
            //pline() << watched->objectName() << event->type();
            return false;
        }
#endif
        case QEvent::MouseButtonRelease:
        {
            addWindow ( target );
            return false;
        }
        case QEvent::WindowDeactivate:
        {
            //如果不是活动窗口，就失效。----很重要。
            d->addRect ( QRect ( 0, 0, 0, 0 ) );
            return false;
        }
        default:
            break;
    }

    //pline() << event->type() << watched->objectName();

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
