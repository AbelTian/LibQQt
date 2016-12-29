#ifndef QQTGRAPHICSVIEW_H
#define QQTGRAPHICSVIEW_H

#include <QGraphicsView>


class QQTGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QQTGraphicsView(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QGraphicsView interface
protected:
    void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[]);
};

#endif // QQTGRAPHICSVIEW_H
