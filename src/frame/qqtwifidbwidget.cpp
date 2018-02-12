#include "qqtwifidbwidget.h"

QQtWifiDBWidget::QQtWifiDBWidget ( QWidget* parent ) : QQtWidget ( parent )
{

}

void QQtWifiDBWidget::setDbPixMap ( QQtWifiDBWidget::DB_STAT s, const QString& pixname )
{
    if ( s < Db_S0 || s >= Db_SMax )
        return;

    pic[s] = pixname;
}

void QQtWifiDBWidget::setDB ( QQtWifiDBWidget::DB_STAT s )
{
    if ( s < Db_S0 || s >= Db_SMax )
        return;

    setPixmap ( pic[s] );
}
