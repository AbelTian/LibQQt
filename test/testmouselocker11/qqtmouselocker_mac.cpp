#include "qqtmouselocker_mac.h"

#include <QEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <qqtcore.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreGraphics/CGDisplayConfiguration.h>


//新方法，开启一个线程，
//while使用系统API实时检测鼠标位置，一单移动到rect以外，立即setPOS在边缘
//这个while可是很快吆。
//比mouseEvent快，比Timer快。

//三个平台上，行为应当表现一致

//1. 在activeWindow，马上clipcursor；
//2. installEvent，start，保持clipcursor，stop，停止clipcursor。removeEventFilter以前必须调用关闭！

//我感觉，调用形式可能要变？

//允许多个窗口公用
//允许开启多个句柄

//start/stop 帮助开启和关闭eventFilter。
//跟着rect改变clipcursor的范围

//选中的style1 style2 Qt、四角。

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
    p0 = w.rect().topLeft();
    p1 = w.rect().bottomRight();
    p0 = w.mapToGlobal ( p0 );
    p1 = w.mapToGlobal ( p1 );
    QRect s = QRect ( p0, p1 );

    int x = event->globalX();
    int y = event->globalY();

    int x1 = x, y1 = y;
    //带上=也没有用，还是抖动。
    if ( x <= s.left() )
        x1 = s.left();
    if ( y <= s.top() )
        y1 = s.top();
    if ( x >= s.right() )
        x1 = s.right();
    if ( y >= s.bottom() )
        y1 = s.bottom();
    pline() << x1 << y1 << s.top() << s.bottom() << s.left() << s.right();

#if 0
    //抖动，只有按下才会锁定。
    QCursor::setPos ( x1, y1 );
#elif 0
    //无论是否注释，都存在严重的抖动。只有按下才会锁定。
    CGAssociateMouseAndMouseCursorPosition ( false );
    CGPoint mouseWarpLocation = CGPointMake ( x1, y1 );
    CGWarpMouseCursorPosition ( mouseWarpLocation );
    CGAssociateMouseAndMouseCursorPosition ( true );
#elif 0
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

QQtLockMouseThreadHelper::QQtLockMouseThreadHelper ( QObject* parent ) : QThread ( parent ) {}

QQtLockMouseThreadHelper::~QQtLockMouseThreadHelper() {}

void QQtLockMouseThreadHelper::run()
{
}
