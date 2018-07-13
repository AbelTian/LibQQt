#include "mainwindow.h"
#include <qqtsingletonapplication.h>

int main ( int argc, char* argv[] )
{
    QQtSingleTonApplication a ( argc, argv );
    //QLocalServer::removeServer ( "QQtSingleTon" );
    MainWindow w;
    w.show();

    return a.exec();
}
