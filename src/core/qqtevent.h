#ifndef QQTEVENT_H
#define QQTEVENT_H

#include <QEvent>

#include "qqt-qt.h"
#include <qqt-local.h>


class QQTSHARED_EXPORT QQtMouseEvent : public QMouseEvent
{
public:
    QQtMouseEvent() :
        QMouseEvent ( MouseButtonPress, QPointF(), QPointF(), QPointF(),
                      Qt::LeftButton, Qt::LeftButton, Qt::NoModifier,  Qt::MouseEventNotSynthesized ) {

    }
    virtual ~QQtMouseEvent() {}

public:
    //设置
    QQtMouseEvent& operator= ( const QMouseEvent& other ) {
        QQtMouseEvent& ref = *this;
        ref.setType ( other.type() );
        ref.localPos() = other.localPos();
        ref.windowPos() = other.windowPos();
        ref.screenPos() = other.screenPos();

#ifndef QT_NO_INTEGER_EVENT_COORDINATES
        ref.pos() = other.pos();
        ref.globalPos() = other.globalPos();
#endif

        ref.button() = other.button();
        ref.buttons() = other.buttons();
        ref.setModifiers ( other.modifiers() );

        //source 无解
        return ref;
    }
    //读取
#ifndef QT_NO_INTEGER_EVENT_COORDINATES
    inline QPoint& pos() { return _l; }
    inline QPoint& globalPos() { return _s; }
    inline int& x() { return _l.rx(); }
    inline int& y() { return _l.ry(); }
    inline int& globalX() { return _s.rx(); }
    inline int& globalY() { return _s.ry(); }
#endif
    QPointF& localPos() { return l; }
    QPointF& windowPos() { return w; }
    QPointF& screenPos() { return s; }

    inline Qt::MouseButton& button() { return b; }
    inline Qt::MouseButtons& buttons() { return mouseState; }

    //inline Qt::MouseEventSource& source() { return sou}
    //inline Qt::MouseEventFlags& flags();

    inline void setType ( const Type& _t ) { t = _t; }

protected:
    QPoint _l, _w, _s;
};

#endif // QQTEVENT_H
