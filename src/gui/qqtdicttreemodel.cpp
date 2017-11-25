#include "qqtdicttreemodel.h"
#include "qqtcore.h"
#include <QModelIndex>
#include <QFile>

QQtDictTreeModel::QQtDictTreeModel ( QObject* parent ) : QQtTreeModel ( parent )
{

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

bool QQtDictTreeModel::query ( QString condition )
{
    Q_UNUSED ( condition )
    //TODO:
    return true;
}

