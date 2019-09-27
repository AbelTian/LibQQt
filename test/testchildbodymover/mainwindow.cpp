#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtchildbodymover.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    ui->widget->installEventFilter ( new QQtChildBodyMover ( this ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
