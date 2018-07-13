#include "mainwindow.h"
#include <qqtsingletonapplication.h>
#include <QLocalServer>
#include <QDebug>

int main ( int argc, char* argv[] )
{
    QQtSingleTonApplication a ( argc, argv );
    //QLocalServer::removeServer ( "QQtSingleTon" );
    QLocalServer b;
    qDebug() << "listen:?" << b.listen ( "QQtSingleTon" );
    qDebug() << "listen:?" << b.isListening();
    MainWindow w;
    w.show();

    return a.exec();
}
