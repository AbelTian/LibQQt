#include "qqtcolorwidget.h"

QQtColorWidget::QQtColorWidget ( QWidget* parent ) : QWidget ( parent )
{
    setStyleSheet ( "QWidget{background-color:#FFFFFF;}" );
}

void QQtColorWidget::setColor ( const QRgb& rgb )
{
    mRgb = rgb;
    QString colorString = QString ( "QWidget{background-color:#%1%2%3;}" )
                          .arg ( qRed ( rgb ), 2, 16, QChar ( '0' ) )
                          .arg ( qGreen ( rgb ), 2, 16, QChar ( '0' ) )
                          .arg ( qBlue ( rgb ), 2, 16, QChar ( '0' ) );
    setStyleSheet ( colorString );
}

QRgb QQtColorWidget::getColor()
{
    return mRgb;
}
