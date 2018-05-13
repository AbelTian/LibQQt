#include "qqtgraphicsitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "qqtcore.h"

QQtGraphicsItem::QQtGraphicsItem(QQtGraphicsItem* parent) : QGraphicsItem(parent) {}


QQtGraphicsTextItem::QQtGraphicsTextItem(QQtGraphicsItem* parent) : QGraphicsTextItem(parent) {}


QQtGraphicsRectItem::QQtGraphicsRectItem(QQtGraphicsItem* parent) : QGraphicsRectItem(parent) {}


QQtGraphicsSimpleTextItem::QQtGraphicsSimpleTextItem(QQtGraphicsItem* parent) : QGraphicsSimpleTextItem(parent) {}


QQtGraphicsLineItem::QQtGraphicsLineItem(QQtGraphicsItem* parent) : QGraphicsLineItem(parent) {}


QQtGraphicsPixmapItem::QQtGraphicsPixmapItem(QQtGraphicsItem* parent) : QGraphicsPixmapItem(parent) {}


QQtGraphicsPathItem::QQtGraphicsPathItem(QQtGraphicsItem* parent) : QGraphicsPathItem(parent) {}


QQtGraphicsEllipseItem::QQtGraphicsEllipseItem(QQtGraphicsItem* parent) : QGraphicsEllipseItem(parent) {}


QQtGraphicsPolygonItem::QQtGraphicsPolygonItem(QQtGraphicsItem* parent) : QGraphicsPolygonItem(parent) {}


QQtGraphicsItemGroup::QQtGraphicsItemGroup(QQtGraphicsItem* parent) : QGraphicsItemGroup(parent) {}


QQtGraphicsProxyWidget::QQtGraphicsProxyWidget(QQtGraphicsItem* parent) : QGraphicsProxyWidget(parent) {}


void QQtGraphicsTextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget)
    QFont oldFont(painter->font());

    painter->setFont(font());
    //painter->fillRect(option->rect, Qt::SolidPattern);
    painter->drawText(option->rect, Qt::AlignCenter, toPlainText());

    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus))
        ;

    if (0 && toPlainText().contains("Da Zi"))
    {
        pline() << font().pointSize() << font().pixelSize();
        pline() << pos() << option->rect << option->exposedRect << toPlainText();
        pline() << option->matrix << option->matrix.mapRect(option->rect);
    }

    painter->setFont(oldFont);
}


void QQtGraphicsLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget)
    QPen oldPen(painter->pen());

    qreal xratio = option->rect.width() / option->exposedRect.width();
    qreal yratio = option->rect.height() / option->exposedRect.height();
    Q_UNUSED(yratio)
    //TODO:

    QPen pn = pen();
    pn.setWidth(pn.width()*xratio);
    painter->setPen(pn);

    QLineF l = QLineF(option->rect.left(), option->rect.top(),
                      option->rect.right(), option->rect.bottom());

    painter->drawLine(l);

    if (0)
    {
        pline() << line() << l << option->rect << option->exposedRect;
        pline() << option->matrix << option->matrix.mapRect(option->rect);
    }

    painter->setPen(oldPen);
}


void QQtGraphicsRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget)
    QPen oldPen(painter->pen());
    QBrush oldBrush(painter->brush());

    qreal xratio = option->rect.width() / option->exposedRect.width();
    qreal yratio = option->rect.height() / option->exposedRect.height();
    Q_UNUSED(yratio)
    //TODO:

    QPen pn = pen();
    pn.setWidth(pn.width()*xratio);
    painter->setPen(pn);

    QRectF r = QRectF(option->rect.left(), option->rect.top(),
                      option->rect.width(), option->rect.height());

    painter->setBrush(brush());
    painter->drawRect(r);

    if (0)
    {
        pline() << option->matrix << option->matrix.mapRect(option->rect) << r;
    }

    painter->setPen(oldPen);
    painter->setBrush(oldBrush);
}
