#ifndef QQTGRAPHICSVIEW_H
#define QQTGRAPHICSVIEW_H

#include <QGraphicsView>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QQtGraphicsView ( QWidget* parent = 0 );

signals:

public slots:


    // QWidget interface
protected:
    void paintEvent ( QPaintEvent* );

    // QGraphicsView interface
protected:
    void drawItems ( QPainter* painter, int numItems, QGraphicsItem* items[], const QStyleOptionGraphicsItem options[] );
};

#endif // QQTGRAPHICSVIEW_H
