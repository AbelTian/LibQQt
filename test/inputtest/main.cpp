#include "dialog.h"
#include <QQtApplication>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    Dialog w;
    w.show();

    return a.exec();
}
