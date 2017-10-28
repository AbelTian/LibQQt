#include "mainwindow.h"

#include <qqtcustomspeedmeter.h>

MainWindow::MainWindow(QWidget* parent) :
    QDialog(parent)
{
    QQtCustomSpeedMeter* w0 = new QQtCustomSpeedMeter(this);
    w0->setMinValue(0);
    w0->setMaxValue(100);
    w0->setValue(80);
}

MainWindow::~MainWindow()
{
}
