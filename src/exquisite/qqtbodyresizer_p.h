#ifndef QQTBODYRESIZER_P_H
#define QQTBODYRESIZER_P_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <QMouseEvent>

class QQtBodyResizer;
class QQtBodyResizerPrivate
{
public:
    explicit QQtBodyResizerPrivate ( QQtBodyResizer* q );
    virtual ~QQtBodyResizerPrivate();

    enum MoveDirection
    {
        None = 0,
        Left,
        Right,
        LeftTop,
        RightTop,
        LeftBottom,
        RightBottom,
        Top,
        Bottom,
    };

protected:
    virtual void mousePressEvent ( QMouseEvent* event, QWidget* target = 0 );
    virtual void mouseReleaseEvent ( QMouseEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );

protected:
    virtual void checkDirection ( QMouseEvent* event, QWidget* target = 0 );
private:
    QQtBodyResizer* q_ptr;
    Q_DECLARE_PUBLIC ( QQtBodyResizer )

    bool bMousePressed;
    QPoint pressedPoint;

    MoveDirection direction;
};

#endif //QQTBODYRESIZER_P_H
