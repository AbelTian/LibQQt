#include "qqtsqltreemodel.h"
#include "qqtcore.h"
#include "qqtsql.h"

QQTSqlTreeModel::QQTSqlTreeModel(QObject* parent) :
    QQTTreeModel(parent)
{
    m_db = newDatabaseConn();
}

void QQTSqlTreeModel::setFilePath(QString dbname)
{
    if (dbname.isEmpty())
    {
        return;
    }

    setDatabaseName(m_db, dbname);
}

bool QQTSqlTreeModel::query(QString condition)
{
    Q_UNUSED(condition)
    //TODO:
    return parseDatabase();
}

bool QQTSqlTreeModel::parseDatabase()
{
    QStringList tables = m_db.tables(QSql::Tables);
    QStringListIterator itor(tables);

    while (itor.hasNext())
    {
        QString table = itor.next();
        parseTable(table);
    }

    return true;
}

bool QQTSqlTreeModel::parseTable(QString tableName)
{
    QQTTableModel* mdl = new QQTTableModel(this, m_db);
    mdl->setTable(tableName);
    mdl->query("");
    tableModelList.push_back(mdl);;

    QStandardItem* itemParent = new QStandardItem;
    itemParent->setData(tableName, Qt::EditRole);
    appendRow(itemParent);

    if (columnCount() < mdl->columnCount())
        setColumnCount(mdl->columnCount());

    for (int i = 0; i < mdl->rowCount(); i++)
    {
        QStandardItem* _item = new QStandardItem;
        _item->setData(mdl->index(i, 0).data(Qt::DisplayRole), Qt::EditRole);
        itemParent->appendRow(_item);

        for (int j = 1; j < mdl->columnCount(); j++)
        {
            QStandardItem* __item = new QStandardItem;
            __item->setData(mdl->index(i, j).data(Qt::DisplayRole), Qt::EditRole);
            //pline() << __item->data(Qt::EditRole).toByteArray();
            itemParent->setChild(_item->index().row(), j, __item);
            //setItem(indexFromItem(_item).row(), j, __item);
        }
    }

    return true;
}
