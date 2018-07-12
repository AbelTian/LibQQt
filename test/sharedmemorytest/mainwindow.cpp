#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSharedMemory>
#include <QSharedData>
#include <QSharedDataPointer>
#include <QSharedPointer>


MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    //这个地方，不用detach就能被删除。所以必须用static初始化保持。
    //这里加个static保持就够了，下边的初始化Value是按照用户自己的意愿。理论上需要初始化一下。
    static MyValue a ( "key" );

    //给个初始化的数。
    a.initializer();
    a.setString ( "This is a test value" );
    a.packer();
    pline() << "初始化：" << a.getString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MyValue b ( "key" );
    b.initializer();
    //读取里面的数值，读出来。
    b.parser();
    //...干点什么
    pline() << "b 读取：" << b.getString();

    //给个新的值，设进去。
    b.setString ( "This is b value written by b." );
    b.packer();
    //...干点什么
    pline() << "b 写入：" << b.getString();
}

void MainWindow::on_pushButton_2_clicked()
{
    MyValue a ( "key" );
    a.initializer();
    //读取里面的数值，读出来。
    a.parser();
    //...干点什么
    pline() << "a 读取：" << a.getString();

    //给个新的值，设进去。
    a.setString ( "This is a value written by a." );
    a.packer();
    //...干点什么
    pline() << "a 写入：" << a.getString();
}
