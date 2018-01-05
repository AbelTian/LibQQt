#ifndef QQTSQLQUERY_H
#define QQTSQLQUERY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <qqtsql.h>

class QQtSqlQuery : public QObject
{
    Q_OBJECT
public:
    explicit QQtSqlQuery(QObject *parent = nullptr);
    virtual ~QQtSqlQuery() {}

signals:

public slots:

private:

};

#endif // QQTSQLQUERY_H
