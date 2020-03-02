#include "qqtdictionary.h"

//support json
#include <QJsonDocument>    //json文档
#include <QJsonArray>       //json数组 ["", 1, ...]
#include <QJsonObject>      //json对象 {"":"", ...}
#include <QJsonValue>       //json值 不准确的
#include <QJsonParseError>  //错误处理

//support xml
#include "qdom.h"

QQtDictionary::QQtDictionary ()
{
    m_type = DictMax;
}

QQtDictionary::~QQtDictionary()
{

}

bool QQtDictionary::isValue() const
{
    bool is = false;

    if ( m_type == DictValue )
        is = true;

    return is;
}

QQtDictionary::EDictType QQtDictionary::getType() const
{
    return m_type;
}

QString QQtDictionary::getTypeName() const
{
    QString type = "Invalid";
    if ( DictValue == m_type )
        type = "Dict Value";
    else if ( DictList == m_type )
        type = "Dict List";
    else if ( DictMap == m_type )
        type = "Dict Map";

    return type;
}

void QQtDictionary::setType ( QQtDictionary::EDictType type )
{
    m_type = type;
}

void QQtDictionary::setValue ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
}

void QQtDictionary::setChild ( const QList<QQtDictionary>& list )
{
    m_type = DictList;
    m_list = list;
}

void QQtDictionary::setChild ( const QMap<QString, QQtDictionary>& map )
{
    m_type = DictMap;
    m_map = map;
}

void QQtDictionary::addChild ( const QString& value )
{
    addChild ( QQtDictionary ( QVariant ( value ) ) );
}

void QQtDictionary::addChild ( const QQtDictionary& dict )
{
    m_type = DictList;
    //list类
    //append函数，会引用外部变量，push_back是不是在list内部生成了新的实例？
    //如果要使用外部实例，可以getList，然后append value。
    //m_list.append ( dict );
    //生成内部新空间
    m_list.push_back ( dict );
}

void QQtDictionary::insertChild ( const QString& key, const QQtDictionary& dict )
{
    m_type = DictMap;
    m_map.insert ( key, dict );
}

void QQtDictionary::insertChild ( int index, const QString& value )
{
    insertChild ( index, QQtDictionary ( QVariant ( value ) ) );
}

void QQtDictionary::insertChild ( int index, const QQtDictionary& dict )
{
    m_type = DictList;
    //list类
    //insert不能实现max count以后插入？不能。
    //[]不能实现out of range插入操作，而是实现覆盖操作。插入补全。
    //怎么办？

    //不对，插入失败
    //m_list.insert ( index, dict );
    //this->operator [] ( index ) = dict;

    //不对，多了一项。
    //先补全
    //this->operator [] ( index );
    //后插入
    //m_list.insert ( index, dict );

    //正确
    //[] 提供out of range补全index。
    //还需要insert吗？不需要。
    this->operator [] ( index ) = dict;
}

void QQtDictionary::insertChild ( const QString& key, const QString& value )
{
    insertChild ( key, QQtDictionary ( QVariant ( value ) ) );
}

int QQtDictionary::count() const
{
    int cnt = -1;

    if ( DictList == m_type )
        cnt = m_list.count();
    else if ( DictMap == m_type )
        cnt = m_map.count();
    else if ( DictValue == m_type )
        cnt = 1;

    return cnt;
}

int QQtDictionary::size() const
{
    int cnt = -1;

    if ( DictList == m_type )
        cnt = m_list.size();
    else if ( DictMap == m_type )
        cnt = m_map.size();
    else if ( DictValue == m_type )
        cnt = 1;

    return cnt;
}

bool QQtDictionary::isNull() const
{
    if ( m_type == DictMax )
        return true;

    return false;
}

bool QQtDictionary::isValid() const
{
    bool isValid = false;

    switch ( m_type )
    {
        case DictValue:
            if ( !m_value.isValid() )
                isValid = true;

            break;

        case DictList:
            if ( !m_list.isEmpty() )
                isValid = true;

            break;

        case DictMap:
            if ( !m_map.isEmpty() )
                isValid = true;

            break;

        default:
            break;
    }

    return isValid;
}

bool QQtDictionary::isEmpty() const
{
    bool isEmpty = true;

    switch ( m_type )
    {
        case DictValue:
            if ( !m_value.isNull() )
                isEmpty = false;

            break;

        case DictList:
            if ( !m_list.isEmpty() )
                isEmpty = false;

            break;

        case DictMap:
            if ( !m_map.isEmpty() )
                isEmpty = false;

            break;

        default:
            break;
    }

    return isEmpty;
}


bool QQtDictionary::isList() const
{
    bool is = false;

    if ( m_type == DictList )
        is = true;

    return is;
}

bool QQtDictionary::isMap() const
{
    bool is = false;

    if ( m_type == DictMap )
        is = true;

    return is;

}

bool QQtDictionary::hasChild ( const QString& key ) const
{
    bool has = false;

    if ( m_map.contains ( key ) )
        has = true;

    return has;
}

bool QQtDictionary::hasChild ( const QQtDictionary& value ) const
{
    bool has = false;

    //对于list，不同于map，list当中value相等就是包含。
    if ( m_list.contains ( value ) )
        has = true;

    return has;
}

void QQtDictionary::modValue ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
}

void QQtDictionary::modChild ( int index, const QQtDictionary& value )
{
    if ( !m_list.contains ( value ) )
        return;

    m_type = DictList;
    m_list[index] = value;
}

void QQtDictionary::modChild ( const QString& key, const QQtDictionary& value )
{
    if ( !m_map.contains ( key ) )
        return;

    m_type = DictMap;
    m_map[key] = value;
}

void QQtDictionary::clear()
{
    m_value.clear();
    m_list.clear();
    m_map.clear();
}

void QQtDictionary::remove ( int index )
{
    m_list.removeAt ( index );
}

void QQtDictionary::remove ( const QString& key )
{
    m_map.remove ( key );
}

QQtDictionary::QQtDictionary ( const QQtDictionary& other )
{
    *this = other;
}

QQtDictionary::QQtDictionary ( const QQtDictionary::EDictType type )
{
    m_type = type;
}

const QQtDictionary QQtDictionary::operator[] ( const QString& key ) const
{
    return m_map[key];
}

const QQtDictionary& QQtDictionary::operator[] ( int index ) const
{
    return m_list[index];
}

QQtDictionary::QQtDictionary ( const QVariant& value )
{
    m_type = DictValue;
    *this = value;
}

QQtDictionary& QQtDictionary::operator [] ( int index )
{
    m_type = DictList;

    /*如果index>count，补全*/
    //pline() << m_list.count() << index;

    //list size = 4, 最大index = 3。新 index = 4, 添加，新index才可以使用，否则out of range。
    if ( m_list.size() < index + 1 )
    {
        int cnt = m_list.size();

        /*相差的数量*///count -> index+1 = index+1 - count

        for ( int i = 0; i < index + 1 - cnt; i++ )
            m_list.push_back ( QQtDictionary() );
    }

    return ( QQtDictionary& ) m_list.operator [] ( index );
}

QQtDictionary& QQtDictionary::operator [] ( const QString& key )
{
    m_type = DictMap;
    return m_map.operator [] ( key );
}

QQtDictionary& QQtDictionary::operator = ( const QMap<QString, QQtDictionary>& map )
{
    m_type = DictMap;
    m_map = map;
    return *this;
}

QQtDictionary& QQtDictionary::operator = ( const QList<QQtDictionary>& list )
{
    m_type = DictList;
    m_list = list;
    return *this;
}

QQtDictionary& QQtDictionary::operator = ( const QQtDictionary& other )
{
    EDictType type = other.getType();

    switch ( type )
    {
        case DictValue:
            m_value = other.getValue() ;
            break;

        case DictList:
            m_list = other.getList();

            break;

        case DictMap:
            m_map = other.getMap();

            break;

        default:
            break;
    }

    m_type = type;
    return *this;
}

QQtDictionary& QQtDictionary::operator = ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
    return *this;
}

QByteArray QQtDictionary::toXML ( int intent )
{
    QDomDocument doc;
    packDictionaryToDomNode ( *this, doc, doc );
    return doc.toByteArray ( intent );
}

void QQtDictionary::fromXML ( const QByteArray& xml )
{
    QString errorStr;
    int errorLine;
    int errorCol;

    QDomDocument doc;
    if ( !doc.setContent ( xml, true, &errorStr,
                           &errorLine, &errorCol ) )
    {
        qDebug() << "errorStr:" << errorStr;
        qDebug() << "errorLine:" << errorLine <<
                 "  errorCol:" << errorCol;
        return;
    }

    //-1 ---> 4 代表缩进
    //pline() << qPrintable ( doc.toString ( -2 ) );
#if 0
    if ( !doc.setContent ( doc.toByteArray ( -1 ), true, &errorStr,
                           &errorLine, &errorCol ) )
    {
        qDebug() << "errorStr:" << errorStr;
        qDebug() << "errorLine:" << errorLine <<
                 "  errorCol:" << errorCol;
        return;
    }
#endif

    //QDomElement root = doc.documentElement();
    parseDomNode ( doc, *this );
}

QByteArray QQtDictionary::toJson ( QJsonDocument::JsonFormat format )
{
    //node -> QJsonValue -> QJsonDocument
    QJsonValue value;
    packDictionaryToJsonValue ( *this, value );
    QJsonDocument doc = QJsonDocument::fromVariant ( value.toVariant() );
    QByteArray result = doc.toJson ( format );
    return result;
}

void QQtDictionary::fromJson ( const QByteArray& json )
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson ( json, &error );
    //pline() << doc;
    if ( error.error != QJsonParseError::NoError )
    {
        pline() << error.errorString();
        return;
    }
    if ( doc.isNull() || doc.isEmpty() )
    {
        pline() << "json is " << doc.isNull() << doc.isEmpty();
        return;
    }

    QJsonValue root = QJsonValue::fromVariant ( doc.toVariant() );

    parseJsonValue ( root, *this );
}

void QQtDictionary::parseJsonValue ( const QJsonValue& value, QQtDictionary& parent )
{
    switch ( value.type() )
    {
        case QJsonValue::Null:
            //pline() << "null json value" << value;
            parent = QJsonValue();
            break;
        case QJsonValue::Undefined:
            pline() << "undefined json value" << value;
            break;
        case QJsonValue::Bool:
            parent = value.toBool();
            break;
        case QJsonValue::Double:
            parent = value.toDouble();
            break;
        case QJsonValue::String:
            parent = value.toString();
            break;
        case QJsonValue::Array:
        {
            QJsonArray array = value.toArray();
            if ( array.size() <= 0 )
            {
                parent = QQtDictionary ( DictList );
                break;
            }
            for ( int i = 0; i < array.size(); i++ )
            {
                //list，按照顺序为parent节点增加孩子。
                QJsonValueRef value = array[i];
                parseJsonValue ( value, parent[i] );
            }
            break;
        }
        case QJsonValue::Object:
        {
            QJsonObject obj = value.toObject();
            if ( obj.size() <= 0 )
            {
                parent = QQtDictionary ( DictMap );
                break;
            }
            QJsonObject::Iterator itor ( &obj, 0 );
            while ( itor != obj.end() )
            {
                //MAP，parent节点，给parent节点增加孩子
                QJsonValueRef value = itor.value();
                parseJsonValue ( value, parent[itor.key()] );
                itor++;
            }
            break;
        }
        default:
            break;
    }
}

void QQtDictionary::packDictionaryToJsonValue ( const QQtDictionary& node, QJsonValue& result )
{
    switch ( node.getType() )
    {
        case DictValue:
        {
            //null, bool, double, string
            pline() << node.getValue().type();
            if ( node.getValue() == QVariant ( QJsonValue() ) )
            {
                result = QJsonValue();
            }
            else if ( node.getValue().type() == QVariant::Bool )
            {
                result = QJsonValue ( node.getValue().toBool() );
            }
            else if ( node.getValue().type() == QVariant::Double )
            {
                result = QJsonValue ( node.getValue().toDouble() );
            }
            else if ( node.getValue().type() == QVariant::String )
            {
                result = QJsonValue ( node.getValue().toString() );
            }
            break;
        }
        case DictList:
        {
            //"name":[a, b, ...]
            QJsonArray array;
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QQtDictionary>& l = node.getList();
                QJsonValue value;
                packDictionaryToJsonValue ( l[i], value );
                //array.append ( value );
                array.push_back ( value );
            }
            result = array;
            break;
        }
        case DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            QJsonObject object;
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin(); itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& key = itor.key();
                const QQtDictionary& srcvalue = itor.value();
                QJsonValue value;
                packDictionaryToJsonValue ( srcvalue, value );
                object.insert ( key, value );
            }
            result = object;
            break;
        }
        case DictMax:
        default:
            break;
    }
}

void QQtDictionary::parseDomNode ( const QDomNode& value, QQtDictionary& parent )
{
    pline() << value.nodeName() << value.nodeType() << value.nodeValue();

    switch ( value.nodeType() )
    {
        case QDomNode::CommentNode: //8
        {
            //#comment
            QString name0 = value.nodeName();
            QString value0  = value.nodeValue();
            //pline() << value.nodeName() << value.hasChildNodes() << value.hasAttributes();
            parent = value0;
        }
        break;
        case QDomNode::AttributeNode: //2
        {
            //<element key=value>
            QString name0 = value.nodeName();
            QString value0  = value.nodeValue();
            //pline() << value.nodeName() << value.hasChildNodes() << value.hasAttributes();
            parent = value0;
        }
        break;
        case QDomNode::TextNode: //3
        {
            //#text
            QString name0 = value.nodeName();
            QString value0  = value.nodeValue();
            //pline() << value.nodeName() << value.hasChildNodes() << value.hasAttributes();
            parent = value0;
        }
        break;
        case QDomNode::ElementNode: //1
        {
            /**
             * <person a="0">liu kai</person>           dict["person"]
             *                                          dict["person"]["__attributes__"]
             *                                          dict["person"]["#text"]
             * ----------------------------------------------------------------------------
             * <person a="0">
             *     <sub-person2 b="0">BBB</sub-person2>
             *     <sub-person b="0">AAA</sub-person>   dict["person"]["sub-person"]["__attributes__"]
             * </person>                                dict["person"]["sub-person"]["#text"]
             * -----------------------------------------------------------------------------
             */

            //attri [__attributes__], key=value
            QDomNamedNodeMap attrs = value.attributes();
            for ( int i = 0; i < attrs.size(); i++ )
            {
                QDomNode node3 = attrs.item ( i );
                QString name0 = node3.nodeName();
                //pline() << node3.nodeName() << node3.nodeType() << node3.nodeValue() ;
                //pline() << node3.nodeName() << node3.hasChildNodes() << node3.hasAttributes();
                parseDomNode ( node3, parent["__attributes__"][name0] );
            }


            //child [+text], key=value
            QDomNodeList childs = value.childNodes();

            //check count
            //dict[item]["count"]
            //dict[item]["pos"]
            QQtDictionary node_count;
            for ( int i = 0; i < childs.size(); i++ )
            {
                QDomNode node3 = childs.item ( i );
                QString name0 = node3.nodeName();
                node_count[name0]["count"] = 0;
                node_count[name0]["pos"] = 0;
            }
            for ( int i = 0; i < childs.size(); i++ )
            {
                QDomNode node3 = childs.item ( i );
                QString name0 = node3.nodeName();
                node_count[name0]["count"] = node_count[name0]["count"].getValue().toInt () + 1;
            }

            for ( int i = 0; i < childs.size(); i++ )
            {
                QDomNode node3 = childs.item ( i );
                QString name0 = node3.nodeName();
                //pline() << node3.nodeName() << node3.nodeType() << node3.nodeValue() ;
                //pline() << node3.nodeName() << node3.hasChildNodes() << node3.hasAttributes();
                int count0 = node_count[name0]["count"].getValue().toInt();
                int pos0 = node_count[name0]["pos"].getValue().toInt();
                //pline() << count0 << pos0;
                if ( count0 > 1 )
                {
                    parseDomNode ( node3, parent[name0][pos0] );
                    node_count[name0]["pos"] = pos0 + 1;
                }
                else
                    parseDomNode ( node3, parent[name0] );
            }
        }
        break;
        case QDomNode::ProcessingInstructionNode: //7
        {
            //<?xml ... ?>
            QDomProcessingInstruction pi0 = value.toProcessingInstruction();
            //pline() << pi0.target() << pi0.data();
            parent = pi0.data();

#if 0
            //NO DATA
            //attri [__attributes__], key=value
            QDomNamedNodeMap attrs = value.attributes();
            for ( int i = 0; i < attrs.size(); i++ )
            {
                QDomNode node3 = attrs.item ( i );
                QString name0 = node3.nodeName();
                //pline() << node3.nodeName() << node3.nodeType() << node3.nodeValue() ;
                //pline() << node3.nodeName() << node3.hasChildNodes() << node3.hasAttributes();
                parseDomNode ( node3, parent["__attributes__"][name0] );
            }
#endif

        }
        break;
        case QDomNode::DocumentNode: //9
        {
            QDomNodeList childs = value.childNodes();
            for ( int i = 0; i < childs.size(); i++ )
            {
                QDomNode node1 = childs.item ( i );
                QString name0 = node1.nodeName();
                //pline() << node1.nodeName() << node1.nodeType() << node1.nodeValue() ;
                //pline() << node1.nodeName() << node1.hasChildNodes() << node1.hasAttributes();
                if ( node1.nodeType() == QDomNode::ProcessingInstructionNode )
                    parseDomNode ( node1, parent["__processinginstruction__"][name0] );
                else
                    parseDomNode ( node1, parent[name0] );
            }
        }
        break;
        case QDomNode::EntityNode:
        default:
        {
            QString name0 = value.nodeName();
            QString value0  = value.nodeValue();
            //pline() << value.nodeName() << value.hasChildNodes() << value.hasAttributes();
            parent = value0;
        }
        break;
    }
}

void QQtDictionary::packDictionaryToDomNode ( const QQtDictionary& node, QDomNode& result, QDomDocument& doc )
{
    switch ( node.getType() )
    {
        case DictValue:
        {
            //null, bool, double, string
            pline() << node.getValue().type();
            QDomNode& object = result;
            QDomText text = doc.createTextNode ( node.getValue().toString() );
            object.appendChild ( text );
            break;
        }
        case DictList:
        {
            //<book a="1"> ... </book>
            //<book a="2"> ... </book>
            QDomNode& object = result;
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QQtDictionary>& l = node.getList();
                QString nodeName = object.nodeName();//error，这个位置好像来不了。
                QDomElement value = doc.createElement ( nodeName );
                packDictionaryToDomNode ( l[i], value, doc );
                object.appendChild ( value );
            }
            break;
        }
        case DictMap:
        {
            //<person a="1">
            //  <sub-person b="10"> </sub-person>
            //  <sub-person2 b="11"> </sub-person2>
            //</person>
            QDomNode& object = result;
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin(); itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& key = itor.key();
                const QQtDictionary& srcvalue = itor.value();

                if ( key == "__processinginstruction__" )
                {
                    //"xml"
                    for ( QMap<QString, QQtDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        const QString& key2 = itor2.key();
                        const QQtDictionary& srcvalue2 = itor2.value();
                        QDomProcessingInstruction node0 = doc.createProcessingInstruction ( key2, srcvalue2.getValue().toString() );
                        object.appendChild ( node0 );
                    }
                    continue;
                }

                if ( key == "__attributes__" )
                {
                    //"attributes" key = value
                    for ( QMap<QString, QQtDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        const QString& key2 = itor2.key();
                        const QQtDictionary& srcvalue2 = itor2.value();
                        QDomElement e0 = object.toElement();
                        e0.setAttribute ( key2, srcvalue2.getValue().toString() );
                    }
                    continue;
                }

                if ( key == "#text" )
                {
                    //"text"
                    const QString& value2 = srcvalue.getValue().toString();
                    QDomText text = doc.createTextNode ( value2 );
                    object.appendChild ( text );
                    continue;
                }

                if ( key == "#comment" )
                {
                    //"comment"
                    if ( srcvalue.getType() == DictValue )
                    {
                        const QString& value2 = srcvalue.getValue().toString();
                        QDomComment text = doc.createComment ( value2 );
                        object.appendChild ( text );
                        continue;
                    }

                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        QDomComment text = doc.createComment ( l[i].getValue().toString() );
                        object.appendChild ( text );
                    }
                    continue;
                }

                if ( srcvalue.getType() == DictList )
                {
#if 1
                    //list一定在map里面发生。
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        QDomElement value = doc.createElement ( key );
                        packDictionaryToDomNode ( l[i], value, doc );
                        object.appendChild ( value );
                    }
#else
                    packDictionaryToDomNode ( srcvalue, object, doc, key );
#endif
                    continue;
                }

                QDomElement value = doc.createElement ( key );
                packDictionaryToDomNode ( srcvalue, value, doc );
                object.appendChild ( value );
            }
            break;
        }
        case DictMax:
        default:
            break;
    }
}

bool QQtDictionary::operator == ( const QQtDictionary& other ) const
{
    if ( m_type == other.getType() &&
         other.getList() == m_list &&
         other.getMap() == m_map &&
         other.getValue() == m_value )
        return true;

    return false;
}

QMap<QString, QQtDictionary>& QQtDictionary::getMap() const
{
    return ( QMap<QString, QQtDictionary>& ) m_map;
}

QList<QQtDictionary>& QQtDictionary::getList() const
{
    return ( QList<QQtDictionary>& ) m_list;
}

QVariant& QQtDictionary::getValue()
{
    return ( QVariant& ) m_value;
}

const QVariant& QQtDictionary::getValue() const
{
    return ( const QVariant& ) m_value;
}

QQtDictionary& QQtDictionary::getChild ( int index )
{
    return m_list[index];
}

QQtDictionary& QQtDictionary::getChild ( const QString& key )
{
    return m_map[key];
}



QDebug operator<< ( QDebug dbg, const QQtDictionary& d )
{
    if ( d.getType() == QQtDictionary::DictMax )
    {
        dbg << "{"
            << "\n"
            << "  Type:" << d.getTypeName()
            << "\n"
            << "  Value:" << d.getValue()
            << "\n"
            << "}";
    }
    else if ( d.getType() == QQtDictionary::DictValue )
    {
        dbg << "{"
            << "\n"
            << "  Type:" << d.getTypeName()
            << "\n"
            << "  Value:" << d.getValue()
            << "\n"
            << "}";
    }
    else
    {
        dbg << "{"
            << "\n"
            << "  Type:" << d.getTypeName()
            << "\n"
            << "  Count:" << d.count();

        if ( d.getType() == QQtDictionary::DictList )
        {
            dbg << "\n"
                << "  List:" << "{";
            for ( int i = 0; i < d.getList().size(); i++ )
            {
                dbg << "\n"
                    << qPrintable ( QString ( "    id: %1 Type: %2" ).arg ( i, -10 ).arg ( d[i].getTypeName(), -10 ) )
                    << "Value:" << d[i].getValue();
                //<< "    id:" << i << "Type:" << d[i].getTypeName() << "Value:" << d[i].getValue();
            }
            dbg << "\n"
                << "  }";
        }
        else if ( d.getType() == QQtDictionary::DictMap )
        {
            dbg << "\n"
                << "  Map:" << "{";
            foreach ( QString key, d.getMap().keys() )
            {
                dbg << "\n"
                    << qPrintable ( QString ( "    id: %1 Type: %2" ).arg ( key, -20 ).arg ( d[key].getTypeName(), -10 ) )
                    << "Value:" << d[key].getValue();
                //<< "    id:" << key << "Type:" << d[key].getTypeName() << "Value:" << d[key].getValue();
            }
            dbg << "\n"
                << "  }";
        }

        dbg << "\n"
            << "}";
    }

    return dbg;
}

