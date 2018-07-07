#include "framelessform.h"
#include "ui_framelessform.h"
#include <qqtframelesshelper.h>

FramelessForm::FramelessForm ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::FramelessForm )
{
    ui->setupUi ( this );
    QQtFramelessHelper* h = new QQtFramelessHelper ( this );
    h->addDragWidget ( this );
}

FramelessForm::~FramelessForm()
{
    delete ui;
}
