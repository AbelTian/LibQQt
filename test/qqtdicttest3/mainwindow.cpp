#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtdictionary.h"

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
    pline() << "emptyObject:";
    pline() << dict["emptyObject"];

}

MainWindow::~MainWindow()
{
    delete ui;
}
