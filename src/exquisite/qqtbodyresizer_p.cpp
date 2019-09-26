#include "qqtbodyresizer_p.h"
#include "qqtbodyresizer.h"

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#ifdef Q_OS_WIN
//#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif
#include <qqtcore.h>

QQtBodyResizerPrivate::QQtBodyResizerPrivate ( QQtBodyResizer* q ) :
    q_ptr ( q )
{
    bMousePressed = false;
}

QQtBodyResizerPrivate::~QQtBodyResizerPrivate()
{
}

void QQtBodyResizerPrivate::mousePressEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );

    if ( event->button() == Qt::LeftButton )
    {
        bMousePressed = true;
        pressedPoint = event->globalPos();
    }

    checkDirection ( event, target );

    event->accept();
}

void QQtBodyResizerPrivate::mouseReleaseEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );
    bMousePressed = false;
    direction = None;
    event->accept();
}

void QQtBodyResizerPrivate::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );

    //QWidget* win = target->window();


    //如果鼠标没有press，遭遇到窗体边缘，变换鼠标样式。
    if ( !bMousePressed && !target->isMaximized() )
    {
        checkDirection ( event, target );
    }

    //如果鼠标pressed，那么移动。
    if ( bMousePressed && !target->isMaximized() )
    {
        QRect oldGeometry = target->geometry();
        QPoint widgetPos = oldGeometry.topLeft();

        int rx, ry;
        int x, y, width = 0, height = 0;

        QRect newGeometry = oldGeometry;

        switch ( direction )
        {
            case Left: // left
                //cursor
                rx = event->globalPos().x() - pressedPoint.x();
                ry = 0;

                //widget
                x = widgetPos.x() + rx;
                y = widgetPos.y();
                width = oldGeometry.width() - rx;
                height = oldGeometry.height();

                newGeometry = QRect ( x, y, width, height );

                //pline() << event->globalPos().x() << pressedPoint.x() << rx << ry;
                //pline() << oldGeometry << newGeometry;

                break;

            case Right: //right
                //cursor
                rx = event->globalPos().x() - pressedPoint.x();
                ry = 0;

                //widget
                x = widgetPos.x();
                y = widgetPos.y();
                width = oldGeometry.width() + rx;
                height = oldGeometry.height();

                newGeometry = QRect ( x, y, width, height );
                break;

            case LeftTop: //left top
                //cursor
                rx = event->globalPos().x() - pressedPoint.x();
                ry = event->globalPos().y() - pressedPoint.y();

                //widget
                x = widgetPos.x() + rx;
                y = widgetPos.y() + ry;
                width = oldGeometry.width() - rx;
                height = oldGeometry.height() - ry;

                newGeometry = QRect ( x, y, width, height );
                break;

            case RightTop: //right top
                //cursor
                rx = event->globalPos().x() - pressedPoint.x();
                ry = event->globalPos().y() - pressedPoint.y();

                //widget
                x = widgetPos.x();
                y = widgetPos.y() + ry;
                width = oldGeometry.width() + rx;
                height = oldGeometry.height() - ry;

                newGeometry = QRect ( x, y, width, height );

                break;

            case LeftBottom: //left bottom
                //cursor
                rx = event->globalPos().x() - pressedPoint.x();
                ry = event->globalPos().y() - pressedPoint.y();

                //widget
                x = widgetPos.x() + rx;
                y = widgetPos.y();
                width = oldGeometry.width() - rx;
                height = oldGeometry.height() + ry;

                newGeometry = QRect ( x, y, width, height );

                break;

            case RightBottom: //right bottom
                //cursor
                rx = event->globalPos().x() - pressedPoint.x();
                ry = event->globalPos().y() - pressedPoint.y();

                //widget
                x = widgetPos.x();
                y = widgetPos.y();
                width = oldGeometry.width() + rx;
                height = oldGeometry.height() + ry;

                newGeometry = QRect ( x, y, width, height );

                break;

            case Top: //top
                //cursor
                rx = 0;
                ry = event->globalPos().y() - pressedPoint.y();

                //widget
                x = widgetPos.x();
                y = widgetPos.y() + ry;
                width = oldGeometry.width();
                height = oldGeometry.height() - ry;

                newGeometry = QRect ( x, y, width, height );

                break;

            case Bottom: //bottom
                //cursor
                rx = 0;
                ry = event->globalPos().y() - pressedPoint.y();

                //widget
                x = widgetPos.x();
                y = widgetPos.y();
                width = oldGeometry.width();
                height = oldGeometry.height() + ry;

                newGeometry = QRect ( x, y, width, height );
                break;

            default:
                break;
        }

        pressedPoint = event->globalPos();

        QMargins m_margins = target->contentsMargins();

        if ( width > ( m_margins.left() + m_margins.right() ) &&
             height > ( m_margins.top() + m_margins.bottom() ) )
        {
            //target->move ( x, y );
            //target->resize ( width, height );
            target->setGeometry ( newGeometry );
        }

    }

    event->accept();
}

void QQtBodyResizerPrivate::checkDirection ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );

    QMargins m_margins = target->contentsMargins();

#if 0
    //geometry 与 globalPos 对比 root窗口
    QRect rectMustIn = target->geometry();//target->frameGeometry();
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    QRect rectMustNotIn = rectMustIn.marginsRemoved ( m_margins );
#else
    QRect rectMustNotIn = rectMustIn.adjusted ( m_margins.left(), m_margins.top(), m_margins.right(), m_margins.bottom() );
#endif
    QPoint cursorPos = event->globalPos();//QCursor::pos();
#endif

#if 0
    //rect() 与 pos() 对比 子窗口
    QRect rectMustIn = target->rect();//target->frameGeometry();
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QRect rectMustNotIn = rectMustIn.adjusted ( m_margins.left(), m_margins.top(), m_margins.right(), m_margins.bottom() );
#else
    QRect rectMustNotIn = rectMustIn.marginsRemoved ( m_margins );
#endif
    QPoint cursorPos = event->pos();//QCursor::pos();
#endif

    //但是，上边的不严谨，只能用于小小的领域，必须是root窗口才行，子窗口不行。
    //以下代码对此进行纠正。
    //应用于子窗口和root窗口的通用代码

#if 1
    //maptoGlobal(rect()) 与 globalPos 对比
    QRect rectMustIn = QRect ( target->mapToGlobal ( target->rect().topLeft() ),
                               target->mapToGlobal ( target->rect().bottomRight() ) );
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QRect rectMustNotIn = rectMustIn.adjusted ( m_margins.left(), m_margins.top(), m_margins.right(), m_margins.bottom() );
#else
    QRect rectMustNotIn = rectMustIn.marginsRemoved ( m_margins );
#endif
    QPoint cursorPos = event->globalPos();
    //经过测试，这种方法，在子窗口、root窗口，得到的数据完全正常。
    //pline() << target->geometry() << rectMustIn
    //        << rectMustIn.contains ( event->globalPos() ) << rectMustNotIn.contains ( event->globalPos() );
#endif

    if ( target->isMaximized() ||
         !target->isActiveWindow() ||
         !rectMustIn.contains ( cursorPos ) ||
         rectMustNotIn.contains ( cursorPos ) )
    {
        direction = None;
        target->unsetCursor();
        event->ignore();
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
            target->setCursor ( Qt::SizeHorCursor );
            break;

        case Top:
        case Bottom:
            target->setCursor ( Qt::SizeVerCursor );
            break;

        case LeftTop:
        case RightBottom:
            target->setCursor ( Qt::SizeFDiagCursor );
            break;

        case LeftBottom:
        case RightTop:
            target->setCursor ( Qt::SizeBDiagCursor );
            break;

        default:
            break;
    }

}
