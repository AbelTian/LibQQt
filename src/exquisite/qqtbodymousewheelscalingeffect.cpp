#include <qqtbodymousewheelscalingeffect.h>

#include <QEvent>
#include <QPainter>
#include <QWidget>

#include <qqtcore.h>

QQtBodyMouseWheelScalingEffect::QQtBodyMouseWheelScalingEffect ( QObject* parent ) : QObject ( parent ) {}

QQtBodyMouseWheelScalingEffect::~QQtBodyMouseWheelScalingEffect() {}


bool QQtBodyMouseWheelScalingEffect::eventFilter ( QObject* watched, QEvent* event )
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

    //static int i = 0;
    //p2line() << i++ << watched->objectName() << event->type() ;

    switch ( event->type() )
    {
        case QEvent::Wheel:
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
                //设置的时候放大。Windows/Unix不一样。
                QWheelEvent* e = ( QWheelEvent* ) event;

                qreal scaling = 1;
                //求取scaling 1.2 0.9
                //up
                if ( e->delta() < 0 )
                {
                    //int ratio = 2;
                    scaling = 1.2;
                }
                else
                {
                    //int ratio = -2;
                    scaling = 0.8;
                }

                //delta 120 -120
                //pixelDelta 是个变化的数字 2->... -2->...
                //angleDelta 是个x=0的点 y = 120 或者 -120
                //phase NoScrollPhase?
                //p2line() << e->delta() << e->pixelDelta() << e->angleDelta() << e->phase();

                //在鼠标位置为中心，开始放大，看来就是比例位置保持。maptoglobal?maptoparent? keepaspio

                QPoint p0, p1;
                p0 = w.rect().topLeft();
                p1 = w.rect().bottomRight();
                p0 = w.mapToGlobal ( p0 );
                p1 = w.mapToGlobal ( p1 );
                QRect r0 = QRect ( p0, p1 );
#ifdef __DESKTOP_WIN__
                qreal ratio = w.devicePixelRatioF();
#else
                qreal ratio = 1;
#endif
                QRect qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ),
                                    QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );

                int width, height;
                width = qr0.width();
                height = qr0.height();
                if ( width == 0 )
                    width = 0.1;

                qreal aspio2 = ( qreal ) height / width;

                //以x为基准进行计算，y进行图形保持比例计算
                int dx1, dx2;
                dx1 = cursorPos.x() - qr0.left();
                dx2 = qr0.right() - cursorPos.x();

                int x1, y1, x2, y2;
                x1 = w.geometry().left() - dx1 * ( scaling - 1 );
                x2 = w.geometry().right() + dx2 * ( scaling - 1 );
                y1 = w.geometry().top() - dx1 * ( scaling - 1 ) * aspio2;
                y2 = y1 + ( x2 - x1 ) * aspio2;
                //p2line() << dx1 << dx2 << scaling << aspio2;
                //p2line() << w.geometry() << QPoint ( x1, y1 ) << QPoint ( x2, y2 ) << QRect ( QPoint ( x1, y1 ), QPoint ( x2, y2 ) );
                w.setGeometry ( QRect ( QPoint ( x1, y1 ), QPoint ( x2, y2 ) ) );
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
