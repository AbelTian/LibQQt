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
        QApplication::setApplicationName ( "exquisite" );
        QApplication::setOrganizationName ( "QQt" );
        QApplication::setOrganizationDomain ( "www.qqt.com" );
        //setQSSStyle();
#ifdef __EMBEDDED_LINUX__
        QString fontfile = QProcessEnvironment::systemEnvironment().value("QTDIR");
        fontfile += "/lib/fonts/wenquanyi.ttf";
        int fontsize = 14;

        //ignored
        //QFontDatabase db;
        pline() << "ziti buged";
        //pline() << db.families();
        //pline() << db.styles("WenQuanYi Zen Hei");
        //if( db.hasFamily("WenQuanYi Zen Hei") ){
            //pline() << "dddd";
        //}
        int fontID = QFontDatabase::addApplicationFont ( fontfile );
        pline() << "font file:" << fontfile;
        pline() << "font id:" << fontID << "family size:" << QFontDatabase::applicationFontFamilies ( fontID ).size();
        QString ziti = QFontDatabase::applicationFontFamilies ( fontID ).at ( 0 );
        pline() << ziti;
        //QFont font = db.font("WenQuanYi Zen Hei", "Medium", 14);

        QFont font ( ziti, fontsize );
        QApplication::setFont ( font );
        //setTextFont(fontfile, 14);
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


