#include "qqtlistview.h"
#include "ui_qqtlistview.h"

QQTListView::QQTListView(QWidget *parent) :
    QListView(parent),
    ui(new Ui::QQTListView)
{
    ui->setupUi(this);
}

QQTListView::~QQTListView()
{
    delete ui;
}
