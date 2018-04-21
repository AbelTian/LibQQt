#include "qqtmainglform.h"
#include "ui_qqtmainglform.h"

QQtMainGLForm::QQtMainGLForm ( QWidget* parent ) :
    QQtOpenGLWindow ( parent ),
    ui ( new Ui::QQtMainGLForm )
{
    ui->setupUi ( this );
}

QQtMainGLForm::~QQtMainGLForm()
{
    delete ui;
}
