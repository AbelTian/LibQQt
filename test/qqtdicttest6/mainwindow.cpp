#include "mainwindow.h"
#include "ui_mainwindow.h"

#include  <QFile>

#include <qqtdictionary.h>
#include <qqtdicttreemodel.h>
#include <qqttableview.h>

QQtDictionary dict;
QQtDictTreeModel* model;

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QFile file ( "weather.json" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();

    dict.fromJson ( bytes );

    ui->textBrowser->append ( QString ( bytes ) );

    model = new QQtDictTreeModel ( ui->treeView );
    ui->treeView->setModel ( model );
    //model->query ( dict );

    QQtDictionary d0;
    d0 = "ABBB";
    model->query ( d0 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked ( bool checked )
{
    model->query ( dict );
}

void MainWindow::on_pushButton_2_clicked ( bool checked )
{
    model->query ( dict );
}
