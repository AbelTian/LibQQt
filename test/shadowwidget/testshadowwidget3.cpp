#include <testshadowwidget3.h>

#include <QPainter>

#include <QtMath>

#include <qqtbodymover.h>

#include <customshadoweffect.h>

CustomShadowEffect2::CustomShadowEffect2 ( QObject* parent ) :
    QGraphicsEffect ( parent ),
    _distance ( 4.0f ),
    _blurRadius ( 10.0f ),
    _color ( 0, 0, 0, 80 )
{
}

QT_BEGIN_NAMESPACE
extern Q_WIDGETS_EXPORT void qt_blurImage ( QPainter* p, QImage& blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

void CustomShadowEffect2::draw ( QPainter* painter )
{
    {
        if ( ( blurRadius() + distance() ) <= 0 )
        {
            drawSource ( painter );
            return;
        }

        PixmapPadMode mode = QGraphicsEffect::PadToEffectiveBoundingRect;
        QPoint offset;
        const QPixmap px = sourcePixmap ( Qt::DeviceCoordinates, &offset, mode );
        // return if no source
        if ( px.isNull() )
            return;

        QPainterPath path;
        path.setFillRule ( Qt::WindingFill );
        path.addRect ( 10, 10, px.size().width() - 20, px.size().height() - 20 );
        //QPainter painter ( this );
        painter->setRenderHint ( QPainter::Antialiasing, true );
        painter->fillPath ( path, QBrush ( Qt::white ) );

        QColor color ( 0, 0, 0, 50 );
        for ( int i = 0; i < 10; i++ )
        {
            QPainterPath path;
            path.setFillRule ( Qt::WindingFill );
            path.addRect ( 10 - i, 10 - i, px.size().width() - ( 10 - i ) * 2, px.size().height() - ( 10 - i ) * 2 );
            color.setAlpha ( 150 - qSqrt ( i ) * 50 );
            painter->setPen ( color );
            painter->drawPath ( path );
        }
    }
    return;

    // if nothing to show outside the item, just draw source
    if ( ( blurRadius() + distance() ) <= 0 )
    {
        drawSource ( painter );
        return;
    }

    PixmapPadMode mode = QGraphicsEffect::PadToEffectiveBoundingRect;
    QPoint offset;
    const QPixmap px = sourcePixmap ( Qt::DeviceCoordinates, &offset, mode );
    // return if no source
    if ( px.isNull() )
        return;
    // save world transform
    QTransform restoreTransform = painter->worldTransform();
    painter->setWorldTransform ( QTransform() );
    // Calculate size for the background image
    QSize szi ( px.size().width() + 2 * distance(), px.size().height() + 2 * distance() );
    QImage tmp ( szi, QImage::Format_ARGB32_Premultiplied );
    QPixmap scaled = px.scaled ( szi );
    tmp.fill ( 0 );
    QPainter tmpPainter ( &tmp );
    tmpPainter.setCompositionMode ( QPainter::CompositionMode_Source );
    tmpPainter.drawPixmap ( QPointF ( -distance(), -distance() ), scaled );
    tmpPainter.end();
    // blur the alpha channel
    QImage blurred ( tmp.size(), QImage::Format_ARGB32_Premultiplied );
    blurred.fill ( 0 );
    QPainter blurPainter ( &blurred );
    qt_blurImage ( &blurPainter, tmp, blurRadius(), false, true );
    blurPainter.end();
    tmp = blurred;
    // blacken the image...
    tmpPainter.begin ( &tmp );
    tmpPainter.setCompositionMode ( QPainter::CompositionMode_SourceIn );
    tmpPainter.fillRect ( tmp.rect(), color() );
    tmpPainter.end();
    // draw the blurred shadow...
    painter->drawImage ( offset, tmp );
    // draw the actual pixmap...
    painter->drawPixmap ( offset, px, QRectF() );
    // restore world transform
    painter->setWorldTransform ( restoreTransform );
}

QRectF CustomShadowEffect2::boundingRectFor ( const QRectF& rect ) const
{
    qreal delta = blurRadius() + distance();
    return rect.united ( rect.adjusted ( -delta, -delta, delta, delta ) );
}

TestShadowWidget3::TestShadowWidget3 ( QWidget* parent ) : QWidget ( parent )
{
    setWindowFlag ( Qt::FramelessWindowHint );

    QQtBodyMover* mover = new QQtBodyMover ( this );
    installEventFilter ( mover );

#if 0
    //shadow 不管用，发黑
    CustomShadowEffect2* bodyShadow = new CustomShadowEffect2 ( this );
    bodyShadow->setBlurRadius ( 20.0 );
    bodyShadow->setDistance ( 6.0 );
    bodyShadow->setColor ( QColor ( 0, 0, 0, 80 ) );
    this->setGraphicsEffect ( bodyShadow );
#endif

    CustomShadowEffect2* bodyShadow = new CustomShadowEffect2();
    bodyShadow->setBlurRadius ( 20.0 );
    bodyShadow->setDistance ( 6.0 );
    bodyShadow->setColor ( QColor ( 0, 0, 0, 80 ) );
    this->setGraphicsEffect ( bodyShadow );

}

TestShadowWidget3::~TestShadowWidget3() {}


void TestShadowWidget3::paintEvent ( QPaintEvent* event )
{
    return QWidget::paintEvent ( event );

    QPainterPath path;
    path.setFillRule ( Qt::WindingFill );
    path.addRect ( 10, 10, this->width() - 20, this->height() - 20 );
    QPainter painter ( this );
    painter.setRenderHint ( QPainter::Antialiasing, true );
    painter.fillPath ( path, QBrush ( Qt::white ) );

    QColor color ( 0, 0, 0, 50 );
    for ( int i = 0; i < 10; i++ )
    {
        QPainterPath path;
        path.setFillRule ( Qt::WindingFill );
        path.addRect ( 10 - i, 10 - i, this->width() - ( 10 - i ) * 2, this->height() - ( 10 - i ) * 2 );
        color.setAlpha ( 150 - qSqrt ( i ) * 50 );
        painter.setPen ( color );
        painter.drawPath ( path );
    }
}
