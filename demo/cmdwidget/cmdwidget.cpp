#include "cmdwidget.h"
#include "ui_cmdwidget.h"
#include <QDesktopWidget>

CmdWidget::CmdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CmdWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    move(qApp->desktop()->width() / 2 - width() / 2,
         qApp->desktop()->height() / 2 - height() / 2 - 100);
}

CmdWidget::~CmdWidget()
{
    delete ui;
}
