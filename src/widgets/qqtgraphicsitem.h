#ifndef QQTGRAPHICSITEM_H
#define QQTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtGraphicsItem : public QGraphicsItem
{
public:
    explicit QQtGraphicsItem ( QQtGraphicsItem* parent = 0 );

};

class QQTSHARED_EXPORT QQtGraphicsTextItem : public QGraphicsTextItem
{
public:
    explicit QQtGraphicsTextItem ( QQtGraphicsItem* parent = 0 );


    // QGraphicsItem interface
public:
    void paint ( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
};


class QQTSHARED_EXPORT QQtGraphicsSimpleTextItem : public QGraphicsSimpleTextItem
{
public:
    explicit QQtGraphicsSimpleTextItem ( QQtGraphicsItem* parent = 0 );

};


class QQTSHARED_EXPORT QQtGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    explicit QQtGraphicsPixmapItem ( QQtGraphicsItem* parent = 0 );

};

class QQTSHARED_EXPORT QQtGraphicsRectItem : public QGraphicsRectItem
{
public:
    explicit QQtGraphicsRectItem ( QQtGraphicsItem* parent = 0 );


    // QGraphicsItem interface
public:
    void paint ( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
};


class QQTSHARED_EXPORT QQtGraphicsLineItem : public QGraphicsLineItem
{
public:
    explicit QQtGraphicsLineItem ( QQtGraphicsItem* parent = 0 );


    // QGraphicsItem interface
public:
    void paint ( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
};




class QQTSHARED_EXPORT QQtGraphicsPathItem : public QGraphicsPathItem
{
public:
    explicit QQtGraphicsPathItem ( QQtGraphicsItem* parent = 0 );

};


class QQTSHARED_EXPORT QQtGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    explicit QQtGraphicsEllipseItem ( QQtGraphicsItem* parent = 0 );

};


class QQTSHARED_EXPORT QQtGraphicsPolygonItem : public QGraphicsPolygonItem
{
public:
    explicit QQtGraphicsPolygonItem ( QQtGraphicsItem* parent = 0 );

};

class QQTSHARED_EXPORT QQtGraphicsItemGroup : public QGraphicsItemGroup
{
public:
    explicit QQtGraphicsItemGroup ( QQtGraphicsItem* parent = 0 );

};

class QQTSHARED_EXPORT QQtGraphicsProxyWidget : public QGraphicsProxyWidget
{
public:
    explicit QQtGraphicsProxyWidget ( QQtGraphicsItem* parent = 0 );

};


#endif // QQTGRAPHICSITEM_H
