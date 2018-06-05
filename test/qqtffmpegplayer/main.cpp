#include <QQtApplication>
#include "qqtwindow.h"

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    QQTWindow w;
    w.show();

    return a.exec();
}
