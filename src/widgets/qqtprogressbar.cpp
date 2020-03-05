#include "qqtprogressbar.h"
#include "ui_qqtprogressbar.h"
#include "QStylePainter"
#include "qqtcore.h"
#include "QHBoxLayout"
#include "QSpacerItem"

QQtProgressBar::QQtProgressBar ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::QQtProgressBar )
{
    ui->setupUi ( this );
    m_value = m_min = 0;
    m_max = 100;
    QString back = "./skin/default/bk_progress_background.png";
    QString trunk = "./skin/default/bk_progress_trunk.png";
    ui->widthTrunk->setPixmap ( trunk );
    ui->widgetBack->setPixmap ( back );

    ui->widthTrunk->setImageStyle ( QQtWidget::QQTTILEDWIDTH );
    ui->widgetBack->setImageStyle ( QQtWidget::QQTZOOMWIDTH );
}

QQtProgressBar::~QQtProgressBar()
{
    delete ui;
}

void QQtProgressBar::setPixMap ( QString back, QString trunk )
{
    ui->widthTrunk->setPixmap ( trunk );
    ui->widgetBack->setPixmap ( back );
}

void QQtProgressBar::setPixMap ( const QImage& back, const QImage& trunk )
{
    ui->widthTrunk->setPixmap ( trunk );
    ui->widgetBack->setPixmap ( back );
}

void QQtProgressBar::setPixmap ( const QImage& back, const QImage& trunk )
{
    ui->widthTrunk->setPixmap ( trunk );
    ui->widgetBack->setPixmap ( back );
}

void QQtProgressBar::setImage ( const QImage& back, const QImage& trunk )
{
    ui->widthTrunk->setPixmap ( trunk );
    ui->widgetBack->setPixmap ( back );
}

void QQtProgressBar::setValue ( int value )
{
    m_value = value;
    int w = ui->widgetBack->width() * ( m_value - m_min ) / ( m_max - m_min );
    int h = ui->widgetBack->height();
    ui->widthTrunk->setFixedSize ( w, h );

    //pline() << width() << ui->widgetBack->width() << w << h;
}

void QQtProgressBar::setRange ( int min, int max )
{
    m_min = min;
    m_max = max;
}

