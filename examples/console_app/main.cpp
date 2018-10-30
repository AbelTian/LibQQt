#include <QCoreApplication>
#include <QDebug>
#include <qqtapplication.h>
#include <qqtcore.h>
#include <qqtdictionary.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    qDebug() << "ccc";

    QQtDictionary dict;
    dict[0][1][2][3][4]["my name"][5][6] = "a string";
    pline() << dict[0][1][2][3][4]["my name"][5][6].getValue().toString();

    //win32: 命令行输入 chcp 65501 乱码解除
#ifdef __WIN__
    //会导致清屏，请用户手动设置chcp纠正代码页。LibQQt程序一律为UTF-8编码输出。
    //system("chcp 65001");
#endif
    QTextStream qin ( stdin );
    pline() << "你的输入：" << qin.readLine();

    return 0;
    //return a.exec();
}
