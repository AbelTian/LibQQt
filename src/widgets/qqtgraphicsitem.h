#ifndef QQTGRAPHICSITEM_H
#define QQTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQTGraphicsItem : public QGraphicsItem
{
public:
    explicit QQTGraphicsItem(QQTGraphicsItem *parent = 0);

};

class QQTSHARED_EXPORT QQTGraphicsTextItem : public QGraphicsTextItem
{
public:
    explicit QQTGraphicsTextItem(QQTGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class QQTSHARED_EXPORT QQTGraphicsSimpleTextItem : public QGraphicsSimpleTextItem
{
public:
    explicit QQTGraphicsSimpleTextItem(QQTGraphicsItem *parent = 0);

};


class QQTSHARED_EXPORT QQTGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    explicit QQTGraphicsPixmapItem(QQTGraphicsItem *parent = 0);

};

class QQTSHARED_EXPORT QQTGraphicsRectItem : public QGraphicsRectItem
{
public:
    explicit QQTGraphicsRectItem(QQTGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class QQTSHARED_EXPORT QQTGraphicsLineItem : public QGraphicsLineItem
{
public:
    explicit QQTGraphicsLineItem(QQTGraphicsItem *parent = 0);


    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};




class QQTSHARED_EXPORT QQTGraphicsPathItem : public QGraphicsPathItem
{
public:
    explicit QQTGraphicsPathItem(QQTGraphicsItem *parent = 0);

};


class QQTSHARED_EXPORT QQTGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    explicit QQTGraphicsEllipseItem(QQTGraphicsItem *parent = 0);

};


class QQTSHARED_EXPORT QQTGraphicsPolygonItem : public QGraphicsPolygonItem
{
public:
    explicit QQTGraphicsPolygonItem(QQTGraphicsItem *parent = 0);

};

class QQTSHARED_EXPORT QQTGraphicsItemGroup : public QGraphicsItemGroup
{
public:
    explicit QQTGraphicsItemGroup(QQTGraphicsItem *parent = 0);

};

class QQTSHARED_EXPORT QQTGraphicsProxyWidget : public QGraphicsProxyWidget
{
public:
    explicit QQTGraphicsProxyWidget(QQTGraphicsItem *parent = 0);

};


#endif // QQTGRAPHICSITEM_H
