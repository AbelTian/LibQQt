#include "qqttabwidgetb.h"
#include "ui_qqttabwidgetb.h"

QQTTabWidgetB::QQTTabWidgetB(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::QQTTabWidgetB)
{
    ui->setupUi(this);
}

QQTTabWidgetB::~QQTTabWidgetB()
{
    delete ui;
}
