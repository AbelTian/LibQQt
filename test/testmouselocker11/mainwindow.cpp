#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtwidgets.h>
#include <qqtframemouselocker.h>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}



