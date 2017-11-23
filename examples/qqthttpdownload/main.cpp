#include "mainwindow.h"
#include <QApplication>

#include "qqtobjectfactory.h"
#include "qqtcore.h"

int main ( int argc, char* argv[] )
{
    QApplication a ( argc, argv );

    QQtWidgetFactory::registerObject<QPushButton>();
    QObject* obj = QQtWidgetFactory::createObject ( "QPushButton" );
    pline() << obj->inherits ( "QWidget" );
    pline() << obj->inherits ( "QPushButton" );
    pline() << obj->inherits ( "QObject" );
    obj->setObjectName ( "bbb" );
    pline() << obj->objectName();
    QQtObjectParcel::registerObject ( obj );


    MainWindow w;
    w.show();

    return a.exec();
}
