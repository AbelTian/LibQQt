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
#ifdef __EMBEDDED_LINUX__
        setTextFont("/usr/local/Trolltech/lib/fonts/wenquanyi.ttf", 14);
#endif
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


