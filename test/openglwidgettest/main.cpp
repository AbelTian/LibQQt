#include "mainwindow.h"
#include <QQtApplication>
#include <qqtmainglform.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    QQtMainGLForm w;
    w.show();

    return a.exec();
}
