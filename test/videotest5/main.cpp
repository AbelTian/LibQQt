#include "mainwindow.h"
#include <QQtApplication>

int main ( int argc, char* argv[] )
{
    QApplication a ( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
