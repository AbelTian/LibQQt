#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtwidgets.h>

#include <qqtchildbodymover.h>
#include <qqtbodyresizer.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    //setGeometry ( 100, 200, 800, 600 );

    QQtChildBodyMover* h = new QQtChildBodyMover ( this );
    //ui->widget_3->installEventFilter ( h );
    //ui->widget_4->installEventFilter ( h );
    //ui->widget_5->installEventFilter ( h );

    QQtBodyResizer* h2 = new QQtBodyResizer ( this );
    //ui->widget_3->installEventFilter ( h2 );
    //ui->widget_4->installEventFilter ( h2 );
    //ui->widget_5->installEventFilter ( h2 );

    ui->widget_3->setContentsMargins ( 5, 5, 5, 5 );
    ui->widget_4->setContentsMargins ( 5, 5, 5, 5 );
    ui->widget_5->setContentsMargins ( 5, 5, 5, 5 );

}

MainWindow::~MainWindow()
{
    delete ui;
}



