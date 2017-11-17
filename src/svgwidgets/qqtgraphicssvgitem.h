#ifndef QQTGRAPHICSSVGITEM_H
#define QQTGRAPHICSSVGITEM_H

#include <QGraphicsSvgItem>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtGraphicsSvgItem : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    explicit QQtGraphicsSvgItem(QQtGraphicsSvgItem* parent = nullptr);
    explicit QQtGraphicsSvgItem(const QString& fileName, QQtGraphicsSvgItem* parentItem = nullptr);

signals:

public slots:
};

#endif // QQTGRAPHICSSVGITEM_H
