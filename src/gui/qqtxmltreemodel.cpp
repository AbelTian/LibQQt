#include "qqtxmltreemodel.h"
#include <QFile>
#include "qqtcore.h"
#include <QModelIndex>

QQtXmlTreeModel::QQtXmlTreeModel ( QObject* parent ) : QQtTreeModel ( parent )
{

}

void QQtXmlTreeModel::setFilePath ( QString fileName )
{
    QFile file ( fileName );

    if ( !file.open ( QFile::ReadOnly | QFile::Text ) )
    {
        pline() << "Error: Cannot read file " << qPrintable ( fileName )
                << ": " << qPrintable ( file.errorString() )
                << endl;
        return;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;

    if ( !doc.setContent ( &file, false, &errorStr, &errorLine,
                           &errorColumn ) )
    {
        pline() << "Error: Parse error at line " << errorLine << ", "
                << "column " << errorColumn << ": "
                << qPrintable ( errorStr ) << endl;
        return;
    }

    file.close();

    clear();
    QDomElement rootElement = doc.documentElement();
    parseChildElement ( rootElement );

    return;
}

bool QQtXmlTreeModel::query ( QString condition )
{
    Q_UNUSED ( condition )
    //TODO:
    return true;
}

/**
 * @brief QQtXmlTreeModel::parseChildElement
 * @param element
 * @param parent
 * 这套递归代码，第一次和最后一次不同。
 */
void QQtXmlTreeModel::parseChildElement ( const QDomElement& element, QStandardItem* itemParent )
{
    /**
     * @brief element name
     */
    QStandardItem* item = new QStandardItem();

    item->setData ( element.nodeName(), Qt::EditRole );
    item->setData ( element.text(), Qt::UserRole );

    if ( element.isNull() && !element.hasChildNodes() )
        item->setData ( itemParent->data ( Qt::UserRole ), Qt::EditRole );

    pline() << element.nodeName() << element.text();

    if ( itemParent )
    {
        itemParent->appendRow ( item );
        //if column is not enough
        //setItem(indexFromItem(itemParent).row(), 0, item);
    }
    else
    {
        //first time ok. also
        //appendRow(item);
        setItem ( 0, 0, item );
    }

    /**
     * @brief element attibute
     */
    QDomNamedNodeMap nodeMap = element.attributes();

    if ( nodeMap.count() > columnCount() )
        setColumnCount ( nodeMap.count() );

    for ( int i = 0; i < nodeMap.count(); i++ )
    {
        QString attName = nodeMap.item ( i ).nodeName();
        QString attValue = nodeMap.item ( i ).nodeValue();
        QStandardItem* _item = new QStandardItem();
        _item->setData ( attName, Qt::UserRole );
        _item->setData ( attValue, Qt::EditRole );

        pline() << attName << attValue << itemParent;

        if ( itemParent )
        {
            itemParent->setChild ( item->index().row(), i + 1, _item );

            /**
             * @brief more than two column need this
             */
            //setItem(indexFromItem(item).row(), i+1, _item);
        }
        else
            //first time
            setItem ( indexFromItem ( item ).row(), i + 1, _item );
    }

    /**
     * child element
     */
    QDomNode child = element.firstChild();

    while ( !child.isNull() )
    {
        parseChildElement ( child.toElement(), item );
        child = child.nextSibling();
    }
}
