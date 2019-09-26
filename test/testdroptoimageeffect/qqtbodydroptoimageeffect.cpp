#include <qqtbodydroptoimageeffect.h>

#include <QEvent>
#include <QPainter>
#include <QWidget>

#include <qqtcore.h>

QQtBodyDropImageEffect::QQtBodyDropImageEffect ( QObject* parent ) : QObject ( parent )
{

}

QQtBodyDropImageEffect::~QQtBodyDropImageEffect() {}


bool QQtBodyDropImageEffect::eventFilter ( QObject* watched, QEvent* event )
{
    if ( !watched->inherits ( "QWidget" ) )
        return QObject::eventFilter ( watched, event );

    //修复鼠标穿透。鼠标穿透没有效果
    bool atti = ( qobject_cast<QWidget*> ( watched ) )->testAttribute ( Qt::WA_TransparentForMouseEvents );
    if ( atti )
        return QObject::eventFilter ( watched, event );

    if ( event->type() == QEvent::Paint )
        return QObject::eventFilter ( watched, event );

    if ( event->type() == QEvent::MouseMove )
        return QObject::eventFilter ( watched, event );

    static int i = 0;
    p2line() << i++ << watched->objectName() << event->type() ;

    switch ( event->type() )
    {
        case QEvent::DragEnter:
        {
            QWidget* target = qobject_cast<QWidget*> ( watched );
            QWidget& w = *target;

            QRect rectMustIn = QRect ( w.mapToGlobal ( w.rect().topLeft() ), w.mapToGlobal ( w.rect().bottomRight() ) );//srcR0
            QMargins m_margins = w.contentsMargins();
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
            QRect rectMustNotIn = rectMustIn.adjusted ( m_margins.left(), m_margins.top(), m_margins.right(), m_margins.bottom() );
#else
            QRect rectMustNotIn = rectMustIn.marginsRemoved ( m_margins );
#endif
            QPoint cursorPos = QCursor::pos();//globalPos

            //在content里面才能响应 [比较的时候不放大坐标，调试出来的]
            if ( rectMustIn.contains ( cursorPos ) && rectMustNotIn.contains ( cursorPos ) )
            {
                QDragEnterEvent* e = ( QDragEnterEvent* ) event;
                p2line() << e->answerRect();
                //p2line() << e->dropAction();
                p2line() << e->spontaneous();
                p2line() << e->source()->objectName();
                p2line() << e->mimeData()->formats() << e->mimeData()->urls();
                p2line() << e->possibleActions() << e->proposedAction();
            }

            event->accept();
            return false;
        }
        break;
        case QEvent::DragLeave:
        {
            QWidget* target = qobject_cast<QWidget*> ( watched );
            QWidget& w = *target;

            if ( !target->isActiveWindow() )
            {
                event->ignore();
                return false;
            }

            QRect rectMustIn = QRect ( w.mapToGlobal ( w.rect().topLeft() ), w.mapToGlobal ( w.rect().bottomRight() ) );//srcR0
            QMargins m_margins = w.contentsMargins();
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
            QRect rectMustNotIn = rectMustIn.adjusted ( m_margins.left(), m_margins.top(), m_margins.right(), m_margins.bottom() );
#else
            QRect rectMustNotIn = rectMustIn.marginsRemoved ( m_margins );
#endif
            QPoint cursorPos = QCursor::pos();//globalPos

            //在content里面才能响应 [比较的时候不放大坐标，调试出来的]
            if ( rectMustIn.contains ( cursorPos ) && rectMustNotIn.contains ( cursorPos ) )
            {
                QDragLeaveEvent* e = ( QDragLeaveEvent* ) event;
                p2line() << e->spontaneous();
            }

            event->accept();
            return false;
        }
        break;
        case QEvent::Drop:
        {
            QWidget* target = qobject_cast<QWidget*> ( watched );
            QWidget& w = *target;

            if ( !target->isActiveWindow() )
            {
                event->ignore();
                return false;
            }

            QRect rectMustIn = QRect ( w.mapToGlobal ( w.rect().topLeft() ), w.mapToGlobal ( w.rect().bottomRight() ) );//srcR0
            QMargins m_margins = w.contentsMargins();
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
            QRect rectMustNotIn = rectMustIn.adjusted ( m_margins.left(), m_margins.top(), m_margins.right(), m_margins.bottom() );
#else
            QRect rectMustNotIn = rectMustIn.marginsRemoved ( m_margins );
#endif
            QPoint cursorPos = QCursor::pos();//globalPos

            //在content里面才能响应 [比较的时候不放大坐标，调试出来的]
            if ( rectMustIn.contains ( cursorPos ) && rectMustNotIn.contains ( cursorPos ) )
            {
                QDropEvent* e = ( QDropEvent* ) event;
                p2line();
                //p2line() << e->dropAction();
                p2line() << e->spontaneous();
                p2line() << e->source()->objectName();
                p2line() << e->mimeData()->formats() << e->mimeData()->urls();
                p2line() << e->possibleActions() << e->proposedAction();
            }

            event->accept();
            return false;
        }
        break;
        default:
            break;
    }

    return QObject::eventFilter ( watched, event );
}
