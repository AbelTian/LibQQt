#include "mainwindow.h"
#include <QQtApplication>

#include "qqtsubprotocoltest.h"


int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    //测试一下，数据字段不够，内部如何处理。
    QQtSubProtocolTest* p = new QQtSubProtocolTest();
    QByteArray bytes = "CCCCCCCC";
    p->translator ( bytes );

    //这个例程里，讲解了QQt Application Framework里network module的功能。
    //这是一个例子，
    //这个app处在一个计算机节点上，这个节点有很多网络功能。
    //1. 和下位机通过串口通信 收发信令
    //2. 和网络服务器通过网络通信 收发数据
    //3. 和用户通过串口通信 收发用户命令
    //4. 和局域网用户通过局域网通信 收发局域网数据
    //在这个计算机节点上，这个app通信功能繁重，然而，它还有复杂的页面功能，如此繁重的功能累加，这一个app能不能胜任？答案是能，而且高效率。
    //有很多人，喜欢把这块放到线程中处理，完全没必要，因为Qt Library已经使用了高效的epoll、select、multi-thread做了这些工作，你写个app为什么要重做一遍？这是不是很不合理？
    //LibQQt就架设在Qt Runtime和Qt App之间，提供QQt Application Framework（请参照Android操作系统分层）。

    MainWindow w;
    w.show();

    return a.exec();
}
