#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

typedef struct tagBtnIconTable2
{
    QString pixmap[5];

    tagBtnIconTable2() {}

    QString pixMap ( int index ) {}
    void setPixMap ( int index, QString pix ) {}
    void initNormal ( QString normal, QString press ) {}
    void initCheck ( QString uncheck, QString check ) {}
    void initOther ( QString hover, QString disable ) {}
    const QString& operator[] ( int index ) const {}
    QString& operator [] ( int index ) {}
} TBtnIconTable2;

Q_DECLARE_METATYPE ( TBtnIconTable2 )

int main ( int argc, char* argv[] )
{
    QApplication a ( argc, argv );

    QVariant vv;
    TBtnIconTable2 icc;
    icc.pixmap[0] = "icon";

    vv.setValue<TBtnIconTable2> ( icc );

    /*tested on arm linux, qt5.5.1*/
    qDebug() << vv.value<TBtnIconTable2>().pixmap[0];

    //MainWindow w;
    //w.show();

    return 0;//a.exec();
}
