#include "qqtbodyresizer.h"
#include "qqtbodyresizer_p.h"

#include <QWidget>
#include <QMouseEvent>

QQtBodyResizer::QQtBodyResizer ( QObject* parent ) : QObject ( parent )
{
    d_ptr = new QQtBodyResizerPrivate ( this );
}

QQtBodyResizer::~QQtBodyResizer()
{
    delete d_ptr;
}

QMargins& QQtBodyResizer::margins()
{
    Q_D ( QQtBodyResizer );
    return d->margins();
}

bool QQtBodyResizer::eventFilter ( QObject* watched, QEvent* event )
{
    //过滤掉不是QWidget
    if ( !watched->inherits ( "QWidget" ) )
        return QObject::eventFilter ( watched, event );

    //修复 paint bug
    /*fix the parent handled bug terminally*/
    if ( event->type() == QEvent::Paint )
        return QObject::eventFilter ( watched, event );

    //修复鼠标穿透。如果鼠标穿透，那么不发生作用。
    bool atti = ( ( QWidget* ) watched )->testAttribute ( Qt::WA_TransparentForMouseEvents );
    if ( atti )
        return QObject::eventFilter ( watched, event );

    Q_D ( QQtBodyResizer ) ;

    switch ( event->type() )
    {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            d->mousePressEvent ( e, ( QWidget* ) watched );
            return false;
        }
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            d->mouseReleaseEvent ( e, ( QWidget* ) watched );
            return false;
        }
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
