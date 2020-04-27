#include <qqtdicthelper.h>

QQtDictionary& QQtGetDictNode ( QQtDictionary& rootDict, QList<QString>& keyList1, bool numberAsString )
{
    QListIterator<QString> itor ( keyList1 );
    QQtDictionary* pdict = &rootDict;
    while ( itor.hasNext() )
    {
        const QString& key = itor.next();
        QQtDictionary& dict = *pdict;

        if ( numberAsString )
        {
            pdict = & ( dict[key] );
            continue;
        }

        bool ok;
        uint nkey = key.toUInt ( &ok );
        if ( ok )
            pdict = & ( dict[nkey] );
        else
            pdict = & ( dict[key] );
    }
    QQtDictionary& dict = *pdict;
    return dict;
}

QQtOrderedDictionary& QQtGetDictNode ( QQtOrderedDictionary& rootDict, QList<QString>& keyList1, bool numberAsString )
{
    QListIterator<QString> itor ( keyList1 );
    QQtOrderedDictionary* pdict = &rootDict;
    while ( itor.hasNext() )
    {
        const QString& key = itor.next();
        QQtOrderedDictionary& dict = *pdict;

        if ( numberAsString )
        {
            pdict = & ( dict[key] );
            continue;
        }

        bool ok;
        uint nkey = key.toUInt ( &ok );
        if ( ok )
            pdict = & ( dict[nkey] );
        else
            pdict = & ( dict[key] );
    }
    QQtOrderedDictionary& dict = *pdict;
    return dict;
}
