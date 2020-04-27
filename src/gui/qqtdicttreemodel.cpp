#include "qqtdicttreemodel.h"

#include <QModelIndex>
#include <QStandardItem>

#include "qqtcore.h"

#define p3line() qDebug()

QQtDictTreeModel::QQtDictTreeModel ( QObject* parent ) : QQtTreeModel ( parent )
{
}

void QQtDictTreeModel::setDictionary ( QQtDictionary* dict )
{
    this->pdict = dict;
}

QQtDictionary* QQtDictTreeModel::dictionary()
{
    return pdict;
}

void QQtDictTreeModel::query ( QQtDictionary& dict )
{
    pdict = &dict;

    while ( rowCount() > 0 )
    {
        removeRow ( 0 );
    }

    //p3line() << item ( 0, 0 ); //0
    //p3line() << item ( -1, -1 ); //0
    packDictionaryToTreeModel ( dict, 0 );
}

QStringList QQtDictTreeModel::getFullName ( const QModelIndex& index )
{
    if ( !index.isValid() )
        return QStringList();

    QStringList fullname;
    QModelIndex tempIndex = index;//row 0 parent? NO，在里边。
    while ( tempIndex.isValid() )
    {
        QModelIndex parentIndex = tempIndex.parent();
        int row = tempIndex.row();
        QString data = this->index ( row, 0, parentIndex ).data().toString();
        fullname.push_front ( data );

        tempIndex = tempIndex.parent();
    }
    return fullname;
}

bool QQtDictTreeModel::isLeafNode ( const QModelIndex& index )
{
    if ( !index.isValid() )
        return false;

    return index.child ( 0, 0 ).isValid() ? false : true;
}

bool QQtDictTreeModel::isRootNode ( const QModelIndex& index )
{
    if ( !index.isValid() )
        return false;

    return index.parent().isValid() ? false : true;
}


void QQtDictTreeModel::packDictionaryToTreeModel ( const QQtDictionary& node, QStandardItem* pobject )
{
    switch ( node.getType() )
    {
        case QQtDictionary::DictValue:
        {
            //null, bool, double, string
            //p3line() << node.getValue().type();
            QStandardItem* item = new QStandardItem;
            item->setData ( node.getValue(), Qt::EditRole );
            pobject ? pobject->appendRow ( item ) : appendRow ( item );
            break;
        }
        case QQtDictionary::DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QQtDictionary>& l = node.getList();
                QStandardItem* item = new QStandardItem;
                item->setText ( QString::number ( i + 1 ) );
                pobject ? pobject->appendRow ( item ) : appendRow ( item );
                packDictionaryToTreeModel ( l[i], item );
            }
            break;
        }
        case QQtDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin(); itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& key = itor.key();
                const QQtDictionary& srcvalue = itor.value();
                QStandardItem* item = new QStandardItem;
                item->setText ( key );
                pobject ? pobject->appendRow ( item ) : appendRow ( item );
                packDictionaryToTreeModel ( srcvalue, item );
            }
            break;
        }
        case QQtDictionary::DictMax:
        default:
            break;
    }
}

void QQtDictTreeModel::setFilePath ( QString dictfile )
{
    Q_UNUSED ( dictfile )
    //TODO:
    return;
}

bool QQtDictTreeModel::query ( QString condition )
{
    Q_UNUSED ( condition )
    //TODO:
    return true;
}

