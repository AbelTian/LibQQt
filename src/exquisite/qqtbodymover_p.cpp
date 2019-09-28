#include "qqtbodymover_p.h"
#include "qqtbodymover.h"

#include <QWidget>
#include <QMouseEvent>
#ifdef Q_OS_WIN
//#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

QQtBodyMoverPrivate::QQtBodyMoverPrivate ( QQtBodyMover* q )
{
    q_ptr = q;
    bMousePressed = false;
}

QQtBodyMoverPrivate::~QQtBodyMoverPrivate()
{
}

void QQtBodyMoverPrivate::mousePressEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );

    QMargins m_margins = target->contentsMargins();
    //以下代码用来过滤边缘的margin。
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

    //这里必须用target->window()，这代表root窗口。
    QWidget* win = target->window();

    if ( win->isMaximized() ||
         !win->isActiveWindow() ||
         !rectMustIn.contains ( cursorPos ) ||
         !rectMustNotIn.contains ( cursorPos ) )
    {
        event->ignore();
        return;
    }

#ifdef __DESKTOP_WIN__
    if ( ReleaseCapture() )
    {
        QWidget* pWindow = target->window();
        if ( 1 )
        {
            //SC_MOVE 移动命令
            //HTCAPTION 捕获鼠标命令，否则，会跑到标题栏上去。
            SendMessage ( HWND ( pWindow->winId() ), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0 );
        }
    }
    event->accept();
#else
    if ( event->button() == Qt::LeftButton )
    {
        bMousePressed = true;
        pressedPoint = event->globalPos();
    }
    event->accept();
#endif
}

void QQtBodyMoverPrivate::mouseReleaseEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );
#ifdef __DESKTOP_WIN__
#else
    bMousePressed = false;
    event->accept();
#endif
}

void QQtBodyMoverPrivate::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );
#ifdef __DESKTOP_WIN__
#else
    QWidget* win = target->window();
    if ( bMousePressed && !win->isMaximized() )
    {
        QPoint movePoint = event->globalPos() - pressedPoint;
        QPoint widgetPos = win->pos();
        pressedPoint = event->globalPos();
        win->move ( widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y() );
    }
    event->accept();
#endif
}

