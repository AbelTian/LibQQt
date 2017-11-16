#include "qqttablemodel.h"

QQTTableModel::QQTTableModel(QObject* parent, QSqlDatabase db):
    QSqlRelationalTableModel(parent, db)
{
}

void QQTTableModel::query(QString filter)
{
    setFilter(filter);
    select();
}

QVariant QQTTableModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
    case Qt::TextAlignmentRole:
    case Qt::DisplayRole:
    case Qt::CheckStateRole:
    default:
        break;
    }

    return QSqlRelationalTableModel::data(index, role);
}


bool QQTTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QSqlRelationalTableModel::setData(index, value, role);
}

Qt::ItemFlags QQTTableModel::flags(const QModelIndex& index) const
{
    return QSqlRelationalTableModel::flags(index);
}
