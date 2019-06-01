#include "qqtsql.h"

QSqlDatabase managerDB;

QSqlDatabase newDatabaseConnection()
{
    QUuid uuid = QUuid::createUuid();
    //qDebug() << uuid.toString();
    return QSqlDatabase::addDatabase ( DB_TYPE, uuid.toString() );
}


//opened
//useDatabase
void setDatabaseName ( QSqlDatabase& dbinst, QString dbName )
{
    if ( dbinst.isOpen() )
        dbinst.close();

    dbinst.setDatabaseName ( QString ( "%1" ).arg ( dbName ) );

    if ( !dbinst.open() )
    {
        QMessageBox::warning ( 0, QObject::tr ( "QSQLITE %1 Error" ).arg ( dbinst.databaseName() ),
                               dbinst.lastError().text() );
        return;
    }
}


void openDatabase ( QSqlDatabase& dbinst )
{
    if ( dbinst.isOpen() )
        return;

    if ( !dbinst.open() )
    {
        QMessageBox::warning ( 0, QObject::tr ( "QSQLITE %1 Error" ).arg ( dbinst.databaseName() ),
                               dbinst.lastError().text() );
        return;
    }
}


void closeDatabase ( QSqlDatabase& dbinst )
{
    dbinst.close();
}

void useDatabase ( QSqlDatabase& dbinst, QString dbName )
{
    setDatabaseName ( dbinst, dbName );
}

void deleteDatabaseConnection ( QString connectionName )
{
    QSqlDatabase::removeDatabase ( connectionName );
}

void deleteDatabaseConnection ( QSqlDatabase& dbinst )
{
    QString connectionName = dbinst.connectionName();
    deleteDatabaseConnection ( connectionName );
}
