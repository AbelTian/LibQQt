#include "qqtsqltreemodel.h"
#include "qqtcore.h"
#include "qqtsql.h"

QQtSqlTreeModel::QQtSqlTreeModel ( QObject* parent ) :
    QQtTreeModel ( parent )
{
    m_db = newDatabaseConnection();
}

void QQtSqlTreeModel::setFilePath ( QString dbname )
{
    if ( dbname.isEmpty() )
    {
        return;
    }

    setDatabaseName ( m_db, dbname );
}

void QQtSqlTreeModel::setAbsoluteFilePath ( QString dbname )
{
    if ( dbname.isEmpty() )
    {
        return;
    }

    if ( m_db.isOpen() )
        m_db.close();

    m_db.setDatabaseName ( QString ( "%1" ).arg ( dbname ) );

    if ( !m_db.open() )
    {
        QMessageBox::warning ( 0, QObject::tr ( "QSQLITE %1 Error" ).arg ( m_db.databaseName() ),
                               m_db.lastError().text() );
        return;
    }
}

bool QQtSqlTreeModel::query ( QString condition )
{
    Q_UNUSED ( condition )
    //TODO:
    return parseDatabase();
}

bool QQtSqlTreeModel::parseDatabase()
{
    QStringList tables = m_db.tables ( QSql::Tables );
    pline() << tables;
    QStringListIterator itor ( tables );

    while ( itor.hasNext() )
    {
        QString table = itor.next();
        parseTable ( table );
    }

    return true;
}

bool QQtSqlTreeModel::parseTable ( QString tableName )
{
    QQtTableModel* mdl = new QQtTableModel ( this, m_db );
    mdl->setTable ( tableName );
    mdl->query ( "" );
    tableModelList.push_back ( mdl );;

    QStandardItem* itemParent = new QStandardItem;
    itemParent->setData ( tableName, Qt::EditRole );
    appendRow ( itemParent );

    if ( columnCount() < mdl->columnCount() )
        setColumnCount ( mdl->columnCount() );

    for ( int i = 0; i < mdl->rowCount(); i++ )
    {
        QStandardItem* _item = new QStandardItem;
        _item->setData ( mdl->index ( i, 0 ).data ( Qt::DisplayRole ), Qt::EditRole );
        itemParent->appendRow ( _item );

        for ( int j = 1; j < mdl->columnCount(); j++ )
        {
            QStandardItem* __item = new QStandardItem;
            __item->setData ( mdl->index ( i, j ).data ( Qt::DisplayRole ), Qt::EditRole );
            //pline() << __item->data(Qt::EditRole).toByteArray();
            itemParent->setChild ( _item->index().row(), j, __item );
            //setItem(indexFromItem(_item).row(), j, __item);
        }
    }

    return true;
}
