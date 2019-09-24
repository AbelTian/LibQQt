#include "qqtbodymover.h"
#include "qqtbodymover_p.h"

#include <QWidget>
#include <QMouseEvent>

QQtBodyMover::QQtBodyMover ( QObject* parent ) : QObject ( parent )
{
    d_ptr = new QQtBodyMoverPrivate ( this );
}

QQtBodyMover::~QQtBodyMover()
{
    delete d_ptr;
}

bool QQtBodyMover::eventFilter ( QObject* watched, QEvent* event )
{
    //过滤掉不是QWidget
    if ( !watched->inherits ( "QWidget" ) )
        return QObject::eventFilter ( watched, event );

    //修复 paint bug
    /*fix the parent handled bug terminally*/
    if ( event->type() == QEvent::Paint )
        return QObject::eventFilter ( watched, event );

    //修复鼠标穿透。
    bool atti = ( qobject_cast<QWidget*> ( watched ) )->testAttribute ( Qt::WA_TransparentForMouseEvents );
    if ( atti )
        return QObject::eventFilter ( watched, event );

    Q_D ( QQtBodyMover ) ;

    switch ( event->type() )
    {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            d->mousePressEvent ( e, qobject_cast<QWidget*> ( watched ) );
            return false;
        }
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            d->mouseReleaseEvent ( e, qobject_cast<QWidget*> ( watched ) );
            return false;
        }
        case QEvent::MouseMove:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            d->mouseMoveEvent ( e, qobject_cast<QWidget*> ( watched ) );
            return false;
        }
        default:
            break;
    }

    return QObject::eventFilter ( watched, event );

}
