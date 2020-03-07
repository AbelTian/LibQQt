#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qfile.h>
#include <qqtdictionary.h>

#include <QDebug>
#define p3line() qDebug()

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QFile file ( "mainwindow.ui" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();;

    QQtDictionary dict;
    dict.fromXML ( bytes );
    p3line() << "root:" << dict;
    p3line() << "__processinginstruction__:" << dict["__processinginstruction__"];
    p3line() << "person:" << dict["person"];

    p3line() << "address:" << dict["person"]["address"];
    p3line() << "username:" << dict["person"]["username"];


    p3line() << "phone-number:" << dict["person"]["phone-number"];
    p3line() << "phone-number1:" << dict["person"]["phone-number"][0];
    p3line() << "phone-number1.__attributes__:" << dict["person"]["phone-number"][0]["__attributes__"];
    p3line() << "phone-number1.#text:" << dict["person"]["phone-number"][0]["#text"];

    QByteArray bytes0 = dict.toXML ( 4 );
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_2->append ( bytes0 );

    bytes0 = dict.toJson ( QJsonDocument::Indented ) ;
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_3->append ( bytes0 );

    bytes0 = dict.toYAML() ;
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_4->append ( bytes0 );

    bytes0 = dict["ui"]["widget"].toINI() ;
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_5->append ( bytes0 );

    bytes0 = dict["ui"]["layoutdefault"]["__attributes__"].toProperties() ;
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_6->append ( bytes0 );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked ( bool checked )
{

}
