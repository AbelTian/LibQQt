#include "qqtcolorlabel.h"

QQtColorLabel::QQtColorLabel ( QWidget* parent ) : QLabel ( parent )
{
    setStyleSheet ( "QLabel{background-color:#FFFFFF;}" );
}

void QQtColorLabel::setColor ( const QRgb& rgb )
{
    mRgb = rgb;
    QString colorString = QString ( "QLabel{background-color:#%1%2%3;}" )
                          .arg ( qRed ( rgb ), 2, 16, QChar ( '0' ) )
                          .arg ( qGreen ( rgb ), 2, 16, QChar ( '0' ) )
                          .arg ( qBlue ( rgb ), 2, 16, QChar ( '0' ) );
    setStyleSheet ( colorString );
}

QRgb QQtColorLabel::getColor()
{
    return mRgb;
}
