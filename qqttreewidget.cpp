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

void QQTTreeWidget::setModel(int type)
{
    switch(type)
    {
    case XMLTREE:
        mModel = new QQTXmlTreeModel(this);
        break;
    case SQLTREE:
        mModel = new QQTSqlTreeModel(this);
        break;
        //TODO:
    case LOCALTREE:
        mModel = new QQTFileSystemTreeModel(this);
        break;
        //TODO:
    case CLOUDTREE:
        //mModel = new QQTCloudTreeModel(this);
        break;
    }

    QQTTreeView::setModel(mModel);
}
