#include <qqtrootbodymover.h>


#include <QWidget>
#include <QMouseEvent>

QQtRootBodyMover::QQtRootBodyMover ( QObject* parent ) : QObject ( parent )
{
    bMousePressed = false;
}

QQtRootBodyMover::~QQtRootBodyMover() {}

void QQtRootBodyMover::mousePressEvent ( QMouseEvent* event, QWidget* target )
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

void QQtRootBodyMover::mouseReleaseEvent ( QMouseEvent* event, QWidget* target )
{
    Q_ASSERT ( target );
#ifdef __DESKTOP_WIN__
#else
    bMousePressed = false;
    event->accept();
#endif
}

void QQtRootBodyMover::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
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


bool QQtRootBodyMover::eventFilter ( QObject* watched, QEvent* event )
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
