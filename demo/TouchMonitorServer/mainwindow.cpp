#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <qqtosdwidget.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    //QQtOSDWidget* w = new QQtOSDWidget ( 0 );
    //w->show();
    //w->setGeometry ( 0, 0, 400, 400 );

    w0 = new ControlorWidget ( 0 );
    w0->hide();;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{

}
