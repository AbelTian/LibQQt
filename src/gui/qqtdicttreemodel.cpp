#include "qqtdicttreemodel.h"
#include <QModelIndex>
#include <QFile>

#include "qqtcore.h"

QQtDictTreeModel::QQtDictTreeModel ( QObject* parent ) : QQtTreeModel ( parent )
{

}

void QQtDictTreeModel::setDictionary ( QQtDictionary* dict )
{
    this->pdict = dict;
    query ( "" );
}

QQtDictionary* QQtDictTreeModel::dictionary()
{
    return pdict;
}

void QQtDictTreeModel::setFilePath ( QString dictfile )
{
    QFile file ( dictfile );

    if ( !file.open ( QFile::ReadOnly | QFile::Text ) )
    {
        pline() << "Error: Cannot read file " << qPrintable ( dictfile )
                << ": " << qPrintable ( file.errorString() )
                << endl;
        return;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;


    file.close();

    clear();

    return;
}

void QQtDictTreeModel::parseDictNodeToModel ( const QQtDictionary& node, QStandardItem& item )
{

}

bool QQtDictTreeModel::query ( QString condition )
{
    Q_UNUSED ( condition )
    //TODO:
    return true;
}

