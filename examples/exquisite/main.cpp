#include "mainwindow.h"
#include <qqtapplication.h>

class MainApplication: public QQtApplication
{
public:
    explicit MainApplication ( int argc, char* argv[] ) :
        QQtApplication ( argc, argv ) {
        QApplication::setApplicationName ( "exquisite" );
        QApplication::setOrganizationName ( "QQt" );
        QApplication::setOrganizationDomain ( "www.qqt.com" );
        setQSSStyle();
    }
    virtual ~MainApplication() {}
};

int main(int argc, char* argv[])
{
    MainApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


