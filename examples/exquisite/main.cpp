#include "mainwindow.h"
#include <qqtapplication.h>
#include <QProcess>
#include "qfontdatabase.h"
#include "qqtcore.h"

class MainApplication: public QQtApplication
{
public:
    explicit MainApplication ( int argc, char* argv[] ) :
        QQtApplication ( argc, argv ) {

        QQtApplication::setApplicationName ( "exquisite" );
        QQtApplication::setOrganizationName ( "QQt" );
        QQtApplication::setOrganizationDomain ( "www.qqt.com" );

#ifdef __EMBEDDED_LINUX__
        QString fontfile = QProcessEnvironment::systemEnvironment().value ( "QTDIR" );
        fontfile += "/lib/fonts/wenquanyi.ttf";
        int fontsize = 14;
        //setTextFont(fontfile, fontsize);
#endif
    }
    virtual ~MainApplication() {}
};

int main ( int argc, char* argv[] )
{
    MainApplication a ( argc, argv );

    MainWindow w;
    w.show();

    return a.exec();
}


