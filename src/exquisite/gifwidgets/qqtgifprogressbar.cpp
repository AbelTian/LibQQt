#include "qqtgifprogressbar.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QSpacerItem>
#include <QWidget>
#include <QApplication>

QQtGifProgressBar::QQtGifProgressBar ( QWidget* parent ) : QQtGifWidget ( parent )
{
    this->resize ( 487, 34 );
    setContentsMargins ( 0, 0, 0, 0 );
    setWindowTitle ( QApplication::translate ( "QQtGifProgressBar", "Form", nullptr ) );

    widgetBack = new QQtGifWidget ( this );
    widgetBack->setObjectName ( "gifWidgetBack" );

    QGridLayout* gridLayout = new QGridLayout ( widgetBack );
    gridLayout->setObjectName ( "gifGridLayout" );
    gridLayout->setContentsMargins ( 0, 0, 0, 0 );

    widgetTrunk = new QQtGifWidget ( widgetBack );
    widgetTrunk->setObjectName ( "gifWidgetTrunk" );
    gridLayout->addWidget ( widgetTrunk, 0, 0, 1, 1 );

    QSpacerItem* horizontalSpacer = new QSpacerItem ( 149, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    gridLayout->addItem ( horizontalSpacer, 0, 1, 1, 1 );

    QSpacerItem* verticalSpacer = new QSpacerItem ( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    gridLayout->addItem ( verticalSpacer, 1, 0, 1, 1 );

    QHBoxLayout* horizontalLayout = new QHBoxLayout ( this );
    horizontalLayout->setSpacing ( 0 );
    horizontalLayout->setContentsMargins ( 0, 0, 0, 0 );
    horizontalLayout->setObjectName ( "gifHorizontalLayout" );
    horizontalLayout->addWidget ( widgetBack );
    setLayout ( horizontalLayout );

    setRange ( 0, 100 );
    setValue ( 0 );
}

void QQtGifProgressBar::setGifFile ( QString back, QString trunk )
{
    widgetBack->setGifFile ( back );
    widgetTrunk->setGifFile ( trunk );
}

void QQtGifProgressBar::setValue ( int value )
{
    m_value = value;
    int w = widgetBack->width() * ( m_value - m_min ) / ( m_max - m_min );
    int h = widgetBack->height();
    widgetTrunk->setGeometry ( 0, 0, w, h );
}

void QQtGifProgressBar::setRange ( int min, int max )
{
    m_min = min;
    m_max = max;
}
