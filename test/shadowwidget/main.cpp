#include "mainwindow.h"
#include <QQtApplication>
#include "qqtshadowwidget.h"

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    //MainWindow w;
    //w.show();



    QQtShadowWidget* w = new QQtShadowWidget();
    w->show();
    w->setGeometry ( 400, 500, 800, 600 );

    return a.exec();
}
