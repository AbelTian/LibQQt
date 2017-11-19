#include "qqttablemodel.h"

QQtTableModel::QQtTableModel(QObject* parent, QSqlDatabase db):
    QSqlRelationalTableModel(parent, db)
{
}

void QQtTableModel::query(QString filter)
{
    setFilter(filter);
    select();
}

QVariant QQtTableModel::data(const QModelIndex& index, int role) const
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


bool QQtTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QSqlRelationalTableModel::setData(index, value, role);
}

Qt::ItemFlags QQtTableModel::flags(const QModelIndex& index) const
{
    return QSqlRelationalTableModel::flags(index);
}
