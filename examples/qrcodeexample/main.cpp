#include "mainwindow.h"
#include <QQtApplication>
#include "mainwidget.h"

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    //MainWindow w;
    QQtCustomQrDecodeWidget w;
    w.show();

    return a.exec();
}
