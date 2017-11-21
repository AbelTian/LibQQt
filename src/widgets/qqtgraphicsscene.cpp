#include "qqtgraphicsscene.h"
#include <QGraphicsItem>
#include <QPainter>
#include "qqtcore.h"
#include "qqt-qt.h"
QQtGraphicsScene::QQtGraphicsScene(QObject* parent) :
    QGraphicsScene(parent)
{
}

QQtGraphicsScene::QQtGraphicsScene(const QRectF& sceneRect, QObject* parent) :
    QGraphicsScene(sceneRect, parent)
{

}

QQtGraphicsScene::QQtGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent) :
    QGraphicsScene(x, y, width, height, parent)
{

}

/**
 * @brief QQtGraphicsScene::render
 * 经过测试，失真是由于render放缩QPainter和drawItems里面的itemPaint共同导致失真
 * 现在规整理如下，原则：Qpainter不允许改变
 * 重写itemPaint函数
 * @param painter
 * @param target
 * @param source
 * @param aspectRatioMode
 */
void QQtGraphicsScene::render(QPainter* painter, const QRectF& target, const QRectF& source,
                              Qt::AspectRatioMode aspectRatioMode)
{
    Q_UNUSED(aspectRatioMode)
    // Find the ideal x / y scaling ratio to fit a source into a target.
    QRectF sourceRect = sceneRect();
    QRectF targetRect = sourceRect;

    if (!source.isEmpty())
        sourceRect = source;

    if (!target.isEmpty())
        targetRect = target;

    qreal xratio = targetRect.width() / sourceRect.width();
    qreal yratio = targetRect.height() / sourceRect.height();

    QList<QGraphicsItem*> itemList = items();
    QGraphicsItem** itemArray = new QGraphicsItem *[itemList.size()];
    int numItems = itemList.size();

    for (int i = 0; i < numItems; ++i)
        itemArray[numItems - i - 1] = itemList.at(i);

    itemList.clear();

    painter->save();

    // Generate the style options
    QStyleOptionGraphicsItem* styleOptionArray = new QStyleOptionGraphicsItem[numItems];

    for (int i = 0; i < numItems; ++i)
    {
        QGraphicsItem* item = itemArray[i];
        QStyleOptionGraphicsItem option;
        option.state = QStyle::State_None;

        if (item->isSelected())
            option.state |= QStyle::State_Selected;

        if (item->isEnabled())
            option.state |= QStyle::State_Enabled;

        if (item->hasFocus())
            option.state |= QStyle::State_HasFocus;

        if (item == mouseGrabberItem())
            option.state |= QStyle::State_Sunken;

        option.exposedRect = item->boundingRect();

        option.rect.setLeft(item->pos().x()*xratio);
        option.rect.setWidth(option.exposedRect.width()*xratio);
        option.rect.setTop(item->pos().y()*yratio);
        option.rect.setHeight(option.exposedRect.height()*yratio);

        //pline() << xratio << yratio << item->pos() << option.rect << option.exposedRect;

        styleOptionArray[i] = option;
    }

    // Render the scene.
    drawBackground(painter, targetRect);
    drawItems(painter, numItems, itemArray, styleOptionArray);
    drawForeground(painter, targetRect);
    delete [] itemArray;
    delete [] styleOptionArray;

    painter->restore();
}

QQtGraphicsTextItem* QQtGraphicsScene::addText(const QString& text, const QFont& font)
{
    QQtGraphicsTextItem* item = new QQtGraphicsTextItem;
    item->setFont(font);
    item->setPlainText(text);
    addItem(item);
    return item;
}

QQtGraphicsRectItem* QQtGraphicsScene::addRect(const QRectF& rect, const QPen& pen, const QBrush& brush)
{
    QQtGraphicsRectItem* item = new QQtGraphicsRectItem;
    item->setRect(rect);
    item->setPen(pen);
    item->setBrush(brush);
    item->moveBy(rect.x(), rect.y());
    addItem(item);
    return item;
}

QQtGraphicsLineItem* QQtGraphicsScene::addLine(const QLineF& line, const QPen& pen)
{
    QQtGraphicsLineItem* item = new QQtGraphicsLineItem;
    item->setLine(line);
    item->setPen(pen);
    item->moveBy(line.x1(), line.y1());

    addItem(item);
    return item;
}


void QQtGraphicsScene::drawItems(QPainter* painter, int numItems, QGraphicsItem* items[],
                                 const QStyleOptionGraphicsItem options[], QWidget* widget)
{
    for (int i = 0; i < numItems; ++i)
    {

        QQtGraphicsItem* item = (QQtGraphicsItem*)items[i];

        if (item->flags() & QGraphicsItem::ItemClipsToShape)
        {
            //painter->setClipPath(item->shape(), Qt::IntersectClip);
        }

        item->paint(painter, &options[i], widget);
    }

}
