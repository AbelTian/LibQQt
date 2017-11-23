#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qqtbluetoothmanager.h>
#include <qqtcore.h>
QQtBluetoothManager* manager = NULL;

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    // bluetooth example
    manager = QQtBluetoothManager::Instance ( this );
    connect ( manager, SIGNAL ( addDevice ( QBluetoothDeviceInfo ) ), this, SLOT ( addDevice ( QBluetoothDeviceInfo ) ) );
    connect ( manager, SIGNAL ( addService ( QBluetoothServiceInfo ) ), this,
              SLOT ( addService ( QBluetoothServiceInfo ) ) );
    ui->lw0->addItem ( manager->address().toString() );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnRefresh_clicked()
{
    ui->lw1->clear();
    manager->refresh();
}


void MainWindow::addDevice ( QBluetoothDeviceInfo s )
{
    ui->lw1->addItem ( s.address().toString() );
}

void MainWindow::addService ( QBluetoothServiceInfo s )
{
    pline() << s.serviceClassUuids();
}
