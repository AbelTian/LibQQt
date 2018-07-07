#include "mainform.h"
#include "ui_mainform.h"
#include "qqtframelesshelper.h"

MainForm::MainForm ( QWidget* parent ) :
    QQtWidget ( parent ),
    ui ( new Ui::MainForm )
{
    ui->setupUi ( this );
    setAttribute ( Qt::WA_TranslucentBackground, true );

    //如果需要鼠标可以移动窗体。
    //QQtFramelessHelper* h = new QQtFramelessHelper ( this );
    //h->addDragWidget ( this );

    //这是使用QQtTitleBar的标准过程，请参见mainform.ui。
    setWindowIcon ( QIcon ( "logo.ico" ) );
    setWindowTitle ( "This is a main form test form." );

    //setPixmap ( "rose.png" );
}

MainForm::~MainForm()
{
    delete ui;
}
