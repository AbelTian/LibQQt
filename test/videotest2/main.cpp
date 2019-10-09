#include "mainwindow.h"
#include <QQtApplication>

int main ( int argc, char* argv[] )
{

    //高DPI下，需要支持
#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)
    //QApplication::setAttribute ( Qt::AA_EnableHighDpiScaling );
    //QApplication::setAttribute ( Qt::AA_UseHighDpiPixmaps );
#endif

    QQtApplication a ( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
