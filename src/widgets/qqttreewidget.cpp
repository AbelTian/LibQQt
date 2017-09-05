#include "qqttreewidget.h"
#include "ui_qqttreewidget.h"
#include "qqtxmltreemodel.h"

QQTTreeWidget::QQTTreeWidget(QWidget *parent) :
    QQTTreeView(parent),
    ui(new Ui::QQTTreeWidget)
{
    ui->setupUi(this);
}

QQTTreeWidget::~QQTTreeWidget()
{
    delete ui;
}
