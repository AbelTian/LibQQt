#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileSystemModel"
#include "QDirModel"
#include <QApplication>
#include <qqtsqltreemodel.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    QFileSystemModel* model = new QFileSystemModel ( this );
    //model->setRootPath ( "/Users/abel/Develop/a0-develop/a0-qqtfoundation/examples" );
    QDirModel* model2 = new QDirModel ( this );
    ui->tv0->setModel ( model2 );
    ui->tv0->setRootIndex ( model2->index ( qApp->applicationDirPath() ) );

    QQtSqlTreeModel* md0 = new QQtSqlTreeModel ( this );
    ui->tv1->setModel ( md0 );
    md0->setAbsoluteFilePath ( "/Users/abel/Develop/d1-product/App/db/Manager.db" );
    md0->query();
}

MainWindow::~MainWindow()
{
    delete ui;
}
