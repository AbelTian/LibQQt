#include "cmdwidget.h"
#include <QQtApplication>

int main(int argc, char *argv[])
{
    QQtApplication a(argc, argv);

    CmdWidget w;
    w.show();

    return a.exec();
}
