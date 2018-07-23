#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qqtcolorwidget.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    ui->lineEdit->setText ( "0x863356" );
    ui->widget->setColor ( QRgb ( ui->lineEdit->text().toInt() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->setColor ( QRgb ( ui->lineEdit->text().toInt() ) );
    ui->widget->setAutoFillBackground ( true );
    ui->widget->update();
}
