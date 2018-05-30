#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <math.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_draw.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();
    void setupRealtimeDataDemo ( QwtPlot* qwtplot );

private:
    Ui::MainWindow* ui;
    QVector<double> xdata;
    QVector<double> ydata;
    QTimer updateTimer;
    QString demoName;
    QwtPlotCurve* curve ;
    double getData ( double inteval );

private slots:
    void updatedataSlot();
};

#endif // MAINWINDOW_H
