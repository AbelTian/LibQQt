#include "qqtmouselocker.h"
#include "qqtmouselocker_p.h"

QQtMouseLocker::QQtMouseLocker ( QObject* parent ) : QObject ( parent )
{
    d_ptr = new QQtMouseLockerPrivate ( this );
}

QQtMouseLocker::~QQtMouseLocker()
{
    delete d_ptr;
}

bool QQtMouseLocker::eventFilter ( QObject* watched, QEvent* event )
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

    Q_D ( QQtMouseLocker ) ;

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
        case QEvent::MouseMove:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            d->mouseMoveEvent ( e, ( QWidget* ) watched );
            return false;
        }
        default:
            break;
    }

    return QObject::eventFilter ( watched, event );

}
