#include "tempwidget.h"
#include <QQtApplication>

int main(int argc, char *argv[])
{
    QQtApplication a(argc, argv);
    TempWidget w;
    w.show();

    return a.exec();
}
