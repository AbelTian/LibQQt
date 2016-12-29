#include "qqttreewidget.h"
#include "ui_qqttreewidget.h"

QQTTreeWidget::QQTTreeWidget(QWidget *parent) :
    QQTTreeView(parent),
    ui(new Ui::QQTTreeWidget)
{
    ui->setupUi(this);

    m_fs = new QQTFileSystem(this);
    m_model = new QQTTreeModel(this, m_fs);
    setModel(m_model);

    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));
    connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentRowChanged()));
}

QQTTreeWidget::~QQTTreeWidget()
{
    delete ui;
}

void QQTTreeWidget::query(QString path)
{
    QString file;
    m_fs->parse(path, m_prot, file);
    m_model->query(path);
    for(int i = 0; i < FILE_MAX; i++)
        m_model->setHeaderData(i, Qt::Horizontal, "");
    for(int i = 1; i < FILE_MAX; i++)
        setColumnHidden(i, true);
}

void QQTTreeWidget::removeRow()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!curIndex.isValid())
        return;

    m_model->removeRow(curIndex.row(), parIndex);
}

void QQTTreeWidget::currentRowChanged()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!curIndex.isValid())
        return;

    //根据是否文件夹进行判断
    if(parIndex.isValid())
        return;

        QString path = m_model->index(curIndex.row(), FILE_FILEPATH, parIndex).data().toString();
        pline() << m_prot << path;
        query(QString("%1%2").arg(m_prot).arg(path));

        //expand(curIndex);
}

void QQTTreeWidget::clicked(QModelIndex)
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!curIndex.isValid())
        return;

    //根据是否文件夹进行判断
    if(parIndex.isValid())
        return;

    QString type = m_model->index(curIndex.row(), FILE_TYPE, parIndex).data().toString();

    pline() << type;

    if(type == "dir")
    {
        if(isExpanded(curIndex))
            collapse(curIndex);
    else
            expand(curIndex);
    }
}
