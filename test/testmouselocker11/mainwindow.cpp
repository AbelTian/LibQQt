#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtwidgets.h>
#include <qqtframemouselocker.h>
#include <qqtbodymouselocker.h>
#include <qqtcore.h>

QQtBodyMouseLocker* helper;
MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    //setGeometry ( 100, 200, 800, 600 );
    //上边有两个，下边这个是不能设置locker的，WINAPI的问题。
    //QQtFrameMouseLocker* helper = new QQtFrameMouseLocker ( this );
    //this->centralWidget()->installEventFilter ( helper );

    //FocusIn有bug，当从外部接触内部标题栏，FocusIN激发，鼠标摁住移动窗口只能在一个小范围移动。必须重新摁一次才能整体移动。
    //需要解决。

    //bug: 需要过滤掉鼠标点击标题栏的移动作用
    //bug: 如何使窗口刚刚启动的时候，就获取到鼠标？WindowActivate

    helper = new QQtBodyMouseLocker ( this );
    ui->widget->installEventFilter ( helper );
    //ui->widget_2->installEventFilter ( helper );
    //helper->addWindow ( ui->widget );
    //helper->addWindow ( ui->widget_2 );

    //可选
    //helper->startCapture();
    //可选
    ui->widget->setMouseTracking ( true );
    //ui->widget_2->setMouseTracking ( true );

    this->installEventFilter ( this );
}

MainWindow::~MainWindow()
{
    //以下二选1，必选
    helper->stopCapture();
    //无论如何要保证MouseLocker优先于ui被释放。
    //delete helper;
    //这个不行的
    //helper->deleteLater();
    delete ui;
}





bool MainWindow::eventFilter ( QObject* watched, QEvent* event )
{
    if ( event->type() == QEvent::Paint )
        return QObject::eventFilter ( watched, event );
    switch ( event->type() )
    {
        case QEvent::MouseButtonPress:
        {
            QRect r0 = frameGeometry();
            QRect r1 = geometry();
            pline() << r0 << r1;
            QMouseEvent* e = ( QMouseEvent* ) event;
            if ( r0.contains ( e->globalPos() ) && !r1.contains ( e->globalPos() ) )
                helper->stopCapture();
            return false;
        }
        case QEvent::MouseButtonRelease:
        {
            QRect r0 = frameGeometry();
            QRect r1 = geometry();
            QMouseEvent* e = ( QMouseEvent* ) event;
            if ( r0.contains ( e->globalPos() ) && !r1.contains ( e->globalPos() ) )
                helper->stopCapture();
            return false;
        }
    }
    return QMainWindow::eventFilter ( watched, event );
}
