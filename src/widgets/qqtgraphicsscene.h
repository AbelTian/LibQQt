#ifndef QQTGRAPHICSSCENE_H
#define QQTGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "qqtgraphicsitem.h"
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QQtGraphicsScene ( QObject* parent = 0 );
    QQtGraphicsScene ( const QRectF& sceneRect, QObject* parent = 0 );
    QQtGraphicsScene ( qreal x, qreal y, qreal width, qreal height, QObject* parent = 0 );
    virtual ~QQtGraphicsScene() {}

    void render ( QPainter* painter,
                  const QRectF& target = QRectF(), const QRectF& source = QRectF(),
                  Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio );
    QQtGraphicsEllipseItem* addEllipse ( const QRectF& rect, const QPen& pen = QPen(), const QBrush& brush = QBrush() );
    inline QQtGraphicsEllipseItem* addEllipse ( qreal x, qreal y, qreal w, qreal h, const QPen& pen = QPen(),
                                              const QBrush& brush = QBrush() )
    { return addEllipse ( QRectF ( x, y, w, h ), pen, brush ); }

    QQtGraphicsPathItem* addPath ( const QPainterPath& path, const QPen& pen = QPen(), const QBrush& brush = QBrush() );
    QQtGraphicsPixmapItem* addPixmap ( const QPixmap& pixmap );
    QQtGraphicsPolygonItem* addPolygon ( const QPolygonF& polygon, const QPen& pen = QPen(),
                                         const QBrush& brush = QBrush() );
    QQtGraphicsTextItem* addText ( const QString& text, const QFont& font = QFont() );
    QQtGraphicsSimpleTextItem* addSimpleText ( const QString& text, const QFont& font = QFont() );
    QQtGraphicsProxyWidget* addWidget ( QWidget* widget, Qt::WindowFlags wFlags = 0 );
    QQtGraphicsLineItem* addLine ( const QLineF& line, const QPen& pen = QPen() );
    inline QQtGraphicsLineItem* addLine ( qreal x1, qreal y1, qreal x2, qreal y2, const QPen& pen = QPen() )
    { return addLine ( QLineF ( x1, y1, x2, y2 ), pen ); }
    QQtGraphicsRectItem* addRect ( const QRectF& rect, const QPen& pen = QPen(), const QBrush& brush = QBrush() );
    inline QQtGraphicsRectItem* addRect ( qreal x, qreal y, qreal w, qreal h, const QPen& pen = QPen(),
                                          const QBrush& brush = QBrush() )
    { return addRect ( QRectF ( x, y, w, h ), pen, brush ); }

signals:

public slots:


    // QGraphicsScene interface
protected:
    void drawItems ( QPainter* painter, int numItems, QGraphicsItem* items[], const QStyleOptionGraphicsItem options[],
                     QWidget* widget = 0 );

private:
};

#endif // QQTGRAPHICSSCENE_H
