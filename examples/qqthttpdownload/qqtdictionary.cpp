#include "qqtdictionary.h"

QQtDictionary::QQtDictionary ( QObject* parent ) :
    QObject ( parent )
{
    m_type = DictMax;
}

bool QQtDictionary::isValue()
{
    bool is = false;

    if ( m_type == DictValue )
        is = true;

    return is;
}

QQtDictionary::EDictType QQtDictionary::getType() { return m_type; }

void QQtDictionary::setType ( QQtDictionary::EDictType type )
{
    m_type = type;
}

void QQtDictionary::setValue ( QVariant& value )
{
    m_type = DictValue;
    m_value = value;
}

void QQtDictionary::setValue ( QList<QVariant>& list )
{
    m_type = DictValueList;
    m_valueList = list;
}

void QQtDictionary::setValue ( QMap<QString, QVariant>& map )
{
    m_type = DictValueMap;
    m_valueMap = map;
}

void QQtDictionary::addValue ( QVariant& value )
{
    m_type = DictValueList;
    m_valueList.append ( value );
}

void QQtDictionary::insertValue ( QString key, QVariant& value )
{
    m_type = DictValueMap;
    m_valueMap.insert ( key, value );
}

void QQtDictionary::insertValue ( int index, QVariant& value )
{
    m_type = DictValueList;
    m_valueList.insert ( index, value );
}

void QQtDictionary::setChild ( QList<QQtDictionary>& list )
{
    m_type = DictList;
    m_list = list;
}

void QQtDictionary::setChild ( QMap<QString, QQtDictionary>& map )
{
    m_type = DictMap;
    m_map = map;
}

void QQtDictionary::addChild ( QQtDictionary& dict )
{
    m_type = DictList;
    m_list.append ( dict );
}

void QQtDictionary::insertChild ( QString key, QQtDictionary& dict )
{
    m_type = DictMap;
    m_map.insert ( key, dict );
}

void QQtDictionary::addChild ( int index, QQtDictionary& dict )
{
    m_type = DictList;
    m_list.insert ( index, dict );
}

int QQtDictionary::count()
{
    int cnt = -1;

    if ( DictList == m_type )
        cnt = m_list.count();
    else if ( DictMap == m_type )
        cnt = m_map.count();
    else if ( DictValueList == m_type )
        cnt = m_valueList.count();
    else if ( DictValueMap == m_type )
        cnt = m_valueMap.count();
    else if ( DictValue == m_type )
        cnt = 1;

    return cnt;
}

bool QQtDictionary::isNull()
{
    if ( m_type == DictMax )
        return true;

    return false;
}

bool QQtDictionary::isValid()
{
    return isNull();
}
bool QQtDictionary::isEmpty()
{
    bool isEmpty = true;

    switch ( m_type )
    {
    case DictValue:
        if ( !m_value.isNull() )
            isEmpty = false;

        break;

    case DictValueList:
        if ( !m_valueList.isEmpty() )
            isEmpty = false;

        break;

    case DictValueMap:
        if ( !m_valueMap.isEmpty() )
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


bool QQtDictionary::isList()
{
    bool is = false;

    if ( !m_type == DictList )
        is = true;

    return is;
}

bool QQtDictionary::isValueList()
{
    bool is = false;

    if ( !m_type == DictValueList )
        is = true;

    return is;
}

bool QQtDictionary::isMap()
{
    bool is = false;

    if ( !m_type == DictMap )
        is = true;

    return is;

}

bool QQtDictionary::isValueMap()
{
    bool is = false;

    if ( !m_type == DictValueMap )
        is = true;

    return is;
}

QString& QQtDictionary::getName()
{
    return m_name;
}

bool QQtDictionary::hasValue ( QString key )
{
    bool has = false;

    if ( m_type == DictValueMap )
        if ( m_valueMap.contains ( key ) )
            has = true;

    return has;
}

bool QQtDictionary::hasValue ( QVariant& value )
{
    bool has = false;

    if ( m_type == DictValueList )
        if ( m_valueList.contains ( value ) )
            has = true;

    return has;
}

bool QQtDictionary::hasChild ( QString& key )
{
    bool has = false;

    if ( m_type == DictMap )
        if ( m_map.contains ( key ) )
            has = true;

    return has;
}

bool QQtDictionary::hasChild ( QQtDictionary& value )
{
    bool has = false;

    if ( m_type == DictList )
        if ( m_list.contains ( value ) )
            has = true;

    return has;
}

void QQtDictionary::modValue ( QVariant& value )
{
    if ( DictValue == m_type )
    {
        m_value = value;
    }
}

void QQtDictionary::modValue ( int index, QVariant& value )
{
    if ( DictValueList == m_type )
    {
        m_valueList[index] = value;
    }
}

void QQtDictionary::modValue ( QString key, QVariant& value )
{
    if ( DictValueMap == m_type )
    {
        m_valueMap[key] = value;
    }
}

void QQtDictionary::modChild ( int index, QQtDictionary& value )
{
    if ( DictList == m_type )
    {
        m_list[key] = value;
    }
}

void QQtDictionary::modChild ( QString key, QQtDictionary& value )
{
    if ( DictMap == m_type )
    {
        m_map[key] = value;
    }
}

void QQtDictionary::clear()
{
    if ( DictValue == m_type )
    {
        m_value.clear();
    }
    else if ( DictValueList == m_type )
    {
        m_valueList.clear();
    }
    else if ( DictValueMap == m_type )
    {
        m_valueMap.clear();
    }
    else if ( DictList == m_type )
    {
        m_list.clear();
    }
    else if ( DictMap == m_type )
    {
        m_map.clear();
    }
}

void QQtDictionary::remove ( int index )
{
    if ( DictValueList == m_type )
    {
        m_valueList.removeAt ( index );
    }
    else if ( DictList == m_type )
    {
        m_list.removeAt ( index );
    }
}

void QQtDictionary::remove ( QString key )
{
    if ( DictMap == m_type )
    {
        m_map.remove ( key );
    }
    else if ( DictValueMap == m_type )
    {
        m_valueMap.remove ( key );
    }
}

QQtDictionary::QQtDictionary ( QQtDictionary& other, QObject* parent ) :
    QObject ( parent )
{
    EDictType type = other.getType();

    switch ( type )
    {
    case DictValue:
        m_value = other.getValue() ;
        break;

    case DictValueList:
        m_valueList = other.getValueList();
        break;

    case DictValueMap:
        m_valueMap = other.getValueMap();

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

    m_name = other.getName();
    m_type = type;
}

QQtDictionary::QQtDictionary ( QString& name, QQtDictionary::EDictType type, QObject* parent ) :
    QObject ( parent )
{
    m_name = name;
    m_type = type;
}

QQtDictionary::QQtDictionary ( QQtDictionary::EDictType type, QObject* parent ) :
    QObject ( parent )
{
    m_type = type;
}

QQtDictionary& QQtDictionary::operator [] ( int index )
{
    return ( QQtDictionary& ) m_list.operator [] ( index );
}

QQtDictionary& QQtDictionary::operator [] ( QString key )
{
    return m_map.operator [] ( key );
}

QQtDictionary& QQtDictionary::operator = ( QMap<QString, QVariant>& map )
{
    m_valueMap = map;
    return *this;
}

QQtDictionary& QQtDictionary::operator = ( QMap<QString, QQtDictionary>& map )
{
    m_map = map;
    return *this;
}

QQtDictionary& QQtDictionary::operator = ( QList<QVariant>& list )
{
    m_valueList = list;
    return *this;
}

QQtDictionary& QQtDictionary::operator = ( QList<QQtDictionary>& list )
{
    m_list = list;
    return *this;
}

QQtDictionary& QQtDictionary::operator = ( QQtDictionary& other )
{
    EDictType type = other.getType();

    switch ( type )
    {
    case DictValue:
        m_value = other.getValue() ;
        break;

    case DictValueList:
        m_valueList = other.getValueList();
        break;

    case DictValueMap:
        m_valueMap = other.getValueMap();

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

    m_name = other.getName();
    m_type = type;
}

QMap<QString, QQtDictionary>& QQtDictionary::getMap()
{
    return m_map;
}

QList<QQtDictionary>& QQtDictionary::getList()
{
    return m_list;
}

QMap<QString, QVariant>& QQtDictionary::getValueMap()
{
    return m_valueMap;
}

QList<QVariant>& QQtDictionary::getValueList()
{
    return m_valueList;
}

QVariant& QQtDictionary::getValue()
{
    return m_value;
}

QVariant& QQtDictionary::getValue ( int index )
{
    return ( QVariant& ) m_valueList[index];
}

QVariant& QQtDictionary::getValue ( QString key )
{
    return m_valueMap[key];
}

QQtDictionary& QQtDictionary::getChild ( int index )
{
    return m_list[key];
}

QQtDictionary& QQtDictionary::getChild ( QString key )
{
    return m_map[key];
}

