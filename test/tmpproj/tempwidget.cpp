#include "tempwidget.h"
#include "ui_tempwidget.h"

TempWidget::TempWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TempWidget)
{
    ui->setupUi(this);
}

TempWidget::~TempWidget()
{
    delete ui;
}
