#include "qqtsqlquery.h"

QQtSqlQuery::QQtSqlQuery ( QSqlResult* r ) : QSqlQuery ( r ) {}

QQtSqlQuery::QQtSqlQuery ( const QString& query, QSqlDatabase db ) : QSqlQuery ( query, db ) {}

QQtSqlQuery::QQtSqlQuery ( QSqlDatabase db ) : QSqlQuery ( db ) {}

QQtSqlQuery::QQtSqlQuery ( const QQtSqlQuery& other ) : QSqlQuery ( other ) {}

QQtSqlQuery& QQtSqlQuery::operator= ( const QQtSqlQuery& other )
{
    const QSqlQuery& refOther = other;
    QSqlQuery& refThis = *this;
    refThis = refOther;
    return *this;
}

bool QQtSqlQuery::insert ( const QString& table, const QStringList& names, const QStringList& values )
{
    int length = names.count();
    int count = values.count();

    if ( length != count )
    {
        return false;
    }

    QString sql = QString ( "insert into " ) + table + QString ( "(" );

    //pline() << names;
    //pline() << values;

    int i;

    for ( i = 0; i < length; i++ )
    {
        sql = sql + names.value ( i );

        if ( i < length - 1 )
        {
            sql += QString ( "," );
        }
        else
        {

            sql = sql + QString ( ")" );
        }
    }

    sql = sql + QString ( "values (" );

    for ( i = 0; i < count; i++ )
    {
        sql = sql + QString ( "'" ) + values.value ( i ) + QString ( "'" );

        if ( i < count - 1 )
        {
            sql = sql + QString ( "," );
        }
        else
            sql = sql + QString ( ")" );
    }


    return exec ( sql );
}

bool QQtSqlQuery::insert ( const QString& table, const QStringList& names, const QList<qreal>& values )
{
    int length = names.count();
    int count = values.count();

    if ( length != count )
    {
        return false;
    }

    QString sql = QString ( "insert into " ) + table + QString ( "(" );

    //pline() << names;
    //pline() << values;

    int i;

    for ( i = 0; i < length; i++ )
    {
        sql = sql + names.value ( i );

        if ( i < length - 1 )
        {
            sql += QString ( "," );
        }
        else
        {

            sql = sql + QString ( ")" );
        }
    }

    sql = sql + QString ( "values (" );

    for ( i = 0; i < count; i++ )
    {
        sql = sql + QString ( "'" ) + values.value ( i ) + QString ( "'" );

        if ( i < count - 1 )
        {
            sql = sql + QString ( "," );
        }
        else
            sql = sql + QString ( ")" );
    }


    return exec ( sql );
}

bool QQtSqlQuery::update ( const QString& table, const QStringList& names, const QStringList& values,
                           const QString& expression )
{
    if ( names.size() != values.size() )
    {
        return false;
    }

    /*UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值*/
    QString sql = QString ( "update " ) + table + QString ( " set " );

    for ( int i = 0; i < names.size(); i++ )
    {
        sql = sql + names.value ( i );
        sql = sql + QString ( " = '" );
        sql = sql + values.value ( i );
        sql = sql + QString ( "'" );

        if ( i != names.size() - 1 )
        {
            sql = sql + QString ( " ," );
        }
    }

    sql = sql + QString ( " where " ) + expression;
    return exec ( sql );
}

bool QQtSqlQuery::del ( const QString& table, const QString& srcDatacloum, const QString& strData )
{
    /*DELETE FROM 表名称 WHERE 列名称 = 值*/
    QString sql = QString ( "delete from " ) + table + QString ( " where " )
                  + srcDatacloum + QString ( "='" ) + strData + QString ( "'" );

    return exec ( sql );
}

void QQtSqlQuery::getValues ( const QString& table, QStringList& values, const int index )
{
    QString sql = QString ( "select * from " ) + table;
    exec ( sql );

    while ( next() )
    {
        values << value ( index ).toString();
    }
}

void QQtSqlQuery::getValues ( const QString& table, QStringList& values, const QString& srcDatacloum,
                              const QString& strData, const int index )
{
    QString sql = QString ( "select * from " ) + table + QString ( " where " ) + srcDatacloum + QString ( "='" ) + strData +
                  QString ( "'" );

    exec ( sql );

    while ( next() )
    {
        values << value ( index ).toString();
    }
}

void QQtSqlQuery::getValues ( const QString& table, QStringList& values, const QString filter, const int ilimit,
                              const int ioffset, const int index )
{
    QString sql = QString ( "select * from " ) + table + QString ( filter ) + QString ( " limit " ) + ilimit +
                  QString ( " offset " ) + ioffset;

    exec ( sql );

    while ( next() )
    {
        values << value ( index ).toString();
    }
}

int QQtSqlQuery::getSize ( QString& table )
{
    QString sql = QString ( "select count(*) from " ) + table;
    exec ( sql );

    if ( next() )
        return value ( 0 ).toInt();
}
