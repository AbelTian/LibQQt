#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtcustomspeedmeter.h>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->w0->setMinValue(0);
    //ui->widget->setMaxValue(100);
    //ui->widget->setValue(80);
}

MainWindow::~MainWindow()
{
    delete ui;
}
