#include "qqtmouselocker_win.h"

#include <QEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <qqtcore.h>

#include <windows.h>
#include <windef.h>
#include <winuser.h>

QQtMouseLockerImpl::QQtMouseLockerImpl() {}

void QQtMouseLockerImpl::focusInEvent ( QFocusEvent* event, QWidget* target )
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
            //BUG, NEED MOD!
            ClipCursor ( NULL );
            ClipCursor ( &mainWinRect ); //这是Windows API
#if 1
            pline() << "focus in-----------------------";
            pline() << "client:" << w.geometry();
            pline() << "to screen:" << qr0;
            pline() << "old:" << r0.left << r0.top << r0.right - r0.left << r0.bottom - r0.top;
            pline() << "new:" << mainWinRect.left << mainWinRect.top << mainWinRect.right - mainWinRect.left << mainWinRect.bottom - mainWinRect.top;
#endif
        }
    }
    event->accept();

}

void QQtMouseLockerImpl::focusOutEvent ( QFocusEvent* event, QWidget* target )
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
            ClipCursor ( NULL );
#if 1
            pline() << "focus out-----------------------";
            pline() << "client:" << w.geometry();
            pline() << "to screen:" << qr0;
            pline() << "old:" << r0.left << r0.top << r0.right - r0.left << r0.bottom - r0.top;
            GetClipCursor ( &r0 );
            pline() << "new:" << r0.left << r0.top << r0.right - r0.left << r0.bottom - r0.top;
#endif
        }
    }
    event->accept();

}

void QQtMouseLockerImpl::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
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

        qreal ratio = w.devicePixelRatioF();

        QRect r0 = QRect ( p0, p1 );
        mainWinRect.left = ( LONG ) r0.left() * ratio;
        mainWinRect.right = ( LONG ) r0.right() * ratio;
        mainWinRect.top = ( LONG ) r0.top() * ratio;
        mainWinRect.bottom = ( LONG ) r0.bottom() * ratio;

        qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ), QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );
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
            ClipCursor ( NULL );
            ClipCursor ( &mainWinRect ); //这是Windows API
#if 1
            pline() << "mouse move-----------------------";
            pline() << "client:" << w.geometry();
            pline() << "to screen:" << qr0;
            pline() << "old:" << r0.left << r0.top << r0.right - r0.left << r0.bottom - r0.top;
            pline() << "new:" << mainWinRect.left << mainWinRect.top << mainWinRect.right - mainWinRect.left << mainWinRect.bottom - mainWinRect.top;
#endif
        }
    }
    event->accept();
    return;
}
