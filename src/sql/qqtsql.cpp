#include "qqtsql.h"

QSqlDatabase newDatabaseConn()
{
    QUuid uuid = QUuid::createUuid();
    //qDebug() << uuid.toString();
    return QSqlDatabase::addDatabase(DB_TYPE, uuid.toString());
}


//opened
//useDatabase
void setDatabaseName(QSqlDatabase &db, QString dbName)
{
    if(db.isOpen())
        db.close();

    db.setDatabaseName(QString("%1/%2").arg(DB_PATH).arg(dbName));

    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("QSQLITE %1 Error").arg(db.databaseName()),
                             db.lastError().text());
        return;
    }
}


void openDatabase(QSqlDatabase &db)
{
    if(db.isOpen())
        return;

    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("QSQLITE %1 Error").arg(db.databaseName()),
                             db.lastError().text());
        return;
    }
}


void closeDatabase(QSqlDatabase &db)
{
    db.close();
}
