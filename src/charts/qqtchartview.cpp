#include "qqtchartview.h"

QQtChartView::QQtChartView ( QWidget* parent ) :
    QChartView ( parent )
{

}

QQtChartView::QQtChartView ( QChart* chart, QWidget* parent ) :
    QChartView ( chart, parent )
{

}
