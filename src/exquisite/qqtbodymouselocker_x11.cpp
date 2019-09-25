#include <qqtbodymouselocker_x11.h>
#include "qqtbodymouselocker.h"

#include <QWidget>

#include <qqtcore.h>

#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>


void simulate_mouse ( int fd, int rel_x, int rel_y )
{
    struct input_event event, ev;
    gettimeofday ( &event.time, 0 );
    //x轴坐标的相对位移
    event.type = EV_REL;
    event.value = rel_x;
    event.code = REL_X;
    write ( fd, &event, sizeof ( event ) );
    //y轴坐标的相对位移
    event.type = EV_REL;
    event.value = rel_y;
    event.code = REL_Y;
    write ( fd, &event, sizeof ( event ) );
    //同步
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write ( fd, &event, sizeof ( event ) );
}

//system c api
//打不开设备 没权限 感觉
void set_mouse_pos ( int x, int y )
{
    int fd_mouse = open ( "/dev/input/mice", O_RDWR );

    //打都打不开！！！
    if ( fd_mouse < 0 )
        qDebug ( "error \n" );

    simulate_mouse ( fd_mouse, x, y );

    close ( fd_mouse );
}

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Display* display;
Window root;

//初始化
void init()
{
    if ( ( display = XOpenDisplay ( NULL ) ) == NULL )
    {
        fprintf ( stderr, "Cannot open local X-display.\n" );
        return;
    }
    root = DefaultRootWindow ( display );
}

void deinit()
{
    XCloseDisplay ( display );
}

void GetCursorPos ( int* x, int* y )
{
    int tmp; unsigned int tmp2;
    Window fromroot, tmpwin;
    XQueryPointer ( display, root, &fromroot, &tmpwin, x, y, &tmp, &tmp, &tmp2 );
}

//跟QCursor行为一致，消息其实已经有效了，可是，鼠标没动作。手动移动的时候还是在没移动的那位置。
//我用xdotool测试了一下，也不管用，是因为在虚拟机里吗？
//设置坐标
void SetCursorPos ( int x, int y )
{
    int tmp;
    XWarpPointer ( display, None, root, 0, 0, 0, 0, x, y );
    //这两个函数都不管用。
    XFlush ( display );
    //XSync ( display, True );
}

//没用的测试
void mouseClick ( int button )
{
    Display* display = XOpenDisplay ( NULL );

    XEvent event;

    if ( display == NULL )
    {
        printf ( "Errore nell'apertura del Display !!!\n" );
        return;
    }

    memset ( &event, 0x00, sizeof ( event ) );

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer ( display, RootWindow ( display, DefaultScreen ( display ) ), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x,
                    &event.xbutton.y, &event.xbutton.state );

    event.xbutton.subwindow = event.xbutton.window;

    while ( event.xbutton.subwindow )
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer ( display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state );
    }

    if ( XSendEvent ( display, PointerWindow, True, 0xfff, &event ) == 0 ) printf ( "Errore nell'invio dell'evento !!!\n" );

    XFlush ( display );

    sleep ( 1 );

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if ( XSendEvent ( display, PointerWindow, True, 0xfff, &event ) == 0 ) printf ( "Errore nell'invio dell'evento !!!\n" );

    XFlush ( display );

    XCloseDisplay ( display );
}

void QQtSetCursorPos ( int x, int y )
{
    XEvent event;
    memset ( &event, 0x00, sizeof ( event ) );
    event.type = PointerMotionMask;
}

/**
 * @brief 以下为我方代码
 */

QQtBodyMouseMouseLockerThreadHelper::QQtBodyMouseMouseLockerThreadHelper ( QObject* parent ) : QThread ( parent )
{
    init();
    workflag = false;
    mGlobalRect = QRect ( 0, 0, 0, 0 );
    startCapture();
}

QQtBodyMouseMouseLockerThreadHelper::~QQtBodyMouseMouseLockerThreadHelper()
{
    stopCapture();
    deinit();
}

void QQtBodyMouseMouseLockerThreadHelper::setTargetGlobalRect ( QRect globalRect )
{
    tex.lock();
    mGlobalRect = globalRect;
    tex.unlock();
}

QRect QQtBodyMouseMouseLockerThreadHelper::getTargetGlobalRect()
{
    return mGlobalRect;
}

void QQtBodyMouseMouseLockerThreadHelper::startCapture()
{
    tex.lock();
    workflag = true;
    tex.unlock();
    start();
}

void QQtBodyMouseMouseLockerThreadHelper::stopCapture()
{
    tex.lock();
    workflag = false;
    tex.unlock();
    quit();
    wait();
}

void QQtBodyMouseMouseLockerThreadHelper::run()
{
    while ( 1 )
    {
        //usleep ( 10 );
        msleep ( 1000 );

        tex.lock();
        bool lworkflag = workflag;
        tex.unlock();
        if ( !lworkflag )
            return;

        QRect globalRect;
        tex.lock();
        globalRect = this->mGlobalRect;
        tex.unlock();

        if ( globalRect == QRect ( 0, 0, 0, 0 ) )
            continue;

        QRect s = globalRect;

        int x = QCursor::pos().x();
        int y = QCursor::pos().y();

        int x1 = x, y1 = y;
        if ( x <= s.left() )
            x1 = s.left();
        if ( y <= s.top() )
            y1 = s.top();
        if ( x >= s.right() )
            x1 = s.right();
        if ( y >= s.bottom() )
            y1 = s.bottom();

        //QCursor::setPos ( x1, y1 );
        SetCursorPos ( x1, y1 );

        int x2, y2;
        GetCursorPos ( &x2, &y2 );

        pline() << x << y << x1 << y1 << x2 << y2;
    }
}

QQtBodyMouseLockerPrivate::QQtBodyMouseLockerPrivate ( QQtBodyMouseLocker* q )
{
    q_ptr = q;
    helper = QQtBodyMouseMouseLockerThreadHelper::instance ( q );
}

QQtBodyMouseLockerPrivate::~QQtBodyMouseLockerPrivate()
{
}

void QQtBodyMouseLockerPrivate::addRect ( const QRect globalRect )
{
    helper->setTargetGlobalRect ( globalRect );
}

QRect QQtBodyMouseLockerPrivate::getRect()
{
    return helper->getTargetGlobalRect();
}

void QQtBodyMouseLockerPrivate::startCapture()
{
    helper->startCapture();
}

void QQtBodyMouseLockerPrivate::stopCapture()
{
    helper->stopCapture();
}

void QQtBodyMouseLockerPrivate::addWindow ( QWidget* target )
{
    //把margin过滤掉，
    QRect rectMustNotIn = getTargetRect ( target );

    //设置需要锁定的rect
    helper->setTargetGlobalRect ( rectMustNotIn );
}

QRect QQtBodyMouseLockerPrivate::getTargetRect ( QWidget* target )
{
    Q_ASSERT ( target );

    QWidget& w = *target;

    QPoint p0, p1;
    p0 = w.rect().topLeft();
    p1 = w.rect().bottomRight();
    p0 = w.mapToGlobal ( p0 );
    p1 = w.mapToGlobal ( p1 );

    qreal ratio = 1; //w.devicePixelRatioF(); 这个在Unix系统里没有用。在armhf里编译不过。
    QRect r0 = QRect ( p0, p1 );
    QRect qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ),
                        QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );

    QMargins m_margins = w.contentsMargins();
    QRect rectMustIn = qr0;
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QRect rectMustNotIn = rectMustIn.adjusted ( m_margins.left(), m_margins.top(), m_margins.right(), m_margins.bottom() );
#else
    QRect rectMustNotIn = rectMustIn.marginsRemoved ( m_margins );
#endif

    return rectMustNotIn;
}

QRect QQtBodyMouseLockerPrivate::getSourceRect ( QWidget* target )
{
    QWidget& w = *target;
    QPoint p0, p1;
    p0 = w.rect().topLeft();
    p1 = w.rect().bottomRight();
    p0 = w.mapToGlobal ( p0 );
    p1 = w.mapToGlobal ( p1 );
    QRect r0 = QRect ( p0, p1 );

    qreal ratio = 1; //w.devicePixelRatioF(); 这个在Unix系统里没有用。在armhf里编译不过。
    QRect qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ), QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );
    return qr0;
}

void QQtClipCursor ( const QRect globalRect )
{
    QQtBodyMouseMouseLockerThreadHelper::instance()->setTargetGlobalRect ( globalRect );
}

QRect QQtGetClipCursor()
{
    return QQtBodyMouseMouseLockerThreadHelper::instance()->getTargetGlobalRect();
}

void QQtClipCursorToWindow ( QWidget* target )
{
    QRect globalRect = QQtBodyMouseLockerPrivate::getTargetRect ( target );
    QQtClipCursor ( globalRect );
}
