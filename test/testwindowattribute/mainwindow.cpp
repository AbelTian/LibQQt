#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtwindowattribute.h>
#include <qqtwidgeteffect.h>

#include <QGraphicsEffect>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    setFullScreen ( this, true );
}

void MainWindow::on_pushButton_2_clicked()
{
    setFullScreen ( this, false );
}

void MainWindow::on_pushButton_3_clicked()
{
    setShadowEffect ( this );
}

void MainWindow::on_pushButton_4_clicked()
{
    graphicsEffect()->setEnabled ( false );
}

void MainWindow::on_pushButton_5_clicked()
{
    setMainWindow ( this, true );
}

void MainWindow::on_pushButton_6_clicked()
{
    setMainWindow ( this, false );
}

void MainWindow::on_pushButton_7_clicked()
{
    setFadeEffect ( this );
}
