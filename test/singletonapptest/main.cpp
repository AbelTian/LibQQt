#include "mainwindow.h"
#include <qqtsingleapplication.h>

int main ( int argc, char* argv[] )
{
    QQtSingleApplication a ( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
