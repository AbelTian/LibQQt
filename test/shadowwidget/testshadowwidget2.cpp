#include <testshadowwidget2.h>

#include <QPainter>

#include <QtMath>

#include <qqtbodymover.h>

TestShadowWidget2::TestShadowWidget2 ( QWidget* parent ) : QWidget ( parent )
{
    setWindowFlag ( Qt::FramelessWindowHint );

    QQtBodyMover* mover = new QQtBodyMover ( this );
    installEventFilter ( mover );
}

TestShadowWidget2::~TestShadowWidget2() {}


void TestShadowWidget2::paintEvent ( QPaintEvent* event )
{

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
