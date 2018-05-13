#ifndef QQTCHARTVIEW_H
#define QQTCHARTVIEW_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

#include "qqtcore.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtChartView : public QChartView
{
    Q_OBJECT
public:
    explicit QQtChartView ( QWidget* parent = nullptr );
    explicit QQtChartView ( QChart* chart, QWidget* parent = nullptr );
    virtual ~QQtChartView() {}

signals:

public slots:
};

#endif // QQTCHARTVIEW_H
