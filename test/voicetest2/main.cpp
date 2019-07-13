#include "mainwindow.h"
#include <QQtApplication>
#include <qqtwidgets.h>
#include <qqtapplication.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    MainWindow w;
    w.show();

#ifdef __ANDROID__
    w.showMaximized();
#endif

    return a.exec();
}
