#include <qqtordereddictionary.h>

//support json
#ifdef __JSONCPP_SUPPORT__
//#define USE_JSONCPP
#endif
#ifdef __RAPIDJSON_SUPPORT__
#define USE_RAPIDJSON
#endif

#ifdef USE_JSONCPP
#include "json/json.h"
#elif defined(USE_RAPIDJSON)
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/reader.h"
#else
#include <QJsonDocument>    //json文档
#include <QJsonArray>       //json数组 ["", 1, ...]
#include <QJsonObject>      //json对象 {"":"", ...}
#include <QJsonValue>       //json值 不准确的
#include <QJsonParseError>  //错误处理
#endif

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
QByteArray toIni ( const QQtOrderedDictionary& dict );
void fromIni ( const QByteArray& bytes, QQtOrderedDictionary& dict );
QByteArray toProperties ( const QQtOrderedDictionary& dict );
void fromProperties ( const QByteArray& bytes, QQtOrderedDictionary& dict );
#endif

#ifdef __YAMLSUPPORT__
QByteArray toYAML ( const QQtOrderedDictionary& dict );
void fromYAML ( const QByteArray& yaml, QQtOrderedDictionary& dict );
void parseYamlNodeToDictionary ( const YAML::Node& node, QQtOrderedDictionary& object );
void packDictionaryToYamlNode ( const QQtOrderedDictionary& node, YAML::Node& object );
#endif

#ifdef __QTCSVLIB__
QByteArray toCSV ( const QQtOrderedDictionary& dict,
                   const QString& separator,
                   const QString& textDelimiter,
                   const QString& textEncoding );
void fromCSV ( const QByteArray& csv, QQtOrderedDictionary& dict,
               const QString& separator,
               const QString& textDelimiter,
               const QString& textEncoding );
#endif


#ifdef USE_JSONCPP
QByteArray toJson ( const QOrderedDictionary& dict, int indent = 0 );
void fromJson ( const QByteArray& json, QOrderedDictionary& dict );
void parseJsonValue ( const Json::Value& value, QOrderedDictionary& parent );
void packDictionaryToJsonValue ( const QOrderedDictionary& node, Json::Value& result );
#elif defined(USE_RAPIDJSON)
QByteArray toJson ( const QQtOrderedDictionary& dict, int indent = 0 );
void fromJson ( const QByteArray& json, QQtOrderedDictionary& dict );
void parseJsonValue ( const rapidjson::Value& value, QQtOrderedDictionary& parent, rapidjson::Document& doc  );
void packDictionaryToJsonValue ( const QQtOrderedDictionary& node, rapidjson::Value& result, rapidjson::Document& doc );
#else
QByteArray toJson ( const QOrderedDictionary& dict, int indent = 0 );
void fromJson ( const QByteArray& json, QOrderedDictionary& dict );
void parseJsonValue ( const QJsonValue& value, QOrderedDictionary& parent );
void packDictionaryToJsonValue ( const QOrderedDictionary& node, QJsonValue& result );
#endif

QByteArray toXML ( const QQtOrderedDictionary& dict, int indent = -1 );
void fromXML ( const QByteArray& xml, QQtOrderedDictionary& dict );
void parseDomNode ( const QDomNode& value, QQtOrderedDictionary& parent );
void packDictionaryToDomNode ( const QQtOrderedDictionary& node, QDomNode& result, QDomDocument& doc );

//#define LOCAL_DEBUG
#ifdef LOCAL_DEBUG
#define p3line() p2line()
#else
#define p3line() QNoDebug()
#endif

QQtOrderedDictionary::QQtOrderedDictionary ()
{
    m_type = DictMax;
}

QQtOrderedDictionary::~QQtOrderedDictionary()
{

}

bool QQtOrderedDictionary::isValue() const
{
    bool is = false;

    if ( m_type == DictValue )
        is = true;

    return is;
}

QQtOrderedDictionary::EDictType QQtOrderedDictionary::getType() const
{
    return m_type;
}

QString QQtOrderedDictionary::getTypeName() const
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

void QQtOrderedDictionary::setType ( QQtOrderedDictionary::EDictType type )
{
    m_type = type;
}

void QQtOrderedDictionary::setValue ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
}

void QQtOrderedDictionary::setChild ( const QList<QQtOrderedDictionary>& list )
{
    m_type = DictList;
    m_list = list;
}

void QQtOrderedDictionary::setChild ( const QOrderedMap<QString, QQtOrderedDictionary>& map )
{
    m_type = DictMap;
    m_map = map;
}

void QQtOrderedDictionary::addChild ( const QString& value )
{
    addChild ( QQtOrderedDictionary ( QVariant ( value ) ) );
}

void QQtOrderedDictionary::addChild ( const QQtOrderedDictionary& dict )
{
    m_type = DictList;
    //list类
    //append函数，会引用外部变量，push_back是不是在list内部生成了新的实例？
    //如果要使用外部实例，可以getList，然后append value。
    //m_list.append ( dict );
    //生成内部新空间
    m_list.push_back ( dict );
}

void QQtOrderedDictionary::insertChild ( const QString& key, const QQtOrderedDictionary& dict )
{
    m_type = DictMap;
    m_map.insert ( key, dict );
}

void QQtOrderedDictionary::insertChild ( int index, const QString& value )
{
    insertChild ( index, QQtOrderedDictionary ( QVariant ( value ) ) );
}

void QQtOrderedDictionary::insertChild ( int index, const QQtOrderedDictionary& dict )
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

void QQtOrderedDictionary::insertChild ( const QString& key, const QString& value )
{
    insertChild ( key, QQtOrderedDictionary ( QVariant ( value ) ) );
}

int QQtOrderedDictionary::count() const
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

int QQtOrderedDictionary::size() const
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

bool QQtOrderedDictionary::isNull() const
{
    if ( m_type == DictMax )
        return true;

    return false;
}

bool QQtOrderedDictionary::isValid() const
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

bool QQtOrderedDictionary::isEmpty() const
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


bool QQtOrderedDictionary::isList() const
{
    bool is = false;

    if ( m_type == DictList )
        is = true;

    return is;
}

bool QQtOrderedDictionary::isMap() const
{
    bool is = false;

    if ( m_type == DictMap )
        is = true;

    return is;

}

bool QQtOrderedDictionary::hasChild ( const QString& key ) const
{
    bool has = false;

    if ( m_map.contains ( key ) )
        has = true;

    return has;
}

bool QQtOrderedDictionary::hasChild ( const QQtOrderedDictionary& value ) const
{
    bool has = false;

    //对于list，不同于map，list当中value相等就是包含。
    if ( m_list.contains ( value ) )
        has = true;

    return has;
}

void QQtOrderedDictionary::modValue ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
}

void QQtOrderedDictionary::modChild ( int index, const QQtOrderedDictionary& value )
{
    if ( !m_list.contains ( value ) )
        return;

    m_type = DictList;
    m_list[index] = value;
}

void QQtOrderedDictionary::modChild ( const QString& key, const QQtOrderedDictionary& value )
{
    if ( !m_map.contains ( key ) )
        return;

    m_type = DictMap;
    m_map[key] = value;
}

void QQtOrderedDictionary::clear()
{
    m_type = DictMax;
    m_value.clear();
    m_list.clear();
    m_map.clear();
}

void QQtOrderedDictionary::remove ( int index )
{
    m_type = DictList;
    m_list.removeAt ( index );
}

void QQtOrderedDictionary::remove ( const QString& key )
{
    m_type = DictMap;
    m_map.remove ( key );
}

QQtOrderedDictionary::QQtOrderedDictionary ( const QQtOrderedDictionary& other )
{
    *this = other;
}

QQtOrderedDictionary::QQtOrderedDictionary ( const QQtOrderedDictionary::EDictType type )
{
    m_type = type;
}

const QQtOrderedDictionary QQtOrderedDictionary::operator[] ( const QString& key ) const
{
    return m_map[key];
}

const QQtOrderedDictionary& QQtOrderedDictionary::operator[] ( int index ) const
{
    return m_list[index];
}

QQtOrderedDictionary::QQtOrderedDictionary ( const QVariant& value )
{
    m_type = DictValue;
    *this = value;
}

QQtOrderedDictionary& QQtOrderedDictionary::operator [] ( int index )
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
            m_list.push_back ( QQtOrderedDictionary() );
    }

    return ( QQtOrderedDictionary& ) m_list.operator [] ( index );
}

QQtOrderedDictionary& QQtOrderedDictionary::operator [] ( const QString& key )
{
    m_type = DictMap;
    return m_map.operator [] ( key );
}

QQtOrderedDictionary& QQtOrderedDictionary::operator = ( const QList<QString>& list )
{
    m_type = DictList;

    m_list.clear();
    QListIterator<QString> itor ( list );
    while ( itor.hasNext() )
    {
        const QString& key = itor.next();
        m_list.push_back ( QQtOrderedDictionary ( key ) );
    }
    return *this;
}

QQtOrderedDictionary& QQtOrderedDictionary::operator = ( const QOrderedMap<QString, QQtOrderedDictionary>& map )
{
    m_type = DictMap;
    m_map = map;
    return *this;
}

QQtOrderedDictionary& QQtOrderedDictionary::operator = ( const QList<QQtOrderedDictionary>& list )
{
    m_type = DictList;
    m_list = list;
    return *this;
}

QQtOrderedDictionary& QQtOrderedDictionary::operator = ( const QQtOrderedDictionary& other )
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


QQtOrderedDictionary& QQtOrderedDictionary::operator = ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
    return *this;
}

QByteArray QQtOrderedDictionary::toJson ( int indent ) const
{
    return ::toJson ( *this, indent );
}

void QQtOrderedDictionary::fromJson ( const QByteArray& json )
{
    ::fromJson ( json, *this );
}

QByteArray QQtOrderedDictionary::toXML ( int indent ) const
{
    return ::toXML ( *this, indent );
}

void QQtOrderedDictionary::fromXML ( const QByteArray& xml )
{
    ::fromXML ( xml, *this );
}

#ifdef __YAMLSUPPORT__
QByteArray QQtOrderedDictionary::toYAML() const
{
    return ::toYAML ( *this );
}

void QQtOrderedDictionary::fromYAML ( const QByteArray& yaml )
{
    ::fromYAML ( yaml, *this );
}
#endif

#ifdef __INICONTENTSUPPORT__
QByteArray QQtOrderedDictionary::toINI() const
{
    return ::toIni ( *this );
}

void QQtOrderedDictionary::fromINI ( const QByteArray& ini )
{
    ::fromIni ( ini, *this );
}

QByteArray QQtOrderedDictionary::toProperties() const
{
    return ::toProperties ( *this );
}

void QQtOrderedDictionary::fromProperties ( const QByteArray& properties )
{
    ::fromProperties ( properties, *this );
}
#endif

#ifdef __QTCSVLIB__
QByteArray QQtOrderedDictionary::toCSV ( const QString& separator,
                                       const QString& textDelimiter,
                                       const QString& textEncoding
                                     ) const
{
    return ::toCSV ( *this, separator, textDelimiter, textEncoding );
}

void QQtOrderedDictionary::fromCSV ( const QByteArray& csv,
                                   const QString& separator,
                                   const QString& textDelimiter,
                                   const QString& textEncoding )
{
    ::fromCSV ( csv, *this, separator, textDelimiter, textEncoding );
}
#endif

bool QQtOrderedDictionary::operator == ( const QQtOrderedDictionary& other ) const
{
    if ( m_type == other.getType() &&
         other.getList() == m_list &&
         other.getMap() == m_map &&
         other.getValue() == m_value )
        return true;

    return false;
}

QOrderedMap<QString, QQtOrderedDictionary>& QQtOrderedDictionary::getMap() const
{
    return ( QOrderedMap<QString, QQtOrderedDictionary>& ) m_map;
}

QList<QQtOrderedDictionary>& QQtOrderedDictionary::getList() const
{
    return ( QList<QQtOrderedDictionary>& ) m_list;
}

QVariant& QQtOrderedDictionary::getValue()
{
    return ( QVariant& ) m_value;
}

const QVariant& QQtOrderedDictionary::getValue() const
{
    return ( const QVariant& ) m_value;
}

QQtOrderedDictionary& QQtOrderedDictionary::getChild ( int index )
{
    return m_list[index];
}

QQtOrderedDictionary& QQtOrderedDictionary::getChild ( const QString& key )
{
    return m_map[key];
}



QDebug operator<< ( QDebug dbg, const QQtOrderedDictionary& d )
{
    if ( d.getType() == QQtOrderedDictionary::DictMax )
    {
        dbg << "{"
            << "\n"
            << "  Type:" << d.getTypeName()
            << "\n"
            << "  Value:" << d.getValue()
            << "\n"
            << "}";
    }
    else if ( d.getType() == QQtOrderedDictionary::DictValue )
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

        if ( d.getType() == QQtOrderedDictionary::DictList )
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
        else if ( d.getType() == QQtOrderedDictionary::DictMap )
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


#ifdef USE_JSONCPP
QByteArray toJson ( const QOrderedDictionary& dict, int indent )
{
    //node -> QJsonValue -> QJsonDocument
    Json::Value root;
    packDictionaryToJsonValue ( dict, root );

    QByteArray result;

    QString strIndent;
    strIndent.fill ( ' ', indent );

    Json::StreamWriterBuilder builder;
    builder["emitUTF8"] = true;
    builder["indentation"] = strIndent.toStdString();

    Json::OStringStream sout;
    Json::StreamWriter* const writer ( builder.newStreamWriter() );
    writer->write ( root, &sout );
    Json::String str = sout.str();
    delete writer;

    result = QByteArray::fromStdString ( str );
    return result;
}

void fromJson ( const QByteArray& json, QOrderedDictionary& dict )
{
    Json::Value root;

    Json::CharReaderBuilder builder;
    Json::CharReader* const reader ( builder.newCharReader() );
    Json::String errors;
    bool ret = reader->parse ( json.constData(),
                               json.constData() + json.size() - 1,
                               &root, &errors );
    delete reader;

    if ( !ret )
    {
        pline() <<  QString::fromStdString ( errors );
        return;
    }

    if ( root.isNull() )
    {
        pline() << QString::fromStdString ( errors );
        return;
    }

    parseJsonValue ( root, dict );
}

void parseJsonValue ( const Json::Value& value, QOrderedDictionary& parent )
{
    switch ( value.type() )
    {
        case Json::nullValue:
            //p3line() << "null json value" << value;
            parent = QJsonValue();
            p3line() << QJsonValue();
            break;
        case Json::intValue:
            parent = value.asInt64();
            p3line() << value.asInt64();
            break;
        case Json::uintValue:
            parent = value.asUInt64();
            p3line() << value.asUInt64();
            break;
        case Json::realValue:
            parent = value.asDouble();
            p3line() << value.asDouble();
            break;
        case Json::booleanValue:
            parent = value.asBool();
            p3line() << value.asBool();
            break;
        case Json::stringValue:
            parent = QString::fromStdString ( value.asString() );
            p3line() << QString::fromStdString ( value.asString() );
            break;
        case Json::arrayValue:
        {
            const Json::Value& array = value;
            if ( array.size() <= 0 )
            {
                parent = QOrderedDictionary ( QOrderedDictionary:: DictList );
                break;
            }
            for ( int i = 0; i < array.size(); i++ )
            {
                //list，按照顺序为parent节点增加孩子。
                const Json::Value& value1 = array[i];
                parseJsonValue ( value1, parent[i] );
            }
            break;
        }
        case Json::objectValue:
        {
            const Json::Value& obj = value;
            if ( obj.size() <= 0 )
            {
                parent = QOrderedDictionary ( QOrderedDictionary::DictMap );
                break;
            }
            for ( Json::ValueConstIterator itor = obj.begin(); itor != obj.end(); itor++ )
            {
                QString key = QString::fromStdString ( itor.name() );
                //p2line() << key << QString::fromStdString ( itor.key().asString() );
                const Json::Value& value = *itor;
                parseJsonValue ( value, parent[key] );
            }
            break;
        }
        default:
            p3line() << "unknown type value" << ( int ) value.type();
            break;
    }
}
void packDictionaryToJsonValue ( const QOrderedDictionary& node, Json::Value& result )
{
    switch ( node.getType() )
    {
        case QOrderedDictionary::DictValue:
        {
            //null, bool, double, string
            p3line() << node.getValue().type();
            if ( node.getValue() == QVariant ( QJsonValue() ) )
            {
                result = Json::Value();
            }
            else if ( node.getValue().type() == QVariant::Bool )
            {
                result = Json::Value ( node.getValue().toBool() );
            }
            else if ( node.getValue().type() == QVariant::Int )
            {
                result = Json::Value ( node.getValue().toInt() );
            }
            else if ( node.getValue().type() == QVariant::UInt )
            {
                result = Json::Value ( node.getValue().toUInt() );
            }
            else if ( node.getValue().type() == QVariant::LongLong )
            {
                result = Json::Value ( node.getValue().toLongLong() );
            }
            else if ( node.getValue().type() == QVariant::ULongLong )
            {
                result = Json::Value ( node.getValue().toULongLong() );
            }
            else if ( node.getValue().type() == QVariant::Double )
            {
                result = Json::Value ( node.getValue().toDouble() );
            }
            else if ( node.getValue().type() == QVariant::String )
            {
                result = Json::Value ( node.getValue().toString().toStdString() );
                //p3line() << node.getValue().toString(); //???? How to print
                //p3line() << QString::fromStdString ( result.asString() );
            }
            break;
        }
        case QOrderedDictionary::DictList:
        {
            //"name":[a, b, ...]
            Json::Value array ( Json::arrayValue );
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QOrderedDictionary>& l = node.getList();
                Json::Value value;
                packDictionaryToJsonValue ( l[i], value );
                //array.append ( value );
                //array.push_back ( value );
                array.insert ( i, value );
            }
            result = array;
            break;
        }
        case QOrderedDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            Json::Value object ( Json::objectValue );
            for ( QOrderedMap<QString, QOrderedDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                Json::String key = itor.key().toStdString();
                const QOrderedDictionary& srcvalue = itor.value();
                Json::Value value;
                packDictionaryToJsonValue ( srcvalue, value );
                object[key] = value;
            }
            result = object;
            break;
        }
        case QOrderedDictionary::DictMax:
        default:
            break;
    }
}
#elif defined(USE_RAPIDJSON)
QByteArray toJson ( const QQtOrderedDictionary& dict, int indent )
{
    //node -> QJsonValue -> QJsonDocument
    rapidjson::Document root;
    packDictionaryToJsonValue ( dict, root, root );

    rapidjson::StringBuffer strBuf;
    if ( indent < 0 )
    {
        rapidjson::Writer<rapidjson::StringBuffer> writer ( strBuf );
        root.Accept ( writer );
    }
    else
    {
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer ( strBuf );
        writer.SetIndent ( ' ', indent );
        root.Accept ( writer );
    }

    std::string str = strBuf.GetString();
    QByteArray result;
    result = QByteArray::fromStdString ( str );
    return result;
}

void fromJson ( const QByteArray& json, QQtOrderedDictionary& dict )
{
    rapidjson::Document doc;
    doc.Parse ( json.constData(), json.size() );
    bool ret = doc.HasParseError();
    if ( ret )
    {
        pline() << "parse error" << ( int ) doc.GetParseError();
        return;
    }

    if ( doc.IsNull() )
    {
        pline() << "parse empty json string" << ( int ) doc.GetParseError();
        return;
    }

    parseJsonValue ( doc, dict, doc );
}

void parseJsonValue ( const rapidjson::Value& value, QQtOrderedDictionary& parent, rapidjson::Document& doc  )
{
    switch ( value.GetType() )
    {
        case rapidjson::kNullType:
            //p3line() << "null json value" << value;
            parent = QJsonValue();
            p3line() << QJsonValue();
            break;
        case rapidjson::kNumberType:
            if ( value.IsDouble() )
            {
                parent = value.Get<double>();
            }
            else if ( value.IsFloat() )
            {
                parent = value.Get<float>();
            }
            else if ( value.IsInt() )
            {
                parent = value.Get<int>();
            }
            else if ( value.IsInt64() )
            {
                parent = ( long long ) ( value.Get<int64_t>() );
            }
            else if ( value.IsUint() )
            {
                parent = value.Get<unsigned int>();
            }
            else if ( value.IsUint64() )
            {
                parent = ( unsigned long long ) ( value.Get<uint64_t>() );
            }
            else
            {
                pline() << "rapid json type?";
                parent = value.Get<double>();
            }
            break;
        case rapidjson::kTrueType:
            parent = value.Get<bool>();
            break;
        case rapidjson::kFalseType:
            parent = value.Get<bool>();
            break;
        case rapidjson::kStringType:
            parent = QString::fromStdString ( value.GetString() );
            p3line() << QString::fromStdString ( value.GetString() );
            break;
        case rapidjson::kArrayType:
        {
            const rapidjson::Value& array = value;
            if ( array.Size() <= 0 )
            {
                parent = QQtOrderedDictionary ( QQtOrderedDictionary:: DictList );
                break;
            }
            for ( int i = 0; i < array.Size(); i++ )
            {
                //list，按照顺序为parent节点增加孩子。
                const rapidjson::Value& value1 = array[i];
                parseJsonValue ( value1, parent[i], doc );
            }
            break;
        }
        case rapidjson::kObjectType:
        {
            const rapidjson::Value& obj = value;
            if ( obj.MemberCount() <= 0 )
            {
                parent = QQtOrderedDictionary ( QQtOrderedDictionary::DictMap );
                break;
            }
            for ( rapidjson::Value::ConstMemberIterator itor = obj.MemberBegin(); itor != obj.MemberEnd(); itor++ )
            {
                const rapidjson::Value& rkey = itor->name;
                const rapidjson::Value& rvalue = itor->value;
                QString key = QString::fromStdString ( rkey.GetString() );
                //p2line() << key << QString::fromStdString ( itor.key().asString() );
                //const Json::Value& value = *itor;

                parseJsonValue ( rvalue, parent[key], doc );
            }
            break;
        }
        default:
            p3line() << "unknown type value" << ( int ) value.GetType();
            break;
    }
}
void packDictionaryToJsonValue ( const QQtOrderedDictionary& node, rapidjson::Value& result, rapidjson::Document& doc )
{
    switch ( node.getType() )
    {
        case QQtOrderedDictionary::DictValue:
        {
            //null, bool, double, string
            p3line() << node.getValue().type();
            if ( node.getValue() == QVariant ( QJsonValue() ) )
            {
                result = rapidjson::Value ( );
            }
            else if ( node.getValue().type() == QVariant::Bool )
            {
                result = rapidjson::Value ( node.getValue().toBool() );
            }
            else if ( node.getValue().type() == QVariant::Int )
            {
                result = rapidjson::Value ( ( int ) ( node.getValue().toInt() ) );
            }
            else if ( node.getValue().type() == QVariant::UInt )
            {
                result = rapidjson::Value ( ( unsigned int ) ( node.getValue().toUInt() ) );
            }
            else if ( node.getValue().type() == QVariant::LongLong )
            {
                result = rapidjson::Value ( ( int64_t ) ( node.getValue().toLongLong() ) );
            }
            else if ( node.getValue().type() == QVariant::ULongLong )
            {
                result = rapidjson::Value ( ( uint64_t ) ( node.getValue().toULongLong() ) );
            }
            else if ( node.getValue().type() == QVariant::Double )
            {
                result = rapidjson::Value ( ( double ) ( node.getValue().toDouble() ) );
            }
            else if ( node.getValue().type() == QVariant::String )
            {
                std::string str = node.getValue().toString().toStdString();
                rapidjson::Value str_value ( rapidjson::kStringType );
                str_value.SetString ( str.c_str(), str.size(), doc.GetAllocator() );
                result = str_value;
                //p3line() << node.getValue().toString(); //???? How to print
                //p3line() << QString::fromStdString ( result.asString() );
            }
            break;
        }
        case QQtOrderedDictionary::DictList:
        {
            //"name":[a, b, ...]
            rapidjson::Value array ( rapidjson::kArrayType );
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QQtOrderedDictionary>& l = node.getList();
                rapidjson::Value value;
                packDictionaryToJsonValue ( l[i], value, doc );
                //array.append ( value );
                //array.push_back ( value );
                array.PushBack ( value, doc.GetAllocator() );
            }
            result = array;
            break;
        }
        case QQtOrderedDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            rapidjson::Value object ( rapidjson::kObjectType );
            for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                std::string str = itor.key().toStdString();
                rapidjson::Value key ( rapidjson::kStringType );
                key.SetString ( str.c_str(), str.size(), doc.GetAllocator() );

                const QQtOrderedDictionary& srcvalue = itor.value();
                rapidjson::Value value;
                packDictionaryToJsonValue ( srcvalue, value, doc );
                //object[key] = value;
                object.AddMember ( key, value, doc.GetAllocator() );
            }
            result = object;
            break;
        }
        case QQtOrderedDictionary::DictMax:
        default:
            break;
    }
}
#else
QByteArray toJson ( const QOrderedDictionary& dict, int indent )
{
    //node -> QJsonValue -> QJsonDocument
    QJsonValue value;
    packDictionaryToJsonValue ( dict, value );
    QJsonDocument doc = QJsonDocument::fromVariant ( value.toVariant() );
    QJsonDocument::JsonFormat format = QJsonDocument::Compact;
    if ( indent > 0 )
        format = QJsonDocument::Indented;
    QByteArray result = doc.toJson ( format );
    return result;
}

void fromJson ( const QByteArray& json, QOrderedDictionary& dict )
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

void parseJsonValue ( const QJsonValue& value, QOrderedDictionary& parent )
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
                parent = QOrderedDictionary ( QOrderedDictionary::DictList );
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
                parent = QOrderedDictionary ( QOrderedDictionary::DictMap );
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
void packDictionaryToJsonValue ( const QOrderedDictionary& node, QJsonValue& result )
{
    switch ( node.getType() )
    {
        case QOrderedDictionary::DictValue:
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
        case QOrderedDictionary::DictList:
        {
            //"name":[a, b, ...]
            QJsonArray array;
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QOrderedDictionary>& l = node.getList();
                QJsonValue value;
                packDictionaryToJsonValue ( l[i], value );
                //array.append ( value );
                array.push_back ( value );
            }
            result = array;
            break;
        }
        case QOrderedDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            QJsonObject object;
            for ( QOrderedMap<QString, QOrderedDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                const QString& key = itor.key();
                const QOrderedDictionary& srcvalue = itor.value();
                QJsonValue value;
                packDictionaryToJsonValue ( srcvalue, value );
                object.insert ( key, value );
            }
            result = object;
            break;
        }
        case QOrderedDictionary::DictMax:
        default:
            break;
    }
}
#endif

QByteArray toXML ( const QQtOrderedDictionary& dict, int intent )
{
    QDomDocument doc;
    packDictionaryToDomNode ( dict, doc, doc );
    return doc.toByteArray ( intent );
}

void fromXML ( const QByteArray& xml, QQtOrderedDictionary& dict )
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

void parseDomNode ( const QDomNode& value, QQtOrderedDictionary& parent )
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
            QQtOrderedDictionary node_count;
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

void packDictionaryToDomNode ( const QQtOrderedDictionary& node, QDomNode& result, QDomDocument& doc )
{
    switch ( node.getType() )
    {
        case QQtOrderedDictionary::DictValue:
        {
            //null, bool, double, string
            p3line() << node.getValue().type();
            QDomNode& object = result;
            QDomText text = doc.createTextNode ( node.getValue().toString() );
            object.appendChild ( text );
            break;
        }
        case QQtOrderedDictionary::DictList:
        {
            //<book a="1"> ... </book>
            //<book a="2"> ... </book>
            QDomNode& object = result;
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QQtOrderedDictionary>& l = node.getList();
                QString nodeName = object.nodeName();//error，这个位置好像来不了。
                QDomElement value = doc.createElement ( nodeName );
                packDictionaryToDomNode ( l[i], value, doc );
                object.appendChild ( value );
            }
            break;
        }
        case QQtOrderedDictionary::DictMap:
        {
            //<person a="1">
            //  <sub-person b="10"> </sub-person>
            //  <sub-person2 b="11"> </sub-person2>
            //</person>
            QDomNode& object = result;

            for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor = node.getMap().begin(); itor != node.getMap().end();
                  itor++ )
            {
                //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                const QString& key = itor.key();
                const QQtOrderedDictionary& srcvalue = itor.value();

                //1! "__processinginstruction__" <?xml version='1.0' encoding='UTF-8'?>
                if ( key == "__processinginstruction__" )
                {
                    //"xml"
                    for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        const QString& key2 = itor2.key();
                        const QQtOrderedDictionary& srcvalue2 = itor2.value();
                        QDomProcessingInstruction node0 = doc.createProcessingInstruction ( key2, srcvalue2.getValue().toString() );
                        object.appendChild ( node0 );
                    }
                    continue;
                }
            }

            for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                const QString& key = itor.key();
                const QQtOrderedDictionary& srcvalue = itor.value();

                if ( key == "__processinginstruction__" )
                    continue;

                //2! "__attributes__" <Person attr-key="attr-value"> </Person>
                if ( key == "__attributes__" )
                {
                    //"attributes" key = value
                    for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        const QString& key2 = itor2.key();
                        const QQtOrderedDictionary& srcvalue2 = itor2.value();
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
                    if ( srcvalue.getType() == QOrderedDictionary::DictValue )
                    {
                        const QString& value2 = srcvalue.getValue().toString();
                        QDomComment text = doc.createComment ( value2 );
                        object.appendChild ( text );
                        continue;
                    }

                    //multiple
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QOrderedDictionary>& l = srcvalue.getList();
                        QDomComment text = doc.createComment ( l[i].getValue().toString() );
                        object.appendChild ( text );
                    }
                    continue;
                }
#endif

                if ( key == "#comment" )
                    continue;

                //5! dict["person"][0-] <person>a</person> <person>b</person>
                if ( srcvalue.getType() == QQtOrderedDictionary::DictList )
                {
#if 1
                    //list一定在map里面发生。
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtOrderedDictionary>& l = srcvalue.getList();
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
        case QQtOrderedDictionary::DictMax:
        default:
            break;
    }
}

#ifdef __QTCSVLIB__
QByteArray toCSV ( const QQtOrderedDictionary& dict,
                   const QString& separator,
                   const QString& textDelimiter,
                   const QString& textEncoding
                 )
{
    QtCSV::StringData strlist0;

    for ( int i = 0; i < dict.getList().size(); i++ )
    {
        const QQtOrderedDictionary& v0 = dict.getList() [i];
        QStringList strlist1;
        for ( int j = 0; j < v0.getList().size(); j++ )
        {
            const QQtOrderedDictionary& v1 = v0.getList() [j];
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

void fromCSV ( const QByteArray& csv, QQtOrderedDictionary& dict,
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
QByteArray toIni ( const QQtOrderedDictionary& dict )
{
    const QQtOrderedDictionary& node = dict;

    inifile::IniFile p0;
    switch ( dict.getType() )
    {
        case QQtOrderedDictionary::DictValue:
        {
            break;
        }
        case QQtOrderedDictionary::DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
#if 0
                QList<QOrderedDictionary>& l = node.getList();
                if ( l[i].getType() == QOrderedDictionary::DictValue )
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

                QList<QQtOrderedDictionary>& l = node.getList();
                const QQtOrderedDictionary& srcvalue = l[i];

                p0.AddSection ( stdsec );

                string comment = node["__comments__"][sec]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][sec]["#right_comment"].getValue().toString().toStdString();
                p0.SetComment ( stdsec, "", comment );
                p0.SetRightComment ( stdsec, "", right_comment );

                if ( srcvalue.getType() == QQtOrderedDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtOrderedDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QQtOrderedDictionary::DictValue )
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

                if ( srcvalue.getType() == QQtOrderedDictionary::DictMap )
                {
                    for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QQtOrderedDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QQtOrderedDictionary::DictValue )
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
        case QQtOrderedDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                const QString& sec = itor.key();
                string stdsec = sec.toStdString();
                const QQtOrderedDictionary& srcvalue = itor.value();

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

                if ( srcvalue.getType() == QQtOrderedDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtOrderedDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QQtOrderedDictionary::DictValue )
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

                if ( srcvalue.getType() == QQtOrderedDictionary::DictMap )
                {
                    for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QQtOrderedDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QQtOrderedDictionary::DictValue )
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
        case QQtOrderedDictionary::DictMax:
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

void fromIni ( const QByteArray& bytes, QQtOrderedDictionary& dict )
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

QByteArray toProperties ( const QQtOrderedDictionary& dict )
{
    const QQtOrderedDictionary& node = dict;

    inifile::IniFile p0;
    switch ( dict.getType() )
    {
        case QQtOrderedDictionary::DictValue:
        {
            break;
        }
        case QQtOrderedDictionary::DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
#if 0
                QList<QOrderedDictionary>& l = node.getList();
                if ( l[i].getType() == QOrderedDictionary::DictValue )
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

                QList<QOrderedDictionary>& l = node.getList();
                const QOrderedDictionary& srcvalue = l[i];

                p0.AddSection ( stdsec );

                string comment = node["__comments__"][sec]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][sec]["#right_comment"].getValue().toString().toStdString();
                p0.SetComment ( stdsec, "", comment );
                p0.SetRightComment ( stdsec, "", right_comment );

                if ( srcvalue.getType() == QOrderedDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QOrderedDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QOrderedDictionary::DictValue )
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

                if ( srcvalue.getType() == QOrderedDictionary::DictMap )
                {
                    for ( QOrderedMap<QString, QOrderedDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QOrderedDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QOrderedDictionary::DictValue )
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
                QList<QQtOrderedDictionary>& l = node.getList();
                const QQtOrderedDictionary& srcvalue = l[i];

                if ( key == "__comments__" )
                    continue;

                if ( srcvalue.getType() != QQtOrderedDictionary::DictValue )
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
        case QQtOrderedDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                const QString& key = itor.key();
                string stdkey = key.toStdString();
                const QQtOrderedDictionary& srcvalue = itor.value();

                if ( key == "__comments__" )
                    continue;

                if ( srcvalue.getType() != QQtOrderedDictionary::DictValue )
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
        case QQtOrderedDictionary::DictMax:
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

void fromProperties ( const QByteArray& bytes, QQtOrderedDictionary& dict )
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
QByteArray toYAML ( const QQtOrderedDictionary& dict )
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

void fromYAML ( const QByteArray& yaml, QQtOrderedDictionary& dict )
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



void parseYamlNodeToDictionary ( const YAML::Node& node, QQtOrderedDictionary& object )
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

void packDictionaryToYamlNode ( const QQtOrderedDictionary& node, YAML::Node& object )
{
    switch ( node.getType() )
    {
        case QQtOrderedDictionary:: DictValue:
        {
            //null, bool, double, string
            std::string value = node.getValue().toString().toStdString();
            object = value;
            break;
        }
        case  QQtOrderedDictionary:: DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QQtOrderedDictionary>& l = node.getList();
                YAML::Node value;
                packDictionaryToYamlNode ( l[i], value );
                object.push_back ( value );
            }
            break;
        }
        case QQtOrderedDictionary::  DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QOrderedMap<QString, QQtOrderedDictionary>::Iterator itor = node.getMap().begin(); itor != node.getMap().end();
                  itor++ )
            {
                //QOrderedMap<QString, QOrderedDictionary>& m = node.getMap();
                const QString& qkey = itor.key();
                std::string key = qkey.toStdString();
                const QQtOrderedDictionary& srcvalue = itor.value();
                YAML::Node value;
                packDictionaryToYamlNode ( srcvalue, value );
                object[key] = value;
            }
            break;
        }
        case  QQtOrderedDictionary:: DictMax:
        default:
            break;
    }

}
#endif
