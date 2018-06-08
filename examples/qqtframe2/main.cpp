#include "mainwindow.h"
#include <QQtApplication>
#include <qqtapplication.h>
#include <qqtframe.h>
#include <QSettings>
#include <qqtcore.h>

class MyApp : public QQtApplication
{
public:
    explicit MyApp ( int& argc, char** argv ) : QQtApplication ( argc, argv ) {
        QQtApplication::setOrganizationName ( "qqtframe" );
        QQtApplication::setOrganizationDomain ( "www.qqtframe.com" ); // 专为Mac OS X 准备的
        QQtApplication::setApplicationName ( "QQtFrame" );
    }
};

int main ( int argc, char* argv[] )
{
    MyApp a ( argc, argv );

    MainWindow w;
    w.show();

    return a.exec();
}
