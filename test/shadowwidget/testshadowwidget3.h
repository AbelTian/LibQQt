#ifndef TESTSHADOWWIDGET3_H
#define TESTSHADOWWIDGET3_H

#include <QWidget>
#include <QLabel>

#include <QGraphicsEffect>


class CustomShadowEffect2 : public QGraphicsEffect
{
    Q_OBJECT
public:
    explicit CustomShadowEffect2 ( QObject* parent = 0 );
    void draw ( QPainter* painter );
    QRectF boundingRectFor ( const QRectF& rect ) const;
    inline void setDistance ( qreal distance ) { _distance = distance; updateBoundingRect(); }
    inline qreal distance() const { return _distance; }
    inline void setBlurRadius ( qreal blurRadius ) { _blurRadius = blurRadius; updateBoundingRect(); }
    inline qreal blurRadius() const { return _blurRadius; }
    inline void setColor ( const QColor& color ) { _color = color; }
    inline QColor color() const { return _color; }
private:
    qreal  _distance;
    qreal  _blurRadius;
    QColor _color;
};

class TestShadowWidget3 : public QWidget
{
    Q_OBJECT
public:
    explicit TestShadowWidget3 ( QWidget* parent = 0 );
    virtual ~TestShadowWidget3();

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;
};

#endif //TESTSHADOWWIDGET3_H
