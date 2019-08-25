#include "qqtvirtualclickhelper.h"

QQtVirtualClickHelper::QQtVirtualClickHelper ( QObject* parent ) : QObject ( parent )
{
    nTotalClickNumWithCancel = 0;
    nTotalClickNum = 0;
    mClickType = QQtNullClick;
}

QQtVirtualClickHelper::~QQtVirtualClickHelper()
{

}

void QQtVirtualClickHelper::mousePressEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "press" << event->pos() << userWidget;
}

void QQtVirtualClickHelper::mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "release" << event->pos() << userWidget;
}

void QQtVirtualClickHelper::mouseDoubleClickEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "double click" << event->pos() << userWidget;
}

void QQtVirtualClickHelper::checkClickNumWithCancel()
{
    switch ( mClickType )
    {
        default:
            break;
    }

    nTotalClickNumWithCancel = 0;
    if ( nTotalClickNumWithCancel >= 0xFFFFFFFFFFFFFFFF )
    {
        p2debug() << "out......";
        nTotalClickNumWithCancel = 0;
    }
}

void QQtVirtualClickHelper::checkClickNum ( QQtVirtualClickHelper::QQtClickType type )
{
    switch ( type )
    {
        default:
            break;
    }

    nTotalClickNum = 0;
    if ( nTotalClickNum >= 0xFFFFFFFFFFFFFFFF )
    {
        p2debug() << "out......";
        nTotalClickNum = 0;
    }
}


bool QQtVirtualClickHelper::eventFilter ( QObject* watched, QEvent* event )
{
    //过滤掉不是QWidget
    if ( !watched->inherits ( "QWidget" ) )
        return QObject::eventFilter ( watched, event );

    //修复 paint bug
    /*fix the parent handled bug terminally*/
    if ( event->type() == QEvent::Paint )
        return QObject::eventFilter ( watched, event );

    //修复鼠标穿透。如果鼠标穿透，那么不发生作用。
    bool atti = ( qobject_cast<QWidget*> ( watched ) )->testAttribute ( Qt::WA_TransparentForMouseEvents );
    if ( atti )
        return QObject::eventFilter ( watched, event );

    switch ( event->type() )
    {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            if ( e->button() != Qt::LeftButton )
                break;
            this->mousePressEvent ( e, qobject_cast<QWidget*> ( watched ) );
            event->accept();
            return false;
        }
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            if ( e->button() != Qt::LeftButton )
                break;
            this->mouseReleaseEvent ( e, qobject_cast<QWidget*> ( watched ) );
            event->accept();
            return false;
        }
        case QEvent::MouseButtonDblClick:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            if ( e->button() != Qt::LeftButton )
                break;
            this->mouseDoubleClickEvent ( e, qobject_cast<QWidget*> ( watched ) );
            event->accept();
            return false;
        }
        default:
            break;
    }

    return QObject::eventFilter ( watched, event );
}
