#include "qqtdicttablemodel.h"
#include "qqtcore.h"

#include <QModelIndex>

#include "qqtcore.h"

#define p3line() qDebug()

QQtDictTableModel::QQtDictTableModel ( QObject* parent ) : QStandardItemModel ( parent )
{

}

void QQtDictTableModel::setDictionary ( QQtDictionary* dict )
{
    this->pdict = dict;
}

QQtDictionary* QQtDictTableModel::dictionary()
{
    return pdict;
}

void QQtDictTableModel::query ( QQtDictionary& dict )
{
    pdict = &dict;

    while ( rowCount() > 0 )
    {
        removeRow ( 0 );
    }

    if ( dict.getType() == QQtDictionary::DictList )
    {
        const QQtDictionary& node = dict;
        for ( int i = 0; i < node.getList().size(); i++ )
        {
            QStandardItem* item = new QStandardItem;
            appendRow ( item );

            QList<QQtDictionary>& l = node.getList();
            const QQtDictionary& node1 = l[i];
            if ( node1.getType() == QQtDictionary::DictList )
            {
                if ( node1.count() > columnCount() )
                    setColumnCount ( node1.count() );

                QList<QStandardItem*> itemList;
                for ( int j = 0; j < node1.getList().size(); j++ )
                {
                    QStandardItem* item1 = new QStandardItem;

                    QList<QQtDictionary>& l1 = node1.getList();
                    const QQtDictionary& node2 = l1[j];
                    //p3line() << node2;
                    if ( node2.getType() == QQtDictionary::DictValue )
                    {
                        item1->setData ( node2.getValue(), Qt::EditRole );
                        //p3line() << item1;
                        //p3line() << item1->data ( Qt::EditRole );
                        //item1->setText ( node2.getValue().toString() );
                    }
                    itemList.append ( item1 );
                }
                //p3line() << itemList;

                item->appendColumn ( itemList );
            }
        }
    }
}
