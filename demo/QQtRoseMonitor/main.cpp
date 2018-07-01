#include "mainwindow.h"
#include <QQtApplication>
#include <qqtosdform.h>
#include <qqtwidgets.h>
#include <qqtframelesshelper.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    QQtWidget w;
    w.setWindowTitle ( "QQtRoseMonitor" );
    w.setWindowFlag ( Qt::WindowStaysOnTopHint, true );
    //w.setWindowFlag ( Qt::FramelessWindowHint, true );
    //w.setAttribute ( Qt::WA_TranslucentBackground, true );
    QPalette pal = w.palette();
    pal.setColor ( QPalette::Background, QColor ( 0, 0, 0 ) );
    //w.setPalette ( pal );
    w.setMinimumSize ( 420, 720 );
    w.setGeometry ( 0, 0, 420, 720 );
    moveCenter ( &w );
    w.setPixmap ( "rose.png" );
    w.show();

    return a.exec();
}
