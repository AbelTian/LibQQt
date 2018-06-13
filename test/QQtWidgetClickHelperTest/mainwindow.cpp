#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtcore.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    ui->widget;
    ui->widget->setPixmap ( "" );

    connect ( ui->widget, SIGNAL ( click() ),
              this, SLOT ( setSum() ) );
    connect ( ui->widget, SIGNAL ( doubleClick() ),
              this, SLOT ( set2Sum() ) );
    connect ( ui->widget, SIGNAL ( longClick() ),
              this, SLOT ( set3Sum() ) );

    connect ( ui->widget_4, SIGNAL ( click() ),
              this, SLOT ( set31Sum() ) );
    connect ( ui->widget_4, SIGNAL ( doubleClick() ),
              this, SLOT ( set32Sum() ) );
    connect ( ui->widget_4, SIGNAL ( longClick() ),
              this, SLOT ( set33Sum() ) );

    connect ( ui->widget_2, SIGNAL ( click() ),
              this, SLOT ( set4Sum() ) );
    connect ( ui->widget_2, SIGNAL ( longClick() ),
              this, SLOT ( set5Sum() ) );

    connect ( ui->widget_3, SIGNAL ( click() ),
              this, SLOT ( set6Sum() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSum()
{
    sender();
    ui->textBrowser->append ( QString ( "%1 click" ).arg ( ui->widget->clickHelper()->totalClickNum() ) );;
}

void MainWindow::set2Sum()
{
    ui->textBrowser->append ( QString ( "%1 double click" ).arg ( ui->widget->clickHelper()->totalClickNum() ) );;
}

void MainWindow::set3Sum()
{
    ui->textBrowser->append ( QString ( "%1 long click" ).arg ( ui->widget->clickHelper()->totalClickNum() ) );;
}

void MainWindow::set31Sum()
{
    ui->textBrowser->append ( QString ( "child %1 click" ).arg ( ui->widget_4->clickHelper()->totalClickNum() ) );;
}

void MainWindow::set32Sum()
{
    ui->textBrowser->append ( QString ( "child %1 double click" ).arg ( ui->widget_4->clickHelper()->totalClickNum() ) );;
}

void MainWindow::set33Sum()
{
    ui->textBrowser->append ( QString ( "child %1 long click" ).arg ( ui->widget_4->clickHelper()->totalClickNum() ) );;
}

void MainWindow::set4Sum()
{
    ui->textBrowser_2->append ( QString ( "%1 click" ).arg ( ui->widget_2->clickHelper()->totalClickNum() ) );;
}

void MainWindow::set5Sum()
{
    ui->textBrowser_2->append ( QString ( "%1 long click" ).arg ( ui->widget_2->clickHelper()->totalClickNum() ) );;
}

void MainWindow::set6Sum()
{
    ui->textBrowser_3->append ( QString ( "%1 click" ).arg ( ui->widget_3->clickHelper()->totalClickNum() ) );;
}
