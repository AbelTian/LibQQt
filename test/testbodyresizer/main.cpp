#include "mainwindow.h"
#include <QQtApplication>
#include <mainwidget.h>

int main ( int argc, char* argv[] )
{
    //QQtApplication::setHighDpiScaling();
    QQtApplication a ( argc, argv );

    //MainWindow w;
    //w.show();

    MainWidget w;
    w.show();

    return a.exec();
}
