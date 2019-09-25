#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtwidgets.h>
#include <qqtframemouselocker.h>
#include <qqtbodymouselocker.h>
#include <qqtcore.h>
#include <qqtbodyresizer.h>

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

    ui->widget->installEventFilter ( this );

    //与BodyMouseLocker冲突，在locker的时候，请不要resizer。
    QQtBodyResizer* helper0 = new QQtBodyResizer ( this );
    ui->widget->installEventFilter ( helper0 );

    pline() << ui->widget->contentsMargins();
    ui->widget->setContentsMargins ( 20, 20, 20, 20 );
}

MainWindow::~MainWindow()
{
    //以下二选1，必选
    //helper->stopCapture();
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
        case QEvent::WindowActivate:
        {
            //原来答案在这里，用户如果希望窗口在activate的时候，目标窗口捕获鼠标，可是还要过滤掉标题栏，在这里实现！
            QMouseEvent* e = ( QMouseEvent* ) event;
            //QRect r0 = frameGeometry();
            //QRect r1 = geometry();
            //if ( r0.contains ( e->globalPos() ) && !r1.contains ( e->globalPos() ) )
            //    helper->stopCapture();

            QWidget& w = *this;
            QRect frameR0 = frameGeometry();
            QPoint p0, p1;
            p0 = frameR0.topLeft();
            p1 = frameR0.bottomRight();
            //p0 = w.mapToGlobal ( p0 );
            //p1 = w.mapToGlobal ( p1 );

            QPoint mousePos = QCursor::pos();

            qreal ratio = 1; //w.devicePixelRatioF();
            QRect r0 = QRect ( p0, p1 );
            QRect qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ),
                                QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );

            QRect r1 = rect();
            QRect qr1 = QRect ( w.mapToGlobal ( r1.topLeft() ), w.mapToGlobal ( r1.bottomRight() ) );
            r1 = geometry();

            if ( qr0.contains ( mousePos ) && !qr1.contains ( mousePos ) )
                helper->removeWindow ( ui->widget ); //helper->addWindow ( ui->widget );
            else
                helper->addWindow ( ui->widget );
            pline() << qr0 << qr1 << mousePos;
            event->accept();
            return true;

        }
        //可选
        case QEvent::WindowDeactivate:
        {
            //如果不是活动窗口，就失效。----很重要。
            helper->addClipCursor ( QRect ( 0, 0, 0, 0 ) );
            event->accept();
            pline() << "deactivate";
            return true;
        }
    }
    return QMainWindow::eventFilter ( watched, event );
}
