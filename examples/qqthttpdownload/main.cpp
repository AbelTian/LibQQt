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

    QQtDictionary dict;

    return a.exec();
}
