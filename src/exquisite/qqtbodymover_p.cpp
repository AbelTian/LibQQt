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
}

QQtBodyMoverPrivate::~QQtBodyMoverPrivate()
{
}

void QQtBodyMoverPrivate::mousePressEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );

#ifdef Q_OS_WIN
    if ( ReleaseCapture() )
    {
        QWidget* pWindow = target->window();
        if ( pWindow->isTopLevel() )
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
#ifdef Q_OS_WIN
#else
    bMousePressed = false;
    event->accept();
#endif
}

void QQtBodyMoverPrivate::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );
#ifdef Q_OS_WIN
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
