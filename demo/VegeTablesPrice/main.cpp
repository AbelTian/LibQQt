#include "mainwindow.h"
#include <QApplication>
#include <qqtapplication.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}

