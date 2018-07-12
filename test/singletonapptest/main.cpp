#include "mainwindow.h"
#include <qqtsingleapplication.h>

int main ( int argc, char* argv[] )
{
    QQtSingleApplication a ( argc, argv );
    //QLocalServer::removeServer ( "QQtSingleTon" );
    MainWindow w;
    w.show();

    return a.exec();
}
