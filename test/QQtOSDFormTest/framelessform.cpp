#include "framelessform.h"
#include "ui_framelessform.h"
#include <qqtbodymover.h>

FramelessForm::FramelessForm ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::FramelessForm )
{
    ui->setupUi ( this );
    setWindowFlag(Qt::FramelessWindowHint, true);
    QQtBodyMover* h = new QQtBodyMover ( this );
    installEventFilter(h);
}

FramelessForm::~FramelessForm()
{
    delete ui;
}
