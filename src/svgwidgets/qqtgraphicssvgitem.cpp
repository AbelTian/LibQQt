#include "qqtgraphicssvgitem.h"

QQtGraphicsSvgItem::QQtGraphicsSvgItem(QQtGraphicsSvgItem* parent) :
    QGraphicsSvgItem(parent)
{

}

QQtGraphicsSvgItem::QQtGraphicsSvgItem(const QString& fileName, QQtGraphicsSvgItem* parentItem) :
    QGraphicsSvgItem(fileName, parentItem)
{

}
