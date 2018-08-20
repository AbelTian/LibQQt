#include "qqtcolorwidget.h"
#include <QPainter>
#include <QPainterPath>

QQtColorWidget::QQtColorWidget ( QWidget* parent ) : QWidget ( parent )
{
    mRgb = QRgb ( 0 );
}

void QQtColorWidget::setColor ( const QRgb& rgb )
{
    mRgb = rgb;
    setAutoFillBackground ( true );
    QPalette plt = palette();
    plt.setColor ( QPalette::Background, QColor ( mRgb ) );
    setPalette ( plt );
    update();
}

QRgb QQtColorWidget::getColor()
{
    return mRgb;
}
