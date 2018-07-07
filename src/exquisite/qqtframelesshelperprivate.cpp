#include "qqtframelesshelperprivate.h"
#include <QTimer>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QDebug>
#include <QApplication>

QQtFramelessHelperPrivate::QQtFramelessHelperPrivate ( QWidget* parent )
    : parent ( parent ),
      isMaximized ( false ),
      direction ( None ),
      buttonMaximized ( 0 ),
      buttonRestore ( 0 ),
      buttonClose ( 0 ),
      buttonMinimized ( 0 ),
      isMousePressed ( false ),
      QObject ( parent )
{
    margins = QMargins ( 8, 8, 8, 8 );
    parent->setWindowFlags ( parent->windowFlags() | ( Qt::FramelessWindowHint ) );
    parent->installEventFilter ( this );


    timer = new QTimer ( this );
    timer->setInterval ( 400 );
    connect ( timer, SIGNAL ( timeout() ), this, SLOT ( checkPos() ) );

    timer->start();
}

void QQtFramelessHelperPrivate::addEdgeWidget ( QWidget* widget )
{
    if ( !edgeWidgets.contains ( widget ) )
    {
        edgeWidgets.append ( widget );

        if ( !dragWidgets.contains ( widget ) )
        {
            widget->installEventFilter ( this );
        }
    }
}

void QQtFramelessHelperPrivate::addDragWidget ( QWidget* widget )
{
    if ( !dragWidgets.contains ( widget ) )
    {
        dragWidgets.append ( widget );

        if ( !edgeWidgets.contains ( widget ) )
        {
            widget->installEventFilter ( this );
        }
    }
}

void QQtFramelessHelperPrivate::checkPos()
{
    QRect rectMustIn = parent->frameGeometry();
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    QRect rectMustNotIn = rectMustIn.marginsRemoved ( margins );
#else
    QRect rectMustNotIn = rectMustIn.adjusted ( margins.left(), margins.top(), margins.right(), margins.bottom() );
#endif
    QPoint cursorPos = QCursor::pos();

    if ( isMaximized ||
         !parent->isActiveWindow() ||
         !rectMustIn.contains ( cursorPos ) ||
         rectMustNotIn.contains ( cursorPos ) )
    {
        direction = None;
        parent->unsetCursor();
        return;
    }

    int baseLeftCoord, baseTopCoord, baseRightCoord, baseBottomCoord;

    rectMustNotIn.getCoords ( &baseLeftCoord, &baseTopCoord, &baseRightCoord, &baseBottomCoord );

    int x, y;
    x = cursorPos.x();
    y = cursorPos.y();

    direction = None;

    if ( x < baseLeftCoord )
    {
        if ( y < baseTopCoord )
        {
            direction = LeftTop;
        }
        else if ( y > baseBottomCoord )
        {
            direction = LeftBottom;
        }
        else
        {
            direction = Left;
        }
    }
    else if ( x > baseRightCoord )
    {
        if ( y < baseTopCoord )
        {
            direction = RightTop;
        }
        else if ( y > baseBottomCoord )
        {
            direction = RightBottom;
        }
        else
        {
            direction = Right;
        }
    }

    if ( direction == None )
    {
        if ( y < baseTopCoord )
        {
            direction = Top;
        }
        else
        {
            direction = Bottom;
        }
    }

    switch ( direction )
    {
        case Left:
        case Right:
            parent->setCursor ( Qt::SizeHorCursor );
            break;

        case Top:
        case Bottom:
            parent->setCursor ( Qt::SizeVerCursor );
            break;

        case LeftTop:
        case RightBottom:
            parent->setCursor ( Qt::SizeFDiagCursor );
            break;

        case LeftBottom:
        case RightTop:
            parent->setCursor ( Qt::SizeBDiagCursor );
            break;
    }
}

void QQtFramelessHelperPrivate::resize ( const QPoint& cursorPos )
{
    QSize oldSize = parent->size();

    int x, y, width = 0, height = 0;

    switch ( direction )
    {
        case Left: // left
            width = oldSize.width() - cursorPos.x();
            height = oldSize.height();

            x = parent->pos().x() - ( width - oldSize.width() );
            y = parent->pos().y();
            break;

        case Right: //right
            width = cursorPos.x();
            height = oldSize.height();

            x = parent->pos().x();
            y = parent->pos().y();
            break;

        case LeftTop: //left top
            width = oldSize.width() - cursorPos.x();
            height = oldSize.height() - cursorPos.y();

            x = parent->pos().x() - ( width - oldSize.width() );
            y = parent->pos().y() - ( height - oldSize.height() );
            break;

        case RightTop: //right top
            width = cursorPos.x();
            height = oldSize.height() - cursorPos.y();

            x = parent->pos().x();
            y = parent->pos().y() - ( height - oldSize.height() );

            break;

        case LeftBottom: //left bottom
            width = oldSize.width() - cursorPos.x();
            height = cursorPos.y();

            x = parent->pos().x() - ( width - oldSize.width() );
            y = parent->pos().y();

            break;

        case RightBottom: //right bottom
            width = cursorPos.x();
            height = cursorPos.y();

            x = parent->pos().x();
            y = parent->pos().y();
            break;

        case Top: //top
            width = oldSize.width();
            height =  oldSize.height() - cursorPos.y();

            x = parent->pos().x();
            y = parent->pos().y() - ( height - oldSize.height() );
            break;

        case Bottom: //bottom
            width = oldSize.width();
            height = cursorPos.y();

            x = parent->pos().x();
            y = parent->pos().y();
            break;
    }

    if ( width > ( margins.left() + margins.right() ) &&
         height > ( margins.top() + margins.bottom() ) )
    {
        parent->move ( x, y );
        parent->resize ( width, height );
    }
}

void QQtFramelessHelperPrivate::refreshMaximizedButton()
{
    isMaximized = parent->windowState().testFlag ( Qt::WindowMaximized );

    if ( buttonRestore != 0 )
    {
        buttonRestore->setVisible ( isMaximized );
    }

    if ( buttonMaximized != 0 )
    {
        buttonMaximized->setVisible ( !isMaximized );
    }
}

bool QQtFramelessHelperPrivate::eventFilter ( QObject* obj, QEvent* event )
{
    do
    {
        if ( event->type() == QEvent::WindowStateChange )
        {
            refreshMaximizedButton();
            break;
        }

        if ( event->type() == QEvent::MouseButtonPress )
        {
            QMouseEvent* e = ( QMouseEvent* ) event;

            // no move, no drag
            if ( e->button() != Qt::LeftButton  || isMaximized )
            {
                break;
            }

            checkPos();

            if ( ( obj == parent || edgeWidgets.contains ( qobject_cast<QWidget*> ( obj ) ) ) && direction != None )
            {
                isMousePressed = true;
                operation = MoveResize;
                timer->stop();
                return true;
            }

            if ( dragWidgets.contains ( qobject_cast<QWidget*> ( obj ) ) && direction == None )
            {
                isMousePressed = true;
                operation = MoveDrag;
                dragBasePoint =  e->globalPos() - parent->pos();
                timer->stop();
                return true;
            }

            break;
        }

        if ( event->type() == QEvent::MouseMove && isMousePressed )
        {
            QMouseEvent* e = ( QMouseEvent* ) event;

            if ( operation == MoveDrag )
            {
                parent->move ( e->globalPos() - dragBasePoint );
                return true;
            }

            if ( operation == MoveResize )
            {
                if ( obj != parent )
                {
                    QWidget* w = qobject_cast<QWidget*> ( obj );
                    resize ( w->mapTo ( parent, e->pos() ) );
                }
                else
                {
                    resize ( e->pos() );
                }

                return true;
            }

            break;
        }

        if ( event->type() == QEvent::MouseButtonRelease )
        {
            QMouseEvent* e = ( QMouseEvent* ) event;

            if ( e->button() == Qt::LeftButton && isMousePressed )
            {
                isMousePressed = false;
                operation = MoveNone;
                timer->start();
                return true;
            }

            break;
        }

    } while ( false );



    return QObject::eventFilter ( obj, event );
}
