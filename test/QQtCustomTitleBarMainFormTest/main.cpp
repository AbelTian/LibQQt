#include "mainform.h"
#include <QQtApplication>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    MainForm w;
    w.show();

    return a.exec();
}
