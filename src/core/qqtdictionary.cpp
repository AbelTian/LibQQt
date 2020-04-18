#include "qqtdictionary.h"
#include <qqtordereddictionary.h>

//support json
#include <QJsonDocument>    //json文档
#include <QJsonArray>       //json数组 ["", 1, ...]
#include <QJsonObject>      //json对象 {"":"", ...}
#include <QJsonValue>       //json值 不准确的
#include <QJsonParseError>  //错误处理

//support xml
#include "qdom.h"

//support yaml
#ifdef __YAMLSUPPORT__
#include "yaml-cpp/parser.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/yaml.h"
#endif

//support ini
#ifdef __INICONTENTSUPPORT__
#include "inifile.h"
#endif

#ifdef __QTCSVLIB__
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"
#include "qtcsv/stringdata.h"
#endif

#include <QBuffer>

#include <iostream>
using namespace std;

#ifdef __INICONTENTSUPPORT__
QByteArray toIni ( const QQtDictionary& dict );
void fromIni ( const QByteArray& bytes, QQtDictionary& dict );
QByteArray toProperties ( const QQtDictionary& dict );
void fromProperties ( const QByteArray& bytes, QQtDictionary& dict );
#endif

#ifdef __YAMLSUPPORT__
QByteArray toYAML ( const QQtDictionary& dict );
void fromYAML ( const QByteArray& yaml, QQtDictionary& dict );
void parseYamlNodeToDictionary ( const YAML::Node& node, QQtDictionary& object );
void packDictionaryToYamlNode ( const QQtDictionary& node, YAML::Node& object );
#endif

#ifdef __QTCSVLIB__
QByteArray toCSV ( const QQtDictionary& dict,
                   const QString& separator,
                   const QString& textDelimiter,
                   const QString& textEncoding );
void fromCSV ( const QByteArray& csv, QQtDictionary& dict,
               const QString& separator,
               const QString& textDelimiter,
               const QString& textEncoding );
#endif

QByteArray toJson ( const QQtDictionary& dict, int indent = 0 );
void fromJson ( const QByteArray& json, QQtDictionary& dict );
void parseJsonValue ( const QJsonValue& value, QQtDictionary& parent );
void packDictionaryToJsonValue ( const QQtDictionary& node, QJsonValue& result );

QByteArray toXML ( const QQtDictionary& dict, int indent = -1 );
void fromXML ( const QByteArray& xml, QQtDictionary& dict );
void parseDomNode ( const QDomNode& value, QQtDictionary& parent );
void packDictionaryToDomNode ( const QQtDictionary& node, QDomNode& result, QDomDocument& doc );

void parseOrderedDictionary ( QQtDictionary& node, const QQtOrderedDictionary& obj );

//#define LOCAL_DEBUG
#ifdef LOCAL_DEBUG
#define p3line() p2line()
#else
#define p3line() QNoDebug()
#endif

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
    m_type = DictMax;
    m_value.clear();
    m_list.clear();
    m_map.clear();
}

void QQtDictionary::remove ( int index )
{
    m_type = DictList;
    m_list.removeAt ( index );
}

void QQtDictionary::remove ( const QString& key )
{
    m_type = DictMap;
    m_map.remove ( key );
}

QQtDictionary::QQtDictionary ( const QMap<QString, QQtDictionary>& map )
{
    *this = map;
}

QQtDictionary::QQtDictionary ( const QList<QQtDictionary>& list )
{
    *this = list;
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

QQtDictionary::QQtDictionary ( const QQtOrderedDictionary& other )
{
    *this = other;
}

QQtDictionary& QQtDictionary::operator = ( const QQtOrderedDictionary& other )
{
    parseOrderedDictionary ( *this, other );
    return *this;
}

bool QQtDictionary::operator == ( const QQtOrderedDictionary& other ) const
{
    const QQtDictionary& ref = *this;
    QQtDictionary other1 = other;
    return ( bool ) ( ref == other1 );
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
    //p3line() << m_list.count() << index;

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

QQtDictionary& QQtDictionary::operator = ( const QList<QString>& list )
{
    m_type = DictList;

    m_list.clear();
    QListIterator<QString> itor ( list );
    while ( itor.hasNext() )
    {
        const QString& key = itor.next();
        m_list.push_back ( QQtDictionary ( key ) );
    }
    return *this;
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

QByteArray QQtDictionary::toJson ( QJsonDocument::JsonFormat format ) const
{
    //<0; 0; >0
    int indent = ( int ) format; //default: 0

    //-4,-1; 0; 1-4
    if ( indent < 0 ) //Compact
        indent = -4;
    else if ( indent == 0 ) //Indent
        indent = 1;
    else if ( indent == 1 ) //Compact
        indent = 0;
    else //Indent
        indent = 4;

    return ::toJson ( *this, indent );
}

void QQtDictionary::fromJson ( const QByteArray& json )
{
    ::fromJson ( json, *this );
}

QByteArray QQtDictionary::toXML ( int indent ) const
{
    return ::toXML ( *this, indent );
}

void QQtDictionary::fromXML ( const QByteArray& xml )
{
    ::fromXML ( xml, *this );
}

#ifdef __YAMLSUPPORT__
QByteArray QQtDictionary::toYAML() const
{
    return ::toYAML ( *this );
}

void QQtDictionary::fromYAML ( const QByteArray& yaml )
{
    ::fromYAML ( yaml, *this );
}
#endif

#ifdef __INICONTENTSUPPORT__
QByteArray QQtDictionary::toINI() const
{
    return ::toIni ( *this );
}

void QQtDictionary::fromINI ( const QByteArray& ini )
{
    ::fromIni ( ini, *this );
}

QByteArray QQtDictionary::toProperties() const
{
    return ::toProperties ( *this );
}

void QQtDictionary::fromProperties ( const QByteArray& properties )
{
    ::fromProperties ( properties, *this );
}
#endif

#ifdef __QTCSVLIB__
QByteArray QQtDictionary::toCSV ( const QString& separator,
                                  const QString& textDelimiter,
                                  const QString& textEncoding
                                ) const
{
    return ::toCSV ( *this, separator, textDelimiter, textEncoding );
}

void QQtDictionary::fromCSV ( const QByteArray& csv,
                              const QString& separator,
                              const QString& textDelimiter,
                              const QString& textEncoding )
{
    ::fromCSV ( csv, *this, separator, textDelimiter, textEncoding );
}
#endif

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


QByteArray toJson ( const QQtDictionary& dict, int indent )
{
    //node -> QJsonValue -> QJsonDocument
    QJsonValue value;
    packDictionaryToJsonValue ( dict, value );
    QJsonDocument doc = QJsonDocument::fromVariant ( value.toVariant() );
    QJsonDocument::JsonFormat format = QJsonDocument::Compact;
    //-4,-1; 0; 1-4
    if ( indent < 0 )
        format = QJsonDocument::Compact;
    else if ( indent == 0 )
        format = QJsonDocument::Compact;
    else
        format = QJsonDocument::Indented;
    QByteArray result = doc.toJson ( format );
    return result;
}

void fromJson ( const QByteArray& json, QQtDictionary& dict )
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson ( json, &error );
    //p3line() << doc;
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

    parseJsonValue ( root, dict );
}

void parseJsonValue ( const QJsonValue& value, QQtDictionary& parent )
{
    switch ( value.type() )
    {
        case QJsonValue::Null:
            //p3line() << "null json value" << value;
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
                parent = QQtDictionary ( QQtDictionary::DictList );
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
                parent = QQtDictionary ( QQtDictionary::DictMap );
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

void packDictionaryToJsonValue ( const QQtDictionary& node, QJsonValue& result )
{
    switch ( node.getType() )
    {
        case QQtDictionary::DictValue:
        {
            //null, bool, double, string
            p3line() << node.getValue().type();
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
            else
            {
                result = QJsonValue::fromVariant ( node.getValue() );
            }
            break;
        }
        case QQtDictionary::DictList:
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
        case QQtDictionary::DictMap:
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
        case QQtDictionary::DictMax:
        default:
            break;
    }
}

QByteArray toXML ( const QQtDictionary& dict, int intent )
{
    QDomDocument doc;
    packDictionaryToDomNode ( dict, doc, doc );
    return doc.toByteArray ( intent );
}

void fromXML ( const QByteArray& xml, QQtDictionary& dict )
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
    //p3line() << qPrintable ( doc.toString ( -2 ) );
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
    parseDomNode ( doc, dict );
}

void parseDomNode ( const QDomNode& value, QQtDictionary& parent )
{
    p3line() << value.nodeName() << value.nodeType() << value.nodeValue();

    switch ( value.nodeType() )
    {
        case QDomNode::CommentNode: //8
        {
            //#comment
            QString name0 = value.nodeName();
            QString value0  = value.nodeValue();
            //p3line() << value.nodeName() << value.hasChildNodes() << value.hasAttributes();
            parent = value0;
        }
        break;
        case QDomNode::AttributeNode: //2
        {
            //<element key=value>
            QString name0 = value.nodeName();
            QString value0  = value.nodeValue();
            //p3line() << value.nodeName() << value.hasChildNodes() << value.hasAttributes();
            parent = value0;
        }
        break;
        case QDomNode::TextNode: //3
        {
            //#text
            QString name0 = value.nodeName();
            QString value0  = value.nodeValue();
            //p3line() << value.nodeName() << value.hasChildNodes() << value.hasAttributes();
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
                //p3line() << node3.nodeName() << node3.nodeType() << node3.nodeValue() ;
                //p3line() << node3.nodeName() << node3.hasChildNodes() << node3.hasAttributes();
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

            QStringList comment0;
            for ( int i = 0; i < childs.size(); i++ )
            {
                QDomNode node3 = childs.item ( i );
                QString name0 = node3.nodeName();
                //p3line() << node3.nodeName() << node3.nodeType() << node3.nodeValue() ;
                //p3line() << node3.nodeName() << node3.hasChildNodes() << node3.hasAttributes();
                int count0 = node_count[name0]["count"].getValue().toInt();
                int pos0 = node_count[name0]["pos"].getValue().toInt();
                //p3line() << count0 << pos0;

#if 1
                if ( name0 == "#comment" )
                {
                    comment0.push_front ( node3.nodeValue() );
                    continue;
                }
                if ( comment0.size() > 0 )
                {
                    if ( count0 > 1 )
                    {
                        parent[name0][pos0]["#comment"] = comment0[0];
                    }
                    else
                    {
                        parent[name0]["#comment"] = comment0[0];
                    }
                    comment0.clear();
                }
#endif

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
            //p3line() << pi0.target() << pi0.data();
            parent = pi0.data();

#if 0
            //NO DATA
            //attri [__attributes__], key=value
            QDomNamedNodeMap attrs = value.attributes();
            for ( int i = 0; i < attrs.size(); i++ )
            {
                QDomNode node3 = attrs.item ( i );
                QString name0 = node3.nodeName();
                //p3line() << node3.nodeName() << node3.nodeType() << node3.nodeValue() ;
                //p3line() << node3.nodeName() << node3.hasChildNodes() << node3.hasAttributes();
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
                //p3line() << node1.nodeName() << node1.nodeType() << node1.nodeValue() ;
                //p3line() << node1.nodeName() << node1.hasChildNodes() << node1.hasAttributes();
                if ( node1.nodeType() == QDomNode::CommentNode )
                    continue;

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
            pline() << value.nodeName() << value.hasChildNodes() << value.hasAttributes();
            parent = value0;
        }
        break;
    }
}

void packDictionaryToDomNode ( const QQtDictionary& node, QDomNode& result, QDomDocument& doc )
{
    switch ( node.getType() )
    {
        case QQtDictionary::DictValue:
        {
            //null, bool, double, string
            p3line() << node.getValue().type();
            QDomNode& object = result;
            QDomText text = doc.createTextNode ( node.getValue().toString() );
            object.appendChild ( text );
            break;
        }
        case QQtDictionary::DictList:
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
        case QQtDictionary::DictMap:
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

                //1! "__processinginstruction__" <?xml version='1.0' encoding='UTF-8'?>
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
            }

            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin(); itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& key = itor.key();
                const QQtDictionary& srcvalue = itor.value();

                if ( key == "__processinginstruction__" )
                    continue;

                //2! "__attributes__" <Person attr-key="attr-value"> </Person>
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

                //3! "#text" <Person>#text</Person>
                if ( key == "#text" )
                {
                    //"text"
                    const QString& value2 = srcvalue.getValue().toString();
                    QDomText text = doc.createTextNode ( value2 );
                    object.appendChild ( text );
                    continue;
                }

#if 0
                //4! "#comment" <!--#comment-->
                if ( key == "#comment" )
                {
                    //only one
                    if ( srcvalue.getType() == QQtDictionary::DictValue )
                    {
                        const QString& value2 = srcvalue.getValue().toString();
                        QDomComment text = doc.createComment ( value2 );
                        object.appendChild ( text );
                        continue;
                    }

                    //multiple
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        QDomComment text = doc.createComment ( l[i].getValue().toString() );
                        object.appendChild ( text );
                    }
                    continue;
                }
#endif

                if ( key == "#comment" )
                    continue;

                //5! dict["person"][0-] <person>a</person> <person>b</person>
                if ( srcvalue.getType() == QQtDictionary::DictList )
                {
#if 1
                    //list一定在map里面发生。
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
#if 1 //#comment
                        if ( l[i].getMap().contains ( "#comment" ) )
                        {
                            QDomComment text = doc.createComment ( l[i]["#comment"].getValue().toString() );
                            object.appendChild ( text );
                        }
#endif
                        QDomElement value = doc.createElement ( key );
                        packDictionaryToDomNode ( l[i], value, doc );
                        object.appendChild ( value );
                    }
#else
                    packDictionaryToDomNode ( srcvalue, object, doc, key );
#endif
                    continue;
                }

#if 1 //#comment
                if ( srcvalue.getMap().contains ( "#comment" ) )
                {
                    QDomComment text = doc.createComment ( srcvalue["#comment"].getValue().toString() );
                    object.appendChild ( text );
                }
#endif

                //6! dict[key][child node] <book>...</book>
                QDomElement value = doc.createElement ( key );
                packDictionaryToDomNode ( srcvalue, value, doc );
                object.appendChild ( value );
            }
            break;
        }
        case QQtDictionary::DictMax:
        default:
            break;
    }
}

#ifdef __QTCSVLIB__
QByteArray toCSV ( const QQtDictionary& dict,
                   const QString& separator,
                   const QString& textDelimiter,
                   const QString& textEncoding
                 )
{
    QtCSV::StringData strlist0;

    for ( int i = 0; i < dict.getList().size(); i++ )
    {
        const QQtDictionary& v0 = dict.getList() [i];
        QStringList strlist1;
        for ( int j = 0; j < v0.getList().size(); j++ )
        {
            const QQtDictionary& v1 = v0.getList() [j];
            strlist1.push_back ( v1.getValue().toString() );
        }
        strlist0.addRow ( strlist1 );
    }

    QByteArray bytes;
    QBuffer buffer ( &bytes );
    buffer.open ( QBuffer::WriteOnly );

    QTextCodec* codec = QTextCodec::codecForName ( textEncoding.toLocal8Bit() );
    bool ret = QtCSV::Writer::write ( buffer, strlist0,
                                      separator, textDelimiter,
                                      QStringList(), QStringList(),
                                      codec );
    if ( !ret )
    {
        pline() << "QtCSV write error.";
    }
    buffer.close();
    return bytes;
}

void fromCSV ( const QByteArray& csv, QQtDictionary& dict,
               const QString& separator,
               const QString& textDelimiter,
               const QString& textEncoding
             )
{
    QByteArray bytes = csv;
    QBuffer buffer ( &bytes );
    buffer.open ( QBuffer::ReadOnly );
    QTextCodec* codec = QTextCodec::codecForName ( textEncoding.toLocal8Bit() );
    QList<QStringList> strlist0 = QtCSV::Reader::readToList ( buffer,
                                                              separator, textDelimiter, codec );
    buffer.close();

    for ( int i = 0; i < strlist0.size(); i++ )
    {
        const QStringList& strlist1 = strlist0[i];
        for ( int j = 0; j < strlist1.size(); j++ )
        {
            const QString& strlist2 = strlist1[j];
            dict[i][j] = strlist2;
        }
    }
}

#endif

#ifdef __INICONTENTSUPPORT__
QByteArray toIni ( const QQtDictionary& dict )
{
    const QQtDictionary& node = dict;

    inifile::IniFile p0;
    switch ( dict.getType() )
    {
        case QQtDictionary::DictValue:
        {
            break;
        }
        case QQtDictionary::DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
#if 0
                QList<QQtDictionary>& l = node.getList();
                if ( l[i].getType() == QQtDictionary::DictValue )
                {
                    QString qkey = QString::number ( i );
                    string key = qkey.toStdString();
                    string value = l[i].getValue().toString().toStdString();
                    string comment = node["__comments__"][""][qkey]["#comment"].getValue().toString().toStdString();
                    string right_comment = node["__comments__"][""][qkey]["#right_comment"].getValue().toString().toStdString();
                    p0.SetStringValue ( "", key, value );
                    p0.SetComment ( "", key, comment );
                    p0.SetRightComment ( "", key, right_comment );
                }
#else
                const QString& sec = QString::number ( i );
                string stdsec = sec.toStdString();

                QList<QQtDictionary>& l = node.getList();
                const QQtDictionary& srcvalue = l[i];

                p0.AddSection ( stdsec );

                string comment = node["__comments__"][sec]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][sec]["#right_comment"].getValue().toString().toStdString();
                p0.SetComment ( stdsec, "", comment );
                p0.SetRightComment ( stdsec, "", right_comment );

                if ( srcvalue.getType() == QQtDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QQtDictionary::DictValue )
                        {
                            QString qkey = QString::number ( i );
                            string key = qkey.toStdString();
                            string value = l[i].getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, key, value );
                            p0.SetComment ( stdsec, key, comment );
                            p0.SetRightComment ( stdsec, key, right_comment );
                        }
                    }
                }

                if ( srcvalue.getType() == QQtDictionary::DictMap )
                {
                    for ( QMap<QString, QQtDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QMap<QString, QQtDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QQtDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QQtDictionary::DictValue )
                        {
                            string value = srcvalue2.getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey2]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey2]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, stdkey2, value );
                            p0.SetComment ( stdsec, stdkey2, comment );
                            p0.SetRightComment ( stdsec, stdkey2, right_comment );
                        }
                    }
                }

#endif
            }
            break;
        }
        case QQtDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& sec = itor.key();
                string stdsec = sec.toStdString();
                const QQtDictionary& srcvalue = itor.value();

                if ( sec == "__comments__" )
                    continue;

                p0.AddSection ( stdsec );

                string comment = node["__comments__"][sec]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][sec]["#right_comment"].getValue().toString().toStdString();
                //qDebug() << QString::fromStdString ( comment );
                //qDebug() << QString::fromStdString ( right_comment );
                int ret;
                ret = p0.SetComment ( stdsec, "", comment );
                //qDebug() << ret;
                ret = p0.SetRightComment ( stdsec, "", right_comment );
                //qDebug() << ret;

                if ( srcvalue.getType() == QQtDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QQtDictionary::DictValue )
                        {
                            QString qkey = QString::number ( i );
                            string key = qkey.toStdString();
                            string value = l[i].getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, key, value );
                            p0.SetComment ( stdsec, key, comment );
                            p0.SetRightComment ( stdsec, key, right_comment );
                        }
                    }
                }

                if ( srcvalue.getType() == QQtDictionary::DictMap )
                {
                    for ( QMap<QString, QQtDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QMap<QString, QQtDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QQtDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QQtDictionary::DictValue )
                        {
                            string value = srcvalue2.getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey2]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey2]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, stdkey2, value );
                            p0.SetComment ( stdsec, stdkey2, comment );
                            p0.SetRightComment ( stdsec, stdkey2, right_comment );
                        }
                    }
                }
            }
            break;
        }
        case QQtDictionary::DictMax:
        default:
            break;
    }

    int ret;

    std::string buffer;
    ret = p0.SaveToContent ( buffer );
    //qDebug() << ret;

    QByteArray bytes = QByteArray::fromStdString ( buffer );
    //qDebug() << qPrintable ( bytes );

    //不返回会崩溃
    return bytes;
}

void fromIni ( const QByteArray& bytes, QQtDictionary& dict )
{
    inifile::IniFile p0;
    int ret;
    ret = p0.LoadFromContent ( bytes.toStdString() );

    //qDebug() << ret;
    vector<string> secs;
    ret = p0.GetSections ( &secs );
    for ( vector<string>::iterator itor = secs.begin();
          itor != secs.end(); itor++ )
    {
        string& secName = *itor;
        inifile::IniSection* sec = p0.getSection ( secName );
        //sec name
        string name = sec->name; QString qname = QString::fromStdString ( name );
        //sec comment
        string comment = sec->comment; QString qcomment = QString::fromStdString ( comment );
        //sec right_comment
        string right_comment = sec->rightComment; QString qright_comment = QString::fromStdString ( right_comment );

        dict["__comments__"][qname]["#comment"] = qcomment;
        dict["__comments__"][qname]["#right_comment"] = qright_comment;

        //sec child
        for ( inifile::IniSection::IniItem_it it = sec->begin();
              it != sec->end(); it++ )
        {
            inifile::IniItem& item = *it;

            //#comment
            string comment = item.comment; QString qcomment = QString::fromStdString ( comment );
            //#right_comment
            string right_comment = item.rightComment; QString qright_comment = QString::fromStdString ( right_comment );
            //key
            string key = item.key; QString qkey = QString::fromStdString ( key );
            //value
            string value = item.value; QString qvalue = QString::fromStdString ( value );

            dict["__comments__"][qname][qkey]["#comment"] = qcomment;
            dict["__comments__"][qname][qkey]["#right_comment"] = qright_comment;
            dict[qname][qkey] = qvalue;
        }
    }

    //qDebug() << qPrintable ( dict.toJson ( QJsonDocument::Indented ) );
}

QByteArray toProperties ( const QQtDictionary& dict )
{
    const QQtDictionary& node = dict;

    inifile::IniFile p0;
    switch ( dict.getType() )
    {
        case QQtDictionary::DictValue:
        {
            break;
        }
        case QQtDictionary::DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
#if 0
                QList<QQtDictionary>& l = node.getList();
                if ( l[i].getType() == QQtDictionary::DictValue )
                {
                    QString qkey = QString::number ( i );
                    string key = qkey.toStdString();
                    string value = l[i].getValue().toString().toStdString();
                    string comment = node["__comments__"][""][qkey]["#comment"].getValue().toString().toStdString();
                    string right_comment = node["__comments__"][""][qkey]["#right_comment"].getValue().toString().toStdString();
                    p0.SetStringValue ( "", key, value );
                    p0.SetComment ( "", key, comment );
                    p0.SetRightComment ( "", key, right_comment );
                }
#elif 0
                const QString& sec = QString::number ( i );
                string stdsec = sec.toStdString();

                QList<QQtDictionary>& l = node.getList();
                const QQtDictionary& srcvalue = l[i];

                p0.AddSection ( stdsec );

                string comment = node["__comments__"][sec]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][sec]["#right_comment"].getValue().toString().toStdString();
                p0.SetComment ( stdsec, "", comment );
                p0.SetRightComment ( stdsec, "", right_comment );

                if ( srcvalue.getType() == QQtDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QQtDictionary::DictValue )
                        {
                            QString qkey = QString::number ( i );
                            string key = qkey.toStdString();
                            string value = l[i].getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, key, value );
                            p0.SetComment ( stdsec, key, comment );
                            p0.SetRightComment ( stdsec, key, right_comment );
                        }
                    }
                }

                if ( srcvalue.getType() == QQtDictionary::DictMap )
                {
                    for ( QMap<QString, QQtDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QMap<QString, QQtDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QQtDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QQtDictionary::DictValue )
                        {
                            string value = srcvalue2.getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey2]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey2]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, stdkey2, value );
                            p0.SetComment ( stdsec, stdkey2, comment );
                            p0.SetRightComment ( stdsec, stdkey2, right_comment );
                        }
                    }
                }
#else
                const QString& key = QString::number ( i );
                string stdkey = key.toStdString();
                QList<QQtDictionary>& l = node.getList();
                const QQtDictionary& srcvalue = l[i];

                if ( key == "__comments__" )
                    continue;

                if ( srcvalue.getType() != QQtDictionary::DictValue )
                    continue;

                p0.AddSection ( "" );

                string value = srcvalue.getValue().toString().toStdString();
                string comment = node["__comments__"][key]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][key]["#right_comment"].getValue().toString().toStdString();
                p0.SetStringValue ( "", stdkey, value );
                p0.SetComment ( "", stdkey, comment );
                p0.SetRightComment ( "", stdkey, right_comment );
#endif
            }
            break;
        }
        case QQtDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& key = itor.key();
                string stdkey = key.toStdString();
                const QQtDictionary& srcvalue = itor.value();

                if ( key == "__comments__" )
                    continue;

                if ( srcvalue.getType() != QQtDictionary::DictValue )
                    continue;

                p0.AddSection ( "" );

                string value = srcvalue.getValue().toString().toStdString();
                string comment = node["__comments__"][key]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][key]["#right_comment"].getValue().toString().toStdString();
                p0.SetStringValue ( "", stdkey, value );
                p0.SetComment ( "", stdkey, comment );
                p0.SetRightComment ( "", stdkey, right_comment );
            }
            break;
        }
        case QQtDictionary::DictMax:
        default:
            break;
    }

    int ret;

    std::string buffer;
    ret = p0.SaveToContent ( buffer );
    //qDebug() << ret;

    QByteArray bytes = QByteArray::fromStdString ( buffer );
    //qDebug() << qPrintable ( bytes );

    //不返回会崩溃
    return bytes;
}

void fromProperties ( const QByteArray& bytes, QQtDictionary& dict )
{
    inifile::IniFile p0;
    int ret;
    ret = p0.LoadFromContent ( bytes.toStdString() );

    //qDebug() << ret;
    vector<string> secs;
    ret = p0.GetSections ( &secs );
    for ( vector<string>::iterator itor = secs.begin();
          itor != secs.end(); itor++ )
    {
        string& secName = *itor;
        if ( secName != "" )
            continue;

        inifile::IniSection* sec = p0.getSection ( secName );
        //sec child
        for ( inifile::IniSection::IniItem_it it = sec->begin();
              it != sec->end(); it++ )
        {
            inifile::IniItem& item = *it;

            //#comment
            string comment = item.comment; QString qcomment = QString::fromStdString ( comment );
            //#right_comment
            string right_comment = item.rightComment; QString qright_comment = QString::fromStdString ( right_comment );
            //key
            string key = item.key; QString qkey = QString::fromStdString ( key );
            //value
            string value = item.value; QString qvalue = QString::fromStdString ( value );

            dict["__comments__"][qkey]["#comment"] = qcomment;
            dict["__comments__"][qkey]["#right_comment"] = qright_comment;
            dict[qkey] = qvalue;
        }
    }

    //qDebug() << qPrintable ( dict.toJson ( QJsonDocument::Indented ) );
}
#endif

#ifdef __YAMLSUPPORT__
QByteArray toYAML ( const QQtDictionary& dict )
{

    YAML::Node node;
    packDictionaryToYamlNode ( dict, node );
    //std::cout << "================(A)=============" << std::endl;
    //std::cout << node << std::endl;


    std::string buffer;
    buffer = YAML::Dump ( node );

    QByteArray bytes;
    bytes = QByteArray::fromStdString ( buffer );

    //std::cout << "================(B)=============" << std::endl;
    //qDebug() << qPrintable ( bytes );

    return bytes;
}

void fromYAML ( const QByteArray& yaml, QQtDictionary& dict )
{

    //这个东西非常容易崩溃。
    YAML::Node config;

#if 1
    try
    {
        config = YAML::Load ( yaml );
        //std::cout << config << std::endl;
    }
    catch ( const YAML::Exception& e )
    {
        //-—
        //? [ bad conversion but exited crashed
        std::cerr << e.what() << std::endl;
        return;
    }
#elif 0
    //YAML::Parser parser();
#else
    config = YAML::Load ( yaml );
#endif


    parseYamlNodeToDictionary ( config, dict );
    //qDebug() << "=================";
    //qDebug() << dict;
    //qDebug() << qPrintable ( QString ( dict.toJson ( QJsonDocument::Indented ) ) );
}



void parseYamlNodeToDictionary ( const YAML::Node& node, QQtDictionary& object )
{
    if ( node.IsNull() )
    {
        //qDebug() << "empty value"; //null
        object = QString();
    }
    else if ( node.IsScalar() )
    {
        //auto it = node.begin();
        //qDebug() << QString::fromStdString ( node.Scalar() );
        object = QString::fromStdString ( node.Scalar() );
    }
    else if ( node.IsSequence() )
    {
        int id = 0;
        for ( YAML::Node::const_iterator it = node.begin(); it != node.end(); ++it )
        {
            const YAML::Node& obj = *it;
            parseYamlNodeToDictionary ( obj,  object[id++] );
        }
    }
    else if ( node.IsMap() )
    {
        for ( YAML::Node::const_iterator it = node.begin(); it != node.end(); ++it )
        {
            //qDebug() << QString::fromStdString ( it->first.as<string>() ) << ":" << it->second.Type();
            QString key = QString::fromStdString ( it->first.as<string>() ) ;
            parseYamlNodeToDictionary ( it->second, object[key] );

        }
    }
}

void packDictionaryToYamlNode ( const QQtDictionary& node, YAML::Node& object )
{
    switch ( node.getType() )
    {
        case QQtDictionary:: DictValue:
        {
            //null, bool, double, string
            std::string value = node.getValue().toString().toStdString();
            object = value;
            break;
        }
        case  QQtDictionary:: DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QQtDictionary>& l = node.getList();
                YAML::Node value;
                packDictionaryToYamlNode ( l[i], value );
                object.push_back ( value );
            }
            break;
        }
        case QQtDictionary::  DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin(); itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& qkey = itor.key();
                std::string key = qkey.toStdString();
                const QQtDictionary& srcvalue = itor.value();
                YAML::Node value;
                packDictionaryToYamlNode ( srcvalue, value );
                object[key] = value;
            }
            break;
        }
        case  QQtDictionary:: DictMax:
        default:
            break;
    }

}
#endif

void parseOrderedDictionary ( QQtDictionary& node, const QQtOrderedDictionary& obj )
{
    switch ( obj.getType() )
    {
        case QQtOrderedDictionary::DictValue:
        {
            node = obj.getValue();
        }
        break;
        case QQtOrderedDictionary::DictList:
        {
            for ( int i = 0; i < obj.getList().size(); i++ )
            {
                const QQtOrderedDictionary& value = obj.getList() [i];
                parseOrderedDictionary ( node[i], value );
            }
        }
        break;
        case QQtOrderedDictionary::DictMap:
        {
            QQtOrderedDictionaryMapIterator itor ( obj.getMap() );
            while ( itor.hasNext() )
            {
                itor.next();
                const QString& key = itor.key();
                const QQtOrderedDictionary& value = itor.value();
                parseOrderedDictionary ( node[key], value );
            }
        }
        break;
        case QQtOrderedDictionary::DictMax:
        default:
            break;
    }
}

