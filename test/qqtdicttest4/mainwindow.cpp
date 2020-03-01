#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>

#include <qqtdictionary.h>
#define p3line() qDebug().space()

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QFile file ( "b.xml" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();;

    QQtDictionary dict;
    dict.fromXML ( bytes );
    p3line() << "root:" << dict;
#if 1
    p3line() << "xml:" << dict["xml"];
    p3line() << "person:" << dict["person"];

    p3line() << "phone-number:" << dict["person"]["phone-number"];
    p3line() << "address:" << dict["person"]["address"];
    p3line() << "username:" << dict["person"]["username"];

    //节点多类型！
    dict["person"]["phone-number"].setType ( QQtDictionary::DictMap );
    p3line() << "phone-number:" << dict["person"]["phone-number"]["__attributes__"];
    dict["person"]["phone-number"].setType ( QQtDictionary::DictValue );
    p3line() << "phone-number:" << dict["person"]["phone-number"];

#elif 1
    p3line() << "xml:" << dict["xml"];
    p3line() << "book:" << dict["bookstore"]["book"];
    p3line() << "book:" << dict["bookstore"]["book"]["__attributes__"];
#else
    p3line() << "PRPM_IN301010UV01:" << dict["PRPM_IN301010UV01"];
    p3line() << "PRPM_IN301010UV01:" << dict["PRPM_IN301010UV01"]["id"];
    p3line() << "PRPM_IN301010UV01:" << dict["PRPM_IN301010UV01"]["controlActProcess"];
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}
