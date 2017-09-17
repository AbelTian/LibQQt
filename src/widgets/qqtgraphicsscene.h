#ifndef QQTGRAPHICSSCENE_H
#define QQTGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "qqtgraphicsitem.h"
#include <qqt.h>

class QQTSHARED_EXPORT QQTGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QQTGraphicsScene(QObject *parent = 0);
    QQTGraphicsScene(const QRectF &sceneRect, QObject *parent = 0);
    QQTGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    virtual ~QQTGraphicsScene() {}

    void render(QPainter *painter,
                const QRectF &target = QRectF(), const QRectF &source = QRectF(),
                Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio);
    QQTGraphicsEllipseItem *addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    inline QGraphicsEllipseItem *addEllipse(qreal x, qreal y, qreal w, qreal h, const QPen &pen = QPen(), const QBrush &brush = QBrush())
    { return addEllipse(QRectF(x, y, w, h), pen, brush); }

    QQTGraphicsPathItem *addPath(const QPainterPath &path, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    QQTGraphicsPixmapItem *addPixmap(const QPixmap &pixmap);
    QQTGraphicsPolygonItem *addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    QQTGraphicsTextItem *addText(const QString &text, const QFont &font = QFont());
    QQTGraphicsSimpleTextItem *addSimpleText(const QString &text, const QFont &font = QFont());
    QQTGraphicsProxyWidget *addWidget(QWidget *widget, Qt::WindowFlags wFlags = 0);
    QQTGraphicsLineItem *addLine(const QLineF &line, const QPen &pen = QPen());
    inline QQTGraphicsLineItem *addLine(qreal x1, qreal y1, qreal x2, qreal y2, const QPen &pen = QPen())
    { return addLine(QLineF(x1, y1, x2, y2), pen); }
    QQTGraphicsRectItem *addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    inline QQTGraphicsRectItem *addRect(qreal x, qreal y, qreal w, qreal h, const QPen &pen = QPen(), const QBrush &brush = QBrush())
    { return addRect(QRectF(x, y, w, h), pen, brush); }

signals:

public slots:


    // QGraphicsScene interface
protected:
    void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget = 0);

private:
};

#endif // QQTGRAPHICSSCENE_H
