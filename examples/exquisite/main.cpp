#include "mainwindow.h"
#include <qqtapplication.h>
#include <QProcess>

class MainApplication: public QQtApplication
{
public:
    explicit MainApplication ( int argc, char* argv[] ) :
        QQtApplication ( argc, argv ) {
        QApplication::setApplicationName ( "exquisite" );
        QApplication::setOrganizationName ( "QQt" );
        QApplication::setOrganizationDomain ( "www.qqt.com" );
        //setQSSStyle();
#ifdef __EMBEDDED_LINUX__
        QString value = QProcessEnvironment::systemEnvironment().value("QTDIR");
        value += "/lib/fonts/wenquanyi.ttf";
        setTextFont(value, 14);
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


