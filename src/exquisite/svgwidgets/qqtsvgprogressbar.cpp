#include "qqtsvgprogressbar.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QSpacerItem>
#include <QWidget>
#include <QApplication>

QQtSvgProgressBar::QQtSvgProgressBar ( QWidget* parent ) : QQtSvgWidget ( parent )
{
    this->resize ( 487, 34 );
    setContentsMargins ( 0, 0, 0, 0 );
    setWindowTitle ( QApplication::translate ( "QQtSvgProgressBar", "Form", nullptr ) );

    widgetBack = new QQtSvgWidget ( this );
    widgetBack->setObjectName ( "svgWidgetBack" );

    QGridLayout* gridLayout = new QGridLayout ( widgetBack );
    gridLayout->setObjectName ( "svgGridLayout" );
    gridLayout->setContentsMargins ( 0, 0, 0, 0 );

    widgetTrunk = new QQtSvgWidget ( widgetBack );
    widgetTrunk->setObjectName ( "svgWidgetTrunk" );
    gridLayout->addWidget ( widgetTrunk, 0, 0, 1, 1 );

    QSpacerItem* horizontalSpacer = new QSpacerItem ( 149, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    gridLayout->addItem ( horizontalSpacer, 0, 1, 1, 1 );

    QSpacerItem* verticalSpacer = new QSpacerItem ( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    gridLayout->addItem ( verticalSpacer, 1, 0, 1, 1 );

    QHBoxLayout* horizontalLayout = new QHBoxLayout ( this );
    horizontalLayout->setSpacing ( 0 );
    horizontalLayout->setContentsMargins ( 0, 0, 0, 0 );
    horizontalLayout->setObjectName ( "svgHorizontalLayout" );
    horizontalLayout->addWidget ( widgetBack );
    setLayout ( horizontalLayout );

    setRange ( 0, 100 );
    setValue ( 0 );
}

void QQtSvgProgressBar::setSvgFile ( QString back, QString trunk )
{
    widgetBack->setSvgFile ( back );
    widgetTrunk->setSvgFile ( trunk );
}

void QQtSvgProgressBar::setValue ( int value )
{
    m_value = value;
    int w = widgetBack->width() * ( m_value - m_min ) / ( m_max - m_min );
    int h = widgetBack->height();
    widgetTrunk->setGeometry ( 0, 0, w, h );
}

void QQtSvgProgressBar::setRange ( int min, int max )
{
    m_min = min;
    m_max = max;
}
