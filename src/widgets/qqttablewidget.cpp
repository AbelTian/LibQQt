#include "qqttablewidget.h"
#include "ui_qqttablewidget.h"

#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqtsql.h"

QQTTableWidget::QQTTableWidget(QWidget *parent) :
    QQTTableView(parent),
    ui(new Ui::QQTTableWidget)
{
    ui->setupUi(this);
    m_db = newDatabaseConn();
    m_model = new QQTTableModel(this, m_db);
    setModel(m_model);
    /*
     * 如果没有这个函数，程序存在启动崩溃的情况。
     */
    setItemDelegate(new QSqlRelationalDelegate(this));
}

QQTTableWidget::~QQTTableWidget()
{
    delete ui;
}

void QQTTableWidget::setDB(QString db)
{
    if(db.isEmpty())
    {
        //TODO:
        closeDatabase(m_db);
        return;
    }

    setDatabaseName(m_db, db);
}

void QQTTableWidget::setTable(QString table)
{
    m_model->setTable(table);
}

void QQTTableWidget::query(QString excp)
{
    m_model->query(excp);
}

void QQTTableWidget::removeRow(int row)
{
    m_model->removeRow(row);
    m_model->submit();
}

void QQTTableWidget::removeRows(int column, QList<QStringList> ids)
{
    int rowCount = m_model->rowCount();
    int i = 0;
    while(i < rowCount)
    {
        QModelIndex idx = m_model->index(i, column);

        /*
         * 经过删除，真实的rowCount后的index无效
         */
        if(!idx.isValid())
            break;

        QString modelColValue = m_model->data(idx).toString();

        /*
         * 在ids中找到列值相等的，针对row进行删除，i不变；
         */
        QListIterator<QStringList> itor(ids);
        while(itor.hasNext())
        {
            QString colValue = itor.next().at(column);

            if(colValue == modelColValue)
            {
                removeRow(i); i--;
                break;
            }
        }
        i++;
    }
}

void QQTTableWidget::selectedRows(int column , QMap<int, QStringList> &ids)
{
    QModelIndexList l = selectionModel()->selectedRows(column);
    QModelIndex idx;
    foreach (idx, l) {
        QStringList l;
        for(int i = 0; i < m_model->columnCount(); i++)
            l << m_model->index(idx.row(), i).data().toString();
        ids.insert(idx.row(), l);
    }
}
