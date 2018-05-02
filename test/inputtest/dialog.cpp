#include "dialog.h"
#include "ui_dialog.h"
#include "qqtinput.h"

Dialog::Dialog ( QWidget* parent ) :
    QDialog ( parent ),
    ui ( new Ui::Dialog )
{
    ui->setupUi ( this );

    //这个字体，有的平台不显示。
    //qApp->setFont ( QFont ( "Microsoft YaHei", 10 ) );

    //不挑平台，强制显示。
    QQtInput::Instance()->Init ( "min", "control", "QQT", 14, 14 );
    setFocus();
}

Dialog::~Dialog()
{
    delete ui;
}
