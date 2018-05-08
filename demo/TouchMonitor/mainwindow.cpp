#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    s0 = TouchMonitorInstance ( p0, this );
}

MainWindow::~MainWindow()
{
    delete ui;
}


QQtTcpClient* MainWindow::TouchMonitorInstance ( TouchMonitorProtocol*& protocol, QObject* parent )
{
    static TouchMonitorProtocol* p0 = NULL;
    if ( !p0 )
    {
        p0 = new TouchMonitorProtocol ( parent );
    }
    protocol = p0;

    static QQtTcpClient* s0 = NULL;
    if ( !s0 )
    {
        s0 = new QQtTcpClient ( parent );
        s0->installProtocol ( p0 );
        //s0->setServer
        //s0->sendConnectToHost();
    }

    return s0;
}
