#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <autoswitch.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    Plot* plot = new Plot ( ui->widget, 100 );
}

MainWindow::~MainWindow()
{
    delete ui;
}
