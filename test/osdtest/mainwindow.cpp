#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtframe.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    ui->widget_2->setPixmap ( conf_root ( "a.png" ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
