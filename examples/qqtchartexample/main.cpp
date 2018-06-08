#include "mainwindow.h"
#include <QQtApplication>
#include "qqtcore.h"

int main(int argc, char* argv[])
{

    QQtApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
