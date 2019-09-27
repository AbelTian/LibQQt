#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtbodymover.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    ui->widget->installEventFilter ( new QQtBodyMover ( this ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
