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
    m_back = "./skin/default/bk_progress_background.png";
    m_trunk = "./skin/default/bk_progress_trunk.png";
    ui->widthTrunk->setPixmap ( m_trunk );
    ui->widgetBack->setPixmap ( m_back );
    ui->widthTrunk->setType ( QQtWidget::QQTTILEDWIDTH );
    ui->widgetBack->setType ( QQtWidget::QQTZOOMWIDTH );
}

QQtProgressBar::~QQtProgressBar()
{
    delete ui;
}

void QQtProgressBar::setPixMap ( QString back, QString trunk )
{
    m_back = back;
    m_trunk = trunk;
    ui->widthTrunk->setPixmap ( m_trunk );
    ui->widgetBack->setPixmap ( m_back );
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

