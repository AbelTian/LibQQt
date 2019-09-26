#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtbodydroptoimageeffect.h>
#include <qqtframe.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    ui->widget->setPixmap ( conf_root ( "logo.png" ) );
    ui->widget->setAcceptDrops ( true );
    ui->widget_2->setAcceptDrops ( true );

    QQtBodyDropImageEffect* effect = new QQtBodyDropImageEffect ( this );
    ui->widget->installEventFilter ( effect );
    ui->widget_2->installEventFilter ( effect );
}

MainWindow::~MainWindow()
{
    delete ui;
}
