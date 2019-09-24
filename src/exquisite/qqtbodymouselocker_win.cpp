#include "qqtbodymouselocker_win.h"
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <qqtcore.h>

#include <windows.h>
#include <windef.h>
#include <winuser.h>

QQtBodyMouseLockerPrivate::QQtBodyMouseLockerPrivate ( QQtBodyMouseLocker* q )
{
    q_ptr = q;
}

QQtBodyMouseLockerPrivate::~QQtBodyMouseLockerPrivate()
{

}

void QQtBodyMouseLockerPrivate::addRect ( const QRect globalRect )
{
    RECT mainWinRect; //RECT在windef.h中被定义
    mainWinRect.left = ( LONG ) globalRect.left();
    mainWinRect.right = ( LONG ) globalRect.right();
    mainWinRect.top = ( LONG ) globalRect.top();
    mainWinRect.bottom = ( LONG ) globalRect.bottom();

    //pline() << globalRect;
    if ( globalRect == QRect ( 0, 0, 0, 0 ) )
    {
        ClipCursor ( NULL );
        return;
    }
    ClipCursor ( NULL );
    ClipCursor ( &mainWinRect ); //这是Windows API
}

QRect QQtBodyMouseLockerPrivate::getRect()
{
    QRect qr0 = QRect ( 0, 0, 0, 0 );
    RECT r0;
    if ( GetClipCursor ( &r0 ) )
    {
        qr0 = QRect ( QPoint ( r0.left, r0.top ), QPoint ( r0.right, r0.bottom ) );
    }
    bool ret = GetClipCursor ( &r0 );
    //pline() << qr0 << ret;
    return qr0;
}

void QQtBodyMouseLockerPrivate::addWindow ( QWidget* target )
{
    //把margin过滤掉，
    QRect rectMustNotIn = getTargetRect ( target );
    addRect ( rectMustNotIn );
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

    qreal ratio = w.devicePixelRatioF();
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

    qreal ratio = w.devicePixelRatioF();
    QRect qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ), QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );
    return qr0;
}

void QQtBodyMouseLockerPrivate::startCapture()
{

}

void QQtBodyMouseLockerPrivate::stopCapture()
{

}


void QQtClipCursor ( const QRect globalRect )
{
    RECT mainWinRect; //RECT在windef.h中被定义
    mainWinRect.left = ( LONG ) globalRect.left();
    mainWinRect.right = ( LONG ) globalRect.right();
    mainWinRect.top = ( LONG ) globalRect.top();
    mainWinRect.bottom = ( LONG ) globalRect.bottom();
    if ( globalRect == QRect ( 0, 0, 0, 0 ) )
    {
        ClipCursor ( NULL );
        return;
    }
    ClipCursor ( NULL );
    ClipCursor ( &mainWinRect ); //这是Windows API
}

QRect QQtGetClipCursor()
{
    QRect qr0 = QRect ( 0, 0, 0, 0 );
    RECT r0;
    if ( GetClipCursor ( &r0 ) )
    {
        qr0 = QRect ( QPoint ( r0.left, r0.top ), QPoint ( r0.right, r0.bottom ) );
    }
    return qr0;
}

void QQtClipCursorToWindow ( QWidget* target )
{
    QRect globalRect = QQtBodyMouseLockerPrivate::getTargetRect ( target );
    QQtClipCursor ( globalRect );
}
