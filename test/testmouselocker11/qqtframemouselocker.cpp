#include <qqtframemouselocker.h>

#include <QEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <qqtcore.h>

#ifdef Q_OS_WIN
#include <windows.h>
#include <windef.h>
#include <winuser.h>
#else
#endif

QQtFrameMouseLocker::QQtFrameMouseLocker ( QObject* parent ) : QObject ( parent )
{

}

QQtFrameMouseLocker::~QQtFrameMouseLocker()
{

}

#ifdef Q_OS_WIN
void QQtFrameMouseLocker::focusInEvent ( QFocusEvent* event, QWidget* target )
{
    if ( target == 0 )
    {
        event->ignore();
        return ;
    }

    if ( !target->isActiveWindow() )
    {
        event->ignore();
        return;
    }

    QWidget& w = *target;

    //clip
    RECT mainWinRect; //RECT在windef.h中被定义
    //print
    QRect qr0;

    //client rect
    mainWinRect.left = ( LONG ) w.geometry().left();
    mainWinRect.right = ( LONG ) w.geometry().right();
    mainWinRect.top = ( LONG ) w.geometry().top();
    mainWinRect.bottom = ( LONG ) w.geometry().bottom();
    qr0 = w.geometry();

#if 1
    {
        QPoint p0, p1;
        p0 = w.geometry().topLeft();
        p1 = w.geometry().bottomRight();
        p0 = w.mapToGlobal ( p0 );
        p1 = w.mapToGlobal ( p1 );

        QRect r0 = QRect ( p0, p1 );
        mainWinRect.left = ( LONG ) r0.left();
        mainWinRect.right = ( LONG ) r0.right();
        mainWinRect.top = ( LONG ) r0.top();
        mainWinRect.bottom = ( LONG ) r0.bottom();

        qr0 = r0;
    }
#endif

    RECT r0;
    bool ret = GetClipCursor ( &r0 );
    if ( ret == false )
        pline() << "ret is false.";
    if ( GetClipCursor ( &r0 ) )
    {
        if ( r0.left != mainWinRect.left
             && r0.right != mainWinRect.right
             && r0.top !=  mainWinRect.top
             && r0.bottom != mainWinRect.bottom )
        {
            pline() << "focus in-----------------------";
            pline() << "client:" << w.geometry();
            pline() << "to screen:" << qr0;
            pline() << "old:" << r0.left << r0.top << r0.right - r0.left << r0.bottom - r0.top;
            ClipCursor ( NULL );
            ClipCursor ( &mainWinRect ); //这是Windows API
            pline() << "new:" << mainWinRect.left << mainWinRect.top << mainWinRect.right - mainWinRect.left << mainWinRect.bottom - mainWinRect.top;
        }
    }
    event->accept();

}

void QQtFrameMouseLocker::focusOutEvent ( QFocusEvent* event, QWidget* target )
{
    if ( target == 0 )
    {
        event->ignore();
        return ;
    }

    //if ( !target->isActiveWindow() )
    //{
    //    event->ignore();
    //    return;
    //}

    QWidget& w = *target;

    //clip
    RECT mainWinRect; //RECT在windef.h中被定义
    //print
    QRect qr0;

    //client rect
    mainWinRect.left = ( LONG ) w.geometry().left();
    mainWinRect.right = ( LONG ) w.geometry().right();
    mainWinRect.top = ( LONG ) w.geometry().top();
    mainWinRect.bottom = ( LONG ) w.geometry().bottom();
    qr0 = w.geometry();

#if 1
    {
        QPoint p0, p1;
        p0 = w.geometry().topLeft();
        p1 = w.geometry().bottomRight();
        p0 = w.mapToGlobal ( p0 );
        p1 = w.mapToGlobal ( p1 );

        QRect r0 = QRect ( p0, p1 );
        mainWinRect.left = ( LONG ) r0.left();
        mainWinRect.right = ( LONG ) r0.right();
        mainWinRect.top = ( LONG ) r0.top();
        mainWinRect.bottom = ( LONG ) r0.bottom();

        qr0 = r0;
    }
#endif

    RECT r0;
    bool ret = GetClipCursor ( &r0 );
    if ( ret == false )
        pline() << "ret is false.";
    if ( GetClipCursor ( &r0 ) )
    {
        if ( r0.left == mainWinRect.left
             && r0.right == mainWinRect.right
             && r0.top ==  mainWinRect.top
             && r0.bottom == mainWinRect.bottom )
        {
            pline() << "focus out-----------------------";
            pline() << "client:" << w.geometry();
            pline() << "to screen:" << qr0;
            pline() << "old:" << r0.left << r0.top << r0.right - r0.left << r0.bottom - r0.top;
            ClipCursor ( NULL );
            GetClipCursor ( &r0 );
            pline() << "new:" << r0.left << r0.top << r0.right - r0.left << r0.bottom - r0.top;
        }
    }
    event->accept();

}

void QQtFrameMouseLocker::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    if ( target == 0 )
    {
        event->ignore();
        return ;
    }

    if ( !target->isActiveWindow() )
    {
        event->ignore();
        return;
    }

    QWidget& w = *target;

    //clip
    RECT mainWinRect; //RECT在windef.h中被定义
    //print
    QRect qr0;

    //client rect
    mainWinRect.left = ( LONG ) w.geometry().left();
    mainWinRect.right = ( LONG ) w.geometry().right();
    mainWinRect.top = ( LONG ) w.geometry().top();
    mainWinRect.bottom = ( LONG ) w.geometry().bottom();
    qr0 = w.geometry();

#if 1
    {
        QPoint p0, p1;
        p0 = w.geometry().topLeft();
        p1 = w.geometry().bottomRight();
        p0 = w.mapToGlobal ( p0 );
        p1 = w.mapToGlobal ( p1 );

        QRect r0 = QRect ( p0, p1 );
        mainWinRect.left = ( LONG ) r0.left();
        mainWinRect.right = ( LONG ) r0.right();
        mainWinRect.top = ( LONG ) r0.top();
        mainWinRect.bottom = ( LONG ) r0.bottom();

        qr0 = r0;
    }
#endif

    RECT r0;
    bool ret = GetClipCursor ( &r0 );
    if ( ret == false )
        pline() << "ret is false.";
    if ( GetClipCursor ( &r0 ) )
    {
        if ( r0.left != mainWinRect.left
             && r0.right != mainWinRect.right
             && r0.top !=  mainWinRect.top
             && r0.bottom != mainWinRect.bottom )
        {
            pline() << "mouse move-----------------------";
            pline() << "client:" << w.geometry();
            pline() << "to screen:" << qr0;
            pline() << "old:" << r0.left << r0.top << r0.right - r0.left << r0.bottom - r0.top;
            ClipCursor ( NULL );
            ClipCursor ( &mainWinRect ); //这是Windows API
            pline() << "new:" << mainWinRect.left << mainWinRect.top << mainWinRect.right - mainWinRect.left << mainWinRect.bottom - mainWinRect.top;
        }
    }
    event->accept();

}
#else
void QQtFrameMouseLocker::focusInEvent ( QFocusEvent* event, QWidget* target )
{

}

void QQtFrameMouseLocker::focusOutEvent ( QFocusEvent* event, QWidget* target )
{

}

void QQtFrameMouseLocker::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    if ( target == 0 )
    {
        event->ignore();
        return ;
    }

    if ( !target->isActiveWindow() )
    {
        event->ignore();
        return;
    }

    QWidget& w = *target;

    QPoint p0, p1;
    p0 = w.geometry().topLeft();
    p1 = w.geometry().bottomRight();
    p0 = w.mapToGlobal ( p0 );
    p1 = w.mapToGlobal ( p1 );
    QRect r0 = QRect ( p0, p1 );
    QRect s = r0;


    int x = event->globalX();
    int y = event->globalY();

    int x1 = x, y1 = y;
    if ( x < s.left() )
        x1 = s.left(), y1 = y;
    if ( y < s.top() )
        x1 = x, y1 = s.top();
    if ( x > s.right() )
        x1 = s.right(), y1 = y;
    if ( y > s.bottom() )
        x1 = x, y1 = s.bottom();

    pline() << x1 << y1;
    QCursor::setPos ( x1, y1 );
    event->accept();
}
#endif

bool QQtFrameMouseLocker::eventFilter ( QObject* watched, QEvent* event )
{
    if ( !watched->inherits ( "QWidget" ) )
        return QObject::eventFilter ( watched, event );

    switch ( event->type() )
    {
        //这两个有个bug，
        //FocusIn有bug，当从外部接触内部标题栏，FocusIN激发，鼠标摁住移动窗口只能在一个小范围移动。必须重新摁一次才能整体移动。
        //我的处理办法是，屏蔽掉这两个，已经满足要求，不必要这两个函数。
        //case QEvent::FocusIn:
        //{
        //    QFocusEvent* e = ( QFocusEvent* ) event;
        //    focusInEvent ( e, ( QWidget* ) watched );
        //    return true;
        //}
        //case QEvent::FocusOut:
        //{
        //    QFocusEvent* e = ( QFocusEvent* ) event;
        //    focusOutEvent ( e, ( QWidget* ) watched );
        //    return true;
        //}
        case QEvent::MouseMove:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            mouseMoveEvent ( e, ( QWidget* ) watched );
            return true;
        }
        default:
            break;
    }

    return QObject::eventFilter ( watched, event );
}

