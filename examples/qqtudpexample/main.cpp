#include "mainwindow.h"
#include <QQtApplication>

//libQQt v2.4 以后，这个例子已经废弃
int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
