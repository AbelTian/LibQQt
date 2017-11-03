#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // bluetooth example
    // serialport example
    // tcpsocket example
    // websocket?
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}
