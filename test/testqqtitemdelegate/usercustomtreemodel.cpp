#include <usercustomtreemodel.h>

/**
 * dict["rfc000.txt"]
 *  ["type"] = "file"
 *  ["postfix"] = "txt"
 *  ["DownTime"] = ""
 *  ["DownStatus"] = ""
 *  ["DownProgress"] = ""
 *  ["url"] = ""
 *  ["local_url"] = ""
 *  [...]
 * dict["dir_name"]
 *  ["type"] = "dir"
 *  ["rfc000.txt"]
 *   ["type"] = "file"
 *   ["postfix"] = "txt"
 *   ["DownTime"] = ""
 *   ["DownStatus"] = ""
 *   ["DownProgress"] = ""
 *   ["url"] = "..."
 *   [...]
 */

void UserCustomTreeModel::packDictionaryToTreeModel ( const QQtDictionary& node, QStandardItem* pobject )
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

            //pline() << item->index() << pobject->index();
            //int row = item->index().row();
            //setData ( index ( row, 1, pobject->index() ), "HHHHHHHH" );
            //setData ( index ( row, 2, pobject->index() ), "CCCC" );
            //setData ( pobject->index().child ( row, 3 ), "DDDD" );
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

                if ( key == "type" )
                    continue;

                QStandardItem* item = new QStandardItem;
                item->setText ( key );
                pobject ? pobject->appendRow ( item ) : appendRow ( item );

                item->setColumnCount ( RFCMax );
                item->removeRows ( 0, item->rowCount() );
                item->setRowCount ( 0 );

                if ( srcvalue["type"].getValue().toString() == "dir" )
                    packDictionaryToTreeModel ( srcvalue, item );
                else
                {
                    //pline() << item->index();
                    int row = item->index().row();
                    //QString lastmodify = srcvalue["postfix"].getValue().toString();
                    QString DownProgress = srcvalue["DownProgress"].getValue().toString();
                    QString DownTime = srcvalue["DownTime"].getValue().toString();
                    QString DownStatus = srcvalue["DownStatus"].getValue().toString();
                    //QString lastmodify = srcvalue["DownTime"].getValue().toString();
                    QString url = srcvalue["url"].getValue().toString();
                    QString localUrl = srcvalue["localUrl"].getValue().toString();
                    //setData ( index ( row, 0 ), "JJJJ" );
                    QModelIndex parentIndex = QModelIndex();
                    if ( pobject )
                        parentIndex = pobject->index();
                    setData ( index ( row, RfcDownTime, parentIndex ), DownTime );
                    setData ( index ( row, RfcDownStatus, parentIndex ), DownStatus );
                    setData ( index ( row, RfcDownProgress, parentIndex ), DownProgress );
                    setData ( index ( row, RfcLocalUrl, parentIndex ), localUrl );
                    setData ( index ( row, RfcUrl, parentIndex ), url );
                }
            }
            break;
        }
        case QQtDictionary::DictMax:
        default:
            break;
    }
}

void UserCustomTreeModel::query ( QQtDictionary& dict )
{
    setColumnCount ( RFCMax );
    setHeaderData ( RfcName, Qt::Horizontal, "    Name" );
    setHeaderData ( RfcLocalUrl, Qt::Horizontal, "Local Path" );
    setHeaderData ( RfcUrl, Qt::Horizontal, "Url" );
    setHeaderData ( RfcDownTime, Qt::Horizontal, "Download Time" );
    setHeaderData ( RfcDownStatus, Qt::Horizontal, "Download Status" );
    setHeaderData ( RfcDownProgress, Qt::Horizontal, "Download Progress" );

    removeRows ( 0, rowCount() );
    setRowCount ( 0 );
    QQtDictTreeModel::query ( dict );
}
