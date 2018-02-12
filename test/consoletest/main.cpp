#include <QCoreApplication>
#include <QDebug>
#include <qqtapplication.h>
#include <qqtcore.h>
#include <qqtdictionary.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    qDebug() << "ccc";

    QQtDictNode dict;
    dict[0][1][2][3][4]["my name"][5][6] = "a string";
    pline() << dict[0][1][2][3][4]["my name"][5][6].getValue().toString();

    QTextStream qin ( stdin );
    pline() << "你的输入：" << qin.readLine();

    return 0;
    return a.exec();
}
