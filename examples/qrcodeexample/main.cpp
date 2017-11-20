#include "mainwindow.h"
#include <QApplication>
#include "mainwidget.h"

int main ( int argc, char* argv[] )
{
    QApplication a ( argc, argv );

    //MainWindow w;
    QQtCustomQrDecodeWidget w;
    w.show();

    return a.exec();
}
