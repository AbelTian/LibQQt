#include "mainwindow.h"
#include <QApplication>

#include "qqtsubprotocoltest.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QQtSubProtocolTest* p = new QQtSubProtocolTest();
    QByteArray bytes = "CCCCCCCC";
    p->translator(bytes);

    MainWindow w;
    w.show();

    return a.exec();
}
