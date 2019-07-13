#include "qqtapp.h"
#include "qqt-qt.h"
#include "qqtversion.h"
#include "qqtcore.h"
#include "qqtgui.h"
#include "qqtwindow.h"

#include "qqtapplication.h"

int main ( int argc, char* argv[] )
{
    QQtApplication::setHighDpiScaling();
    QQtApplication a ( argc, argv );

    QQTWindow w;
    w.show();

    return a.exec();
}
