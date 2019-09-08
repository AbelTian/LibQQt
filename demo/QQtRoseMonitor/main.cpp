#include "mainwindow.h"
#include <QQtApplication>


#include <qgraphicseffect.h>
#include <qqtosdform.h>
#include <qqtwidgets.h>
#include <qqtbodymover.h>
#include <qqtframe.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    //MainWindow w;
    //w.show();


    QQtWidget w;
    w.setWindowTitle ( "QQtRoseMonitor" );
    w.setWindowFlag ( Qt::WindowStaysOnTopHint, true );
    w.setWindowFlag ( Qt::FramelessWindowHint, true );
    w.setAttribute ( Qt::WA_TranslucentBackground, true );
    QQtBodyMover* frameless = new QQtBodyMover ( &w );
    w.installEventFilter ( frameless );
    QPalette pal = w.palette();
    pal.setColor ( QPalette::Background, QColor ( 0, 0, 0 ) );
    //w.setPalette ( pal );
    w.setMinimumSize ( 420, 720 );
    w.setGeometry ( 0, 0, 420, 720 );
    moveCenter ( &w );
    w.setPixmap ( conf_root ( "rose.png" ) );
    w.show();

#if 0
    //顺便测试一下shadow。测试结果：对设置的图片管用了，在图片附近产生了阴影。
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius ( 10 );
    shadow->setColor ( QColor ( 0, 0, 0, 160 ) );
    shadow->setOffset ( 5, 5 );
    w.setGraphicsEffect ( shadow );
#endif
    return a.exec();
}
