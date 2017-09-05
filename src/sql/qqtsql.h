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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DB_TYPE "QSQLITE"
#define DB_PATH "./db/"

#ifdef __cplusplus
}
#endif  /* __cplusplus */

QSqlDatabase newDatabaseConn();

void setDatabaseName(QSqlDatabase &db, QString dbName);

void openDatabase(QSqlDatabase &db);

void closeDatabase(QSqlDatabase &db);

#endif // QQTSQLDEFINE_H