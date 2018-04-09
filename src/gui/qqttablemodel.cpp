#include "qqttablemodel.h"

QQtTableModel::QQtTableModel ( QObject* parent, QSqlDatabase db ) :
    QSqlRelationalTableModel ( parent, db )
{
    //这个带关系的tablemodel类QSqlRelationalTableModel有个问题：如果不对tableview的item设置代理，Release版本下tableview会莫名的崩溃。
    //QQtTableView里面，已经设置了空的代理，规避崩溃。
    //用户程序当中，也可以持续设置为有意义的item代理，请留意。
    //QSqlTableModel没有这个问题。
}

void QQtTableModel::query ( QString filter )
{
    setFilter ( filter );
    select();
}

QVariant QQtTableModel::data ( const QModelIndex& index, int role ) const
{
    switch ( role )
    {
        case Qt::TextAlignmentRole:
        case Qt::DisplayRole:
        case Qt::CheckStateRole:
        default:
            break;
    }

    return QSqlRelationalTableModel::data ( index, role );
}


bool QQtTableModel::setData ( const QModelIndex& index, const QVariant& value, int role )
{
    return QSqlRelationalTableModel::setData ( index, value, role );
}

Qt::ItemFlags QQtTableModel::flags ( const QModelIndex& index ) const
{
    return QSqlRelationalTableModel::flags ( index );
}
