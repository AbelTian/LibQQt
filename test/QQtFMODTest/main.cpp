#include "mainwindow.h"
#include <QQtApplication>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );
    //开启日志系统，终端打印不能实时输出。
    a.setWriteLogSystem ( true );

    MainWindow w;
    w.show();

    return a.exec();
}
