#include "qqtripplepushbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>

QQtRipplePushButton::QQtRipplePushButton ( QWidget* parent )
    : QPushButton ( parent )
    , pointX ( 0 )
    , pointY ( 0 )
    , waveRadius ( 0 )
{
    setClickColor ( QColor ( Qt::lightGray ) );
}

void QQtRipplePushButton::paintEvent ( QPaintEvent* event )
{
    if ( waveRadius < ( width() > height() ? width() : height() ) * 2 )
    {
        // 主圆圈
        QPainter tempPainter;
        tempPainter.begin ( this );
        QBrush tempBrush;
        tempBrush.setStyle ( Qt::SolidPattern );
        tempBrush.setColor ( getClickColor() );
        tempPainter.setBrush ( tempBrush );
        QPen tempPen;
        tempPen.setColor ( getClickColor() );
        tempPen.setJoinStyle ( Qt::RoundJoin );
        tempPen.setCapStyle ( Qt::FlatCap );
        tempPainter.setPen ( tempPen );
        tempPainter.setRenderHint ( QPainter::HighQualityAntialiasing );
        tempPainter.setOpacity ( 0.7 );
        QRectF rectangle ( pointX - waveRadius / 2, pointY - waveRadius / 2, waveRadius, waveRadius );
        tempPainter.drawEllipse ( rectangle );
        tempPainter.end();
    }

    QWidget::paintEvent ( event );
}

void QQtRipplePushButton::mousePressEvent ( QMouseEvent* event )
{
    pointX = event->x();
    pointY = event->y();
    QPropertyAnimation* animation = new QPropertyAnimation ( this, "waveRadius" );
    animation->setDuration ( 400 );
    animation->setStartValue ( 0 );
    animation->setEndValue ( ( width() > height() ? width() : height() ) * 2 );
    animation->start();
}

QColor QQtRipplePushButton::getClickColor() const
{
    return clickColor;
}

void QQtRipplePushButton::setClickColor ( const QColor& value )
{
    clickColor = value;
}

qreal QQtRipplePushButton::getWaveRadius() const
{
    return waveRadius;
}

void QQtRipplePushButton::setWaveRadius ( const qreal& value )
{
    waveRadius = value;
    emit waveRadiusChanged ( value );
    update();
}
