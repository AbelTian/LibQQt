#include "mainwindow.h"
#include <qqtsingletonapplication.h>
#include <QLocalServer>
#include <QDebug>

int main ( int argc, char* argv[] )
{
    QQtSingleTonApplication a ( argc, argv );
    a.setApplicationName ( "singletonapptest" );
    a.startSingleTonInstance();

    //QLocalServer::removeServer ( "singletonapptest" );
    QLocalServer b;
    qDebug() << "listen:?" << b.listen ( "singletonapptest" );
    qDebug() << "listen:?" << b.isListening();

    MainWindow w;
    w.show();

    return a.exec();
}
