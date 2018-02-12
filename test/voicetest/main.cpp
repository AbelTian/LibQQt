#include "mainwindow.h"
#include <QApplication>
#include <qqtwidgets.h>
#include <qqtapplication.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    MainWindow w;
    w.show();
    w.showMaximized();

    return a.exec();
}
