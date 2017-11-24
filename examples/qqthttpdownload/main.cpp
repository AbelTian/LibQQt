#include "mainwindow.h"
#include <QApplication>

#include "qqtobjectfactory.h"
#include "qqtcore.h"
#include "qqthttpdownloadmanager.h"
#include "qqtapplication.h"
#include "qqtqtiowebpageparser.h"
#include "qqtdictionary.h"

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    /*
    QQtWidgetFactory::registerObject<QPushButton>();
    QObject* obj = QQtWidgetFactory::createObject ( "QPushButton" );
    pline() << obj->inherits ( "QWidget" );
    pline() << obj->inherits ( "QPushButton" );
    pline() << obj->inherits ( "QObject" );
    obj->setObjectName ( "bbb" );
    pline() << obj->objectName();
    QQtObjectParcel::registerObject ( obj );
    */

    //QQtQtIOWebPageParser webparser;
    //webparser.startNewParse ( );

    //MainWindow w;
    //w.show();

    QQtDict d0;
    d0["cc"] = "dd";
    qDebug() << d0["cc"].getValue();

    QQtDict d1;
    QQtDict d2 ( QVariant ( "CCCC" ) );
    d1.appendValue ( d2 );
    qDebug() << d1[0].getValue();
    d1[0] = "ff";
    qDebug() << d1[0].getValue();

    QQtDict d3;
    d3["cc"]["dd"] = "ee";
    qDebug() << d3["cc"]["dd"].getValue().toString();

    QQtDict d4;

    for ( int i = 0; i < 5; i++ )
    {
        QQtDict d ( QVariant ( QString::number ( i ) ) );
        d4.appendValue ( d );
    }

    qDebug() << d4.count();

    for ( int i = 0; i < d4.count(); i++ )
    {
        qDebug() << d4[i].getValue().toString();
    }

    QQtDict d5;
    d5.appendChild ( "5.7" );
    d5.appendChild ( "5.8" );
    d5.appendChild ( "5.9" );
    d5["5.7"].appendChild ( "5.7.2" );
    d5["5.7"].appendChild ( "5.7.3" );
    d5["5.7"].appendChild ( "5.7.4" );
    d5["5.7"]["5.7.4"].appendChild ( "xxx.dmg" );
    d5["5.7"]["5.7.4"]["xxx.dmg"].appendValue ( "xxx.dmg" );
    d5["5.7"]["5.7.4"]["xxx.dmg"].appendValue ( "2017-12-12" );
    d5["5.7"]["5.7.4"]["xxx.dmg"].appendValue ( "1.2G" );
    d5["5.7"]["5.7.4"]["xxx.dmg"].appendValue ( "Detail" );

    pline() << "\n" << d5["5.7"]["5.7.4"];

    return 0;//a.exec();
}
