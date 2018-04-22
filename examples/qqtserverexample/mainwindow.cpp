#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    pm0 = QQtServerInstance ( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recvANotify ( const QQtProtocol* protocol, const QQtMessage* message )
{
    pline() << "";
}
