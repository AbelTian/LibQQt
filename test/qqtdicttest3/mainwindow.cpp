#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtdictionary.h"

#include <QDebug>
//开头没有空格
//#define p3line() qDebug()
#define p3line() qDebug().space()

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    QFile file ( "a.json" );
    file.open ( QFile::ReadOnly );
    QByteArray json = file.readAll();
    file.close();

    QQtDictionary dict;
    dict.fromJson ( json );

    pline() << dict;
    pline() << "---------------------";
    pline() << "craft_names:";
    pline() << dict["craft_names"];
    pline() << "---------------------";
    pline() << "datas1:";
    pline() << dict["datas1"];
    pline() << "---------------------";
    pline() << "datas1:";
    pline() << dict["datas1"];
    pline() << "---------------------";
    pline() << "servletWrapper:";
    pline() << dict["servletWrapper"];
    pline() << "---------------------";
    pline() << "multipartRequestHandler:";
    pline() << dict["multipartRequestHandler"];
    pline() << "---------------------";
    pline() << "eud_names:";
    pline() << dict["eud_names"];
    pline() << "---------------------";
    pline() << "emptyObject:" << dict["emptyObject"];

    p3line() << dict;
    p3line() << "---------------------";
    p3line() << "craft_names:";
    p3line() << dict["craft_names"];
    p3line() << "---------------------";
    p3line() << "datas1:" << dict["datas1"];
    p3line() << "---------------------";
    p3line() << "datas1:";
    p3line() << dict["datas1"];
    p3line() << "---------------------";
    p3line() << "servletWrapper:" << dict["servletWrapper"];
    p3line() << "---------------------";
    p3line() << "multipartRequestHandler:" << dict["multipartRequestHandler"];
    p3line() << "---------------------";
    p3line() << "eud_names:";
    p3line() << dict["eud_names"];
    p3line() << "---------------------";
    p3line() << "emptyObject:" << dict["emptyObject"];

}

MainWindow::~MainWindow()
{
    delete ui;
}
