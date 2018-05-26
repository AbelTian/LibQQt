#include "mainwindow.h"
#include <QApplication>

//libQQt v2.4 以后，这个例子已经废弃
int main ( int argc, char* argv[] )
{
    QApplication a ( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
