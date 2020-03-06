#include "mainwindow.h"
#include "ui_mainwindow.h"

#include  <QFile>

#include <qqtdictionary.h>
#include <qqtdicttreemodel.h>
#include <qqttableview.h>

#include <qqtdicttablemodel.h>

QQtDictionary dict;
QQtDictTreeModel* model;

#define p3line() qDebug()

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

    static QQtDictionary d0;
    d0 = "ABBB";
    model->query ( d0 );

    QQtDictTableModel* model1;
    model1 = new QQtDictTableModel ( ui->tableView );
    ui->tableView->setModel ( model1 );

    static QQtDictionary d1;
    d1[0][1] = "I Love You!";
    d1[0][2] = "I Love You!";
    d1[0][3] = "I Love You!";
    d1[0][5] = "I Love You!";

    d1[1][0] = "I Love You!";
    d1[1][2] = "I Love You!";
    d1[1][3] = "I Love You!";
    d1[1][5] = "I Love You!";


    d1[2][0] = "I Love You!";
    d1[2][1] = "I Love You!";
    d1[2][2] = "I Love You!";
    d1[2][4] = " kkkkkkkk";
    d1[2][5] = "I Love You!";
    d1[2][6] = "I Love You!";

    p3line() << d1;
    p3line() << d1[0];
    p3line() << d1[0][1];
    model1->query ( d1 );
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
    model->query ( dict["data"] );
}
