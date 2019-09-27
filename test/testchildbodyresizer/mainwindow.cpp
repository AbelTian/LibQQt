#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtbodyresizer.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    ui->widget->installEventFilter ( new QQtBodyResizer ( this ) );
    ui->widget->setContentsMargins ( 10, 10, 10, 10 );
    ui->widget->setMouseTracking ( true );
}

MainWindow::~MainWindow()
{
    delete ui;
}
