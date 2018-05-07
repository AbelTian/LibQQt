#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <qqtosdwidget.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QQtOSDWidget* w = new QQtOSDWidget ( 0 );
    w->show();
    w->setGeometry ( 0, 0, 400, 400 );
}

MainWindow::~MainWindow()
{
    delete ui;
}


