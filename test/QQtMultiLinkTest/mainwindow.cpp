#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtbasedlibtest.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    QQtBasedLibTest l;
}

MainWindow::~MainWindow()
{
    delete ui;
}
