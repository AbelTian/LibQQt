#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qqtshadowwidget.h"
#include <QGraphicsDropShadowEffect>
#include <customshadoweffect.h>

//windows下使用，主窗口是不可能实现shadow的。
//无论在哪个平台，子控件shadow都可以实现。

#include <mainform.h>

#include <testshadowwidget.h>

#include <testshadowwidget2.h>

#include <qqtwidgets.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

#if 0
    //shadow 不管用
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius ( 10 );
    shadow->setColor ( QColor ( 0, 0, 0, 160 ) );
    shadow->setOffset ( 5, 5 );
    this->setGraphicsEffect ( shadow );
    this->setWindowFlag ( Qt::FramelessWindowHint, true );

    //...
    //shadow 不管用
    CustomShadowEffect* bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius ( 20.0 );
    bodyShadow->setDistance ( 6.0 );
    bodyShadow->setColor ( QColor ( 0, 0, 0, 80 ) );
    this->setGraphicsEffect ( bodyShadow );
    // ...

    //shadow 不管用，对子控件管用了。
    MainForm* form = new MainForm();
    form->show();


    //单独设置frameless，不管用
    //单独设置透明，全黑了
    //一起设置，不管用
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius ( 10 );
    shadow->setColor ( QColor ( 0, 0, 0, 160 ) );
    shadow->setOffset ( 5, 5 );
    setWindowFlag ( Qt::FramelessWindowHint );
    setAttribute ( Qt::WA_TranslucentBackground );
    ui->centralWidget->setGraphicsEffect ( shadow );


    //对子控件管用
    //难道就没有管用的方法了吗？
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius ( 10 );
    shadow->setColor ( QColor ( 0, 0, 0, 160 ) );
    shadow->setOffset ( 5, 5 );
    this->setGraphicsEffect ( shadow );
    this->setWindowFlag ( Qt::FramelessWindowHint, true );
    this->setAttribute ( Qt::WA_TranslucentBackground );


    //一片空白，必须设置图片才会管用。
    //设置颜色，不管用
    //必须在main函数里，在这里是不会显示的。
    //shadow 不管用。必须设置图片才管用。
    TestShadowWidget w;
    w.show();


    //不放在主函数不显示。
    TestShadowWidget2 w;
    w.setGeometry ( 400, 300, 800, 600 );
    moveCenter ( &w );
    w.show();
#endif


}

MainWindow::~MainWindow()
{
    delete ui;
}
