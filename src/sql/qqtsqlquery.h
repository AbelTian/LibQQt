#ifndef QQTSQLQUERY_H
#define QQTSQLQUERY_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <qqtsql.h>
#include <qqtcore.h>

class QQtSqlQuery : public QSqlQuery
{
public:
    explicit QQtSqlQuery ( QSqlResult* r );
    explicit QQtSqlQuery ( const QString& query = QString(), QSqlDatabase db = QSqlDatabase() );
    explicit QQtSqlQuery ( QSqlDatabase db );
    QQtSqlQuery ( const QQtSqlQuery& other );
    QQtSqlQuery& operator= ( const QQtSqlQuery& other );
    virtual ~QQtSqlQuery() {}

    /*
     * insert into <table> (<names>) values (<values>)
    */
    bool insert ( const QString& table, const QStringList& names, const QStringList& values );
    bool insert ( const QString& table, const QStringList& names, const QList<qreal>& values );
    /*
     * update <table> set <name1>='<value1>',<name2>='<value2>' where <expression>
    */
    bool update ( const QString& table, const QStringList& names, const QStringList& values, const QString& expression );
    /*
     * delete from <table> where <column>='<expression>'
    */
    bool del ( const QString& table, const QString& srcDatacloum, const QString& strData );
    /*
     * select * from <table>
     * column id
    */
    void getValues ( const QString& table, QStringList& values, const int index );
    /*
     * select * from <table> where <column> = '<expression>'
     * column id
    */
    void getValues ( const QString& table, QStringList& values, const QString& srcDatacloum, const QString& strData,
                     const int index );
    /*
     * select * from <table> <filter> limit <size1> offset <size2>
     * column id
    */
    void getValues ( const QString& table, QStringList& values, const QString filter, const int ilimit,
                     const int ioffset, const int index );
    /*
     * select count(*) from <table>
    */
    int getSize ( QString& table );

signals:

public slots:

private:
};

#endif // QQTSQLQUERY_H
