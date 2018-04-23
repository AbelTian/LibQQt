#include "mainwindow.h"
#include <QQtApplication>
#include "qqtobjectmanager.h"

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    QQtObjectFactory::registerObject<QObject>();
    QObject* o = QQtObjectFactory::createObject ( "QObject" );
    pline() << o;

    MainWindow w;
    w.show();

    return a.exec();
}
