#include "widget.h"
#include "ui_widget.h"

#include "qqtframelesshelper.h"

Widget::Widget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QQtFramelessHelper* frameless = new QQtFramelessHelper(this);
    frameless->addDragWidget(this);
    frameless->setCloseButton(ui->pushButtonClose);
    frameless->setMaximizedButton(ui->pushButtonMax);
    frameless->setRestoreButton(ui->pushButtonRestore);
    frameless->setMinimizedButton(ui->pushButtonMin, false);
}

Widget::~Widget()
{
    delete ui;
}
