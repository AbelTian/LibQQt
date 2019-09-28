#include "mainwindow.h"
#include <QQtApplication>

#include <testshadowwidget.h>
#include <testshadowwidget2.h>
#include <testshadowwidget3.h>

#include <qqtshadowwidget.h>

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    //shadow，测试后，全都不管用。
    //MainWindow w;
    //w.show();

#if 0
    //shadow 不管用
    TestShadowWidget w;
    w.show();
#endif

#if 1
    //shadow 实现。需要美化下效果。
    TestShadowWidget2 w;
    w.show();
#endif

#if 0
    //shadow 发黑。里边正常。
    TestShadowWidget3 w;
    w.show();
#endif

#if 0
    //shadow 管用
    QQtShadowWidget* w = new QQtShadowWidget();
    //w->setWindowFlag ( Qt::FramelessWindowHint, true );
    //w->setAttribute ( Qt::WA_TranslucentBackground, true );
    w->setGeometry ( 400, 500, 800, 600 );
    w->show();
#endif

    return a.exec();
}
