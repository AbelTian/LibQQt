#include "qqtapp.h"
#include "qqt-qt.h"
#include "qqtversion.h"
#include "qqtcore.h"
#include "qqtgui.h"
#include "qqtwindow.h"

int main(int argc, char* argv[])
{
    QQTApp a(argc, argv);

    QQTWindow w;
    w.show();

    return a.exec();
}
