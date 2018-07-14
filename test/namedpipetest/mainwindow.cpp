#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qqtnamedpipe.h>
#include <qqtlocalserver.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    //QQtLocalServer::removeServer ( "QQtNamedPipeServer" );
    static QQtNamedPipe hold ( "mypipe0" );
    hold.initializer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QQtNamedPipe a ( "mypipe0" );
    a.initializer();
    QByteArray bytes = "AAAAAAAAAAAAAAAA pipe1 write";
    a.write ( bytes );
    pline() << bytes;
}

void MainWindow::on_pushButton_2_clicked()
{
    QQtNamedPipe a ( "mypipe0" );
    a.initializer();
    QByteArray bytes = a.read ( 15 );
    pline() << bytes;
}

void MainWindow::on_pushButton_3_clicked()
{
    QQtNamedPipe a ( "mypipe0" );
    a.initializer();
    QByteArray bytes = "BBBBBBBBBBBBB pipe1 write";
    a.write ( bytes );
    pline() << bytes;
}

void MainWindow::on_pushButton_4_clicked()
{
    QQtNamedPipe a ( "mypipe0" );
    a.initializer();
    QByteArray bytes = a.read ( 40 );
    pline() << bytes;
}
