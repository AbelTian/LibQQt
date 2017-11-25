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

    QString tt;
    tt = QString ( "%1" ).sprintf ( "%4d", 13 );//"  13"
    tt = QString ( "%1" ).arg ( 13, 4, 10 );
    pline() << tt;

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

    QQtDictNode d0;
    d0["cc"] = "dd";
    pline() << d0["cc"].getValue();

    QQtDictNode d1;
    QQtDictNode d2 ( QVariant ( "CCCC" ) );
    d1.appendChild ( d2 );
    pline() << d1[0].getValue();
    d1[0] = "ff";
    pline() << d1[0].getValue();

    QQtDictNode d3;
    d3["cc"]["dd"] = "ee";
    pline() << d3["cc"]["dd"].getValue().toString();

    QQtDictNode d4;

    for ( int i = 0; i < 5; i++ )
    {
        QQtDictNode d ( QVariant ( QString::number ( i ) ) );
        d4.appendChild ( d );
    }

    pline() << d4.count();

    for ( int i = 0; i < d4.count(); i++ )
    {
        pline() << d4[i].getValue().toString();
    }

    QQtDictNode d5;

    /*后续有map操作，这一步就没有用了*/
    d5.appendChild ( "5.7" );
    d5.appendChild ( "5.8" );
    d5.appendChild ( "5.9" );

    /*后续有map操作，这一步就没有用了*/
    d5["5.7"].appendChild ( "5.7.2" );
    d5["5.7"].appendChild ( "5.7.3" );
    d5["5.7"].appendChild ( "5.7.4" );

    d5["5.7"]["5.7.4"].appendChild ( "xxx.dmg" );
    d5["5.7"]["5.7.4"][0].appendChild ( "xxx.dmg" );
    d5["5.7"]["5.7.4"][0].appendChild ( "2017-12-12" );
    d5["5.7"]["5.7.4"][0].appendChild ( "1.2G" );
    d5["5.7"]["5.7.4"][0].appendChild ( "Detail" );
    d5["5.7"]["5.7.4"][0].insertChild ( 4, "Detail2" );

    //pline() << "\n" << d5;
    pline() << "\n" << d5["5.7"];

    QQtMapNodeIterator itor ( d5["5.7"].getMap() );

    while ( itor.hasNext() )
    {
        itor.next();
        pline() << "\n" << itor.key() << itor.value();
    }

    pline () << d5["5.7"]["5.7.4"][0].getType();
    pline () << d5["5.7"]["5.7.4"][0].count();

    for ( int i = 0; i < d5["5.7"]["5.7.4"][0].count(); i++ )
    {
        pline() << d5["5.7"]["5.7.4"][0][i].getValue().toString();
    }

    QQtDictNode node = d5;
    pline() << node["5.7"]["5.7.4"][0][0].getValue().toString();

    /*在这里有list操作，前边"5.7"的map就没有用了*/
    /*但是再过去做过的list类型的操作都会被保留，也就是说中间出现过概念错误，没问题还保留着*/
    d5["5.7"].appendChild ( "5.7.5" );

    for ( int i = 0; i < d5["5.7"].count(); i++ )
    {
        pline() << d5["5.7"][i].getValue().toString();
    }

    char* cc = NULL;
    char* bb = "ddddd";

    QString ccq = QString ( "%1%2" ).arg ( cc ).arg ( bb );
    pline() << ccq;

    QQtQtIOWebPageParser webparser;
    webparser.startNewParse ( );

    MainWindow w;
    w.show();

    return a.exec();
}
