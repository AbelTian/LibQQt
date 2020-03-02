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
#if 0

    QFile file ( "b.xml" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();;

    QQtDictionary dict;
    dict.fromXML ( bytes );
    p3line() << "root:" << dict;
    p3line() << "xml:" << dict["xml"];
    p3line() << "person:" << dict["person"];

    p3line() << "address:" << dict["person"]["address"];
    p3line() << "username:" << dict["person"]["username"];

    p3line() << "phone-number:" << dict["person"]["phone-number"];
    p3line() << "phone-number.__attributes__:" << dict["person"]["phone-number"]["__attributes__"];
    p3line() << "phone-number.#text:" << dict["person"]["phone-number"]["#text"];

#elif 0

    QFile file ( "c.xml" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();;

    QQtDictionary dict;
    dict.fromXML ( bytes );
    p3line() << "root:" << dict;
    p3line() << "xml:" << dict["xml"];

    p3line() << "bookstore:" << dict["bookstore"];

    p3line() << "book:" << dict["bookstore"]["book"];
    p3line() << "book1:" << dict["bookstore"]["book"][0];
    p3line() << "book1.__attributes__:" << dict["bookstore"]["book"][0]["__attributes__"];
    p3line() << "book1.price:" << dict["bookstore"]["book"][0]["price"];
    p3line() << "book1.author:" << dict["bookstore"]["book"][0]["author"];

    p3line() << "book4:" << dict["bookstore"]["book"][3];
    p3line() << "book4.__attributes__:" << dict["bookstore"]["book"][3]["__attributes__"];
    p3line() << "book4.price:" << dict["bookstore"]["book"][3]["price"];
    p3line() << "book4.author:" << dict["bookstore"]["book"][3]["author"];
    QQtDictionaryListIterator itor ( dict["bookstore"]["book"][3]["author"].getList() );
    while ( itor.hasNext() )
    {
        const QQtDictionary& d0 = itor.next();
        p3line() << d0["#text"].getValue().toString();
    }
#else

    QFile file ( "a.xml" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();;

    QQtDictionary dict;
    dict.fromXML ( bytes );
    p3line() << "root:" << dict;
    p3line() << "PRPM_IN301010UV01:"    << dict["PRPM_IN301010UV01"];
    p3line() << "id:"                   << dict["PRPM_IN301010UV01"]["id"];
    p3line() << "controlActProcess:"    << dict["PRPM_IN301010UV01"]["controlActProcess"];
    p3line() << "subject:"              << dict["PRPM_IN301010UV01"]["controlActProcess"]["subject"];
    QQtDictionary& d0 =
        dict["PRPM_IN301010UV01"]["controlActProcess"]["subject"]["registrationRequest"]["subject1"]["healthCareProvider"];

    p3line() << "subject1.healthCareProvider:" << d0;
    p3line() << "subject1.healthCareProvider.__attributes__:" << d0["code"]["__attributes__"];
    p3line() << "subject1.healthCareProvider.#comment:" << d0["#comment"];

#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}
