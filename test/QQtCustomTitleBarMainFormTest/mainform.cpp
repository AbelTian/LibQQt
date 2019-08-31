#include "mainform.h"
#include "ui_mainform.h"
#include "qqtbodymover.h"

MainForm::MainForm ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::MainForm )
{
    ui->setupUi ( this );

    //如果需要鼠标可以移动窗体。
    QQtBodyMover* h = new QQtBodyMover ( this );
    //此处不能安装给主窗体，在UNIX系统下，会和QQtTitleBar的鼠标移动共同作用，产生并和移动现象。
    ui->widget_2->installEventFilter ( h );

    //这是使用QQtTitleBar的标准过程，请参见mainform.ui。
    setWindowIcon ( QIcon ( "logo.ico" ) );
    setWindowTitle ( "This is a main form test form." );
}

MainForm::~MainForm()
{
    delete ui;
}
