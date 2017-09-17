#ifndef QQTSQLDEFINE_H
#define QQTSQLDEFINE_H

#include <QWidget>
#include <QUuid>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include <QElapsedTimer>
#include <QDesktopWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <qqt-local.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DB_TYPE "QSQLITE"
#define DB_PATH "./db/"

#ifdef __cplusplus
}
#endif  /* __cplusplus */

QQTSHARED_EXPORT QSqlDatabase newDatabaseConn();

QQTSHARED_EXPORT void setDatabaseName(QSqlDatabase &db, QString dbName);

QQTSHARED_EXPORT void openDatabase(QSqlDatabase &db);

QQTSHARED_EXPORT void closeDatabase(QSqlDatabase &db);

#endif // QQTSQLDEFINE_H
