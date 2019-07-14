#include "qqtapp.h"
#include "qqt-qt.h"
#include "qqtversion.h"
#include "qqtcore.h"
#include "qqtgui.h"
#include "qqtwindow.h"

int main ( int argc, char* argv[] )
{
#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)
    QApplication::setAttribute ( Qt::AA_EnableHighDpiScaling, true );
    QApplication::setAttribute ( Qt::AA_UseHighDpiPixmaps, true );
#endif

    QQTApp a ( argc, argv );

    QQTWindow w;
    w.show();

    return a.exec();
}
