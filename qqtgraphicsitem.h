#ifndef QQTGRAPHICSITEM_H
#define QQTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsProxyWidget>

class QQTGraphicsItem : public QGraphicsItem
{
public:
    explicit QQTGraphicsItem(QQTGraphicsItem *parent = 0);

};

class QQTGraphicsTextItem : public QGraphicsTextItem
{
public:
    explicit QQTGraphicsTextItem(QQTGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class QQTGraphicsSimpleTextItem : public QGraphicsSimpleTextItem
{
public:
    explicit QQTGraphicsSimpleTextItem(QQTGraphicsItem *parent = 0);

};


class QQTGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    explicit QQTGraphicsPixmapItem(QQTGraphicsItem *parent = 0);

};

class QQTGraphicsRectItem : public QGraphicsRectItem
{
public:
    explicit QQTGraphicsRectItem(QQTGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class QQTGraphicsLineItem : public QGraphicsLineItem
{
public:
    explicit QQTGraphicsLineItem(QQTGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};




class QQTGraphicsPathItem : public QGraphicsPathItem
{
public:
    explicit QQTGraphicsPathItem(QQTGraphicsItem *parent = 0);

};


class QQTGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    explicit QQTGraphicsEllipseItem(QQTGraphicsItem *parent = 0);

};


class QQTGraphicsPolygonItem : public QGraphicsPolygonItem
{
public:
    explicit QQTGraphicsPolygonItem(QQTGraphicsItem *parent = 0);

};

class QQTGraphicsItemGroup : public QGraphicsItemGroup
{
public:
    explicit QQTGraphicsItemGroup(QQTGraphicsItem *parent = 0);

};

class QQTGraphicsProxyWidget : public QGraphicsProxyWidget
{
public:
    explicit QQTGraphicsProxyWidget(QQTGraphicsItem *parent = 0);

};


#endif // QQTGRAPHICSITEM_H
