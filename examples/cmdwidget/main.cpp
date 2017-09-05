#include "cmdwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CmdWidget w;
    w.show();

    return a.exec();
}
