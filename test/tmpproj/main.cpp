#include "tempwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TempWidget w;
    w.show();

    return a.exec();
}
