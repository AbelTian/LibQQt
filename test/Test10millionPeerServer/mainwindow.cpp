#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <test10millionpeerserverprotocol.h>

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
    QQtProtocolManager* p0;
    Test10millionPeerServerInstance ( p0, this );
}
