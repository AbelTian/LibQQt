#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <test10millionpeerclientprotocol.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signalStartTest()),
            this, SLOT(slotOnStarting()), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit signalStartTest();
}

void MainWindow::slotOnStarting()
{
    Test10millionPeerClientProtocol* p0;
    QQtTcpClient* r4;
    Test10millionPeerClientInstance(p0, this);
}
