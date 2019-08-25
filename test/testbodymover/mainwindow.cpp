#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtwidgets.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    //setGeometry ( 100, 200, 800, 600 );
}

MainWindow::~MainWindow()
{
    delete ui;
}



