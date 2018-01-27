#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cedianudpprotocol.h"


MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    /*初始化端口*/
    qint32 nPort[9] = {0};

    for ( int i = 0 ; i < 9; i++ )
    {
        //int port = ui->widget_12->getLocalPort ( i + 1 );
        /*正式版*/
        //nPort[i] = port;
        /*有规律版*/
        nPort[i] = 7000 + i * 10;
        //pline() << nPort[i];
    }

    cedianUdpPort ( 5, nPort );
    // serialport example
    // tcpsocket example
    // websocket?
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}
