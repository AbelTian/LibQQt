#include "qqtmouselocker_mac.h"

#include <QEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <qqtcore.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreGraphics/CGDisplayConfiguration.h>

QQtMouseLockerImpl::QQtMouseLockerImpl() {}

void QQtMouseLockerImpl::focusInEvent ( QFocusEvent* event, QWidget* target )
{

}

void QQtMouseLockerImpl::focusOutEvent ( QFocusEvent* event, QWidget* target )
{

}

void QQtMouseLockerImpl::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    if ( target == 0 )
    {
        event->ignore();
        return;
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
    QRect s = QRect ( p0, p1 );

    int x = event->globalX();
    int y = event->globalY();

    int x1 = x, y1 = y;
    //带上=也没有用，还是抖动。
    if ( x <= s.left() )
        x1 = s.left(), y1 = y;
    if ( y <= s.top() )
        x1 = x, y1 = s.top();
    if ( x >= s.right() )
        x1 = s.right(), y1 = y;
    if ( y >= s.bottom() )
        x1 = x, y1 = s.bottom();
    pline() << x1 << y1;

#if 0
    //抖动，只有按下才会锁定。
    QCursor::setPos ( x1, y1 );
#elif 0
    //无论是否注释，都存在严重的抖动。只有按下才会锁定。
    CGAssociateMouseAndMouseCursorPosition ( false );
    CGPoint mouseWarpLocation = CGPointMake ( x1, y1 );
    CGWarpMouseCursorPosition ( mouseWarpLocation );
    CGAssociateMouseAndMouseCursorPosition ( true );
#elif 1
    //还是抖动。只有按下才会锁定。
    CGEventSourceRef evsrc = CGEventSourceCreate ( kCGEventSourceStateCombinedSessionState );
    CGEventSourceSetLocalEventsSuppressionInterval ( evsrc, 0.0 );
    CGAssociateMouseAndMouseCursorPosition ( false );
    CGPoint mouseWarpLocation = CGPointMake ( x1, y1 );
    CGWarpMouseCursorPosition ( mouseWarpLocation );
    CGAssociateMouseAndMouseCursorPosition ( true );
    CFRelease ( evsrc );
#endif

    event->accept();
}
