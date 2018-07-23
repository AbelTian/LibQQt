#include "qqtcolorwidget.h"

QQtColorWidget::QQtColorWidget ( QWidget* parent ) : QWidget ( parent )
{
}

void QQtColorWidget::setColor ( const QRgb& rgb )
{
    mRgb = rgb;
}

QRgb QQtColorWidget::getColor()
{
    return mRgb;
}


void QQtColorWidget::paintEvent ( QPaintEvent* event )
{
    QPainter painter ( this );
    //QPen pen = painter.pen();
    //pen.setColor ( QColor ( mRgb ) );
    painter.setPen ( Qt::NoPen );
    painter.setBrush ( QBrush ( QColor ( mRgb ) ) );
    painter.drawRect ( rect() );
}
