#include "mainwindow.h"
#include <QApplication>
#include <QQtApplication>
#include <qqtcore.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    MainWindow w;
    //w.show();

    //赋值给byte 8个字节 uint64。
    QByteArray array;
    quint64 a0 = 12345678;
    array << a0;

    //取出来 int64
    qint64 b0;
    array >> b0;

    //检查int64对不对？
    pline() << b0;

    //windows
    //经过测试，结果正确。

    return 0;//a.exec();
}
