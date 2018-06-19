#include "widget.h"
#include <QQtApplication>

int main(int argc, char *argv[])
{
    QQtApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
