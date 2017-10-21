#ifndef QQTFRAMELESSHELPERPRIVATE_H
#define QQTFRAMELESSHELPERPRIVATE_H

#include <QObject>
#include <QPoint>
#include <QMargins>

class QPushButton;
class QWidget;
class QEvent;
class QTimer;
class QMouseEvent;
class QQtFramelessHelperPrivate : public QObject
{
    Q_OBJECT
public:
    QPushButton* buttonMaximized;
    QPushButton* buttonRestore;
    QPushButton* buttonClose;
    QPushButton* buttonMinimized;

    QList<QWidget*> dragWidgets;
    QList<QWidget*> edgeWidgets;

    QWidget* parent;
    QMargins margins;

    QQtFramelessHelperPrivate(QWidget* parent);
    void addEdgeWidget(QWidget* widget);
    void addDragWidget(QWidget* widget);

    void refreshMaximizedButton();

protected:
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

    enum MoveOperation
    {
        MoveNone = 0,
        MoveResize,
        MoveDrag,
    };

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private slots:
    void checkPos();

    void resize(const QPoint& cursorPos);

private:
    bool isMaximized;
    MoveDirection direction;
    MoveOperation operation;

    bool isMousePressed;

    QTimer* timer;

    QPoint dragBasePoint;
};

#endif // QQTFRAMELESSHELPERPRIVATE_H
