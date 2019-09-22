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
    ~QQtBodyResizerPrivate();

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

    QMargins& margins();
    const QMargins& margins() const;

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

    QMargins m_margins;
    MoveDirection direction;
};

#endif //QQTBODYRESIZER_P_H
