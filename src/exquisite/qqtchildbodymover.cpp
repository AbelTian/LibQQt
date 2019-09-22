#include <qqtchildbodymover.h>

QQtChildBodyMover::QQtChildBodyMover ( QObject* parent ) : QObject ( parent )
{
    bMousePressed = false;
    m_margins = QMargins ( 10, 10, 10, 10 );

}

QQtChildBodyMover::~QQtChildBodyMover() {}

QMargins& QQtChildBodyMover::margins()
{
    return m_margins;
}

void QQtChildBodyMover::mousePressEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );

    //以下代码用来过滤边缘的margin。
#if 1
    //maptoGlobal(rect()) 与 globalPos 对比
    QRect rectMustIn = QRect ( target->mapToGlobal ( target->rect().topLeft() ), target->mapToGlobal ( target->rect().bottomRight() ) );
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
         !rectMustNotIn.contains ( cursorPos ) )
    {
        event->ignore();
        return;
    }

    if ( event->button() == Qt::LeftButton )
    {
        bMousePressed = true;
        pressedPoint = event->globalPos();
    }
    event->accept();
}

void QQtChildBodyMover::mouseReleaseEvent ( QMouseEvent* event, QWidget* target )
{
    bMousePressed = false;
    event->accept();
}

void QQtChildBodyMover::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );

    QWidget* win = target->window();
    if ( bMousePressed && !win->isMaximized() )
    {
        QPoint p1 = event->globalPos();
        QPoint pxy = p1 - pressedPoint;
        pressedPoint = p1;

        QPoint p0 = target->geometry().topLeft();
        QPoint p2 = p0 + pxy;
        target->move ( p2 );
    }
    event->accept();
}


bool QQtChildBodyMover::eventFilter ( QObject* watched, QEvent* event )
{
    //过滤掉不是QWidget
    if ( !watched->inherits ( "QWidget" ) )
        return QObject::eventFilter ( watched, event );

    //修复 paint bug
    /*fix the parent handled bug terminally*/
    if ( event->type() == QEvent::Paint )
        return QObject::eventFilter ( watched, event );

    //修复鼠标穿透。
    bool atti = ( qobject_cast<QWidget*> ( watched ) )->testAttribute ( Qt::WA_TransparentForMouseEvents );
    if ( atti )
        return QObject::eventFilter ( watched, event );

    switch ( event->type() )
    {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            mousePressEvent ( e, qobject_cast<QWidget*> ( watched ) );
            return false;
        }
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            mouseReleaseEvent ( e, qobject_cast<QWidget*> ( watched ) );
            return false;
        }
        case QEvent::MouseMove:
        {
            QMouseEvent* e = ( QMouseEvent* ) event;
            mouseMoveEvent ( e, qobject_cast<QWidget*> ( watched ) );
            return false;
        }
        default:
            break;
    }

    return QObject::eventFilter ( watched, event );
}
