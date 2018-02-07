#include <QCoreApplication>
#include <QDebug>
#include <qqtapplication.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );
    qDebug() << "ccc";
    return a.exec();
}
