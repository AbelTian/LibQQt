#include "qqtdictionary.h"

QQtDict::QQtDict ( QObject* parent ) :
    QObject ( parent )
{
    m_type = DictMax;
}

bool QQtDict::isValue() const
{
    bool is = false;

    if ( m_type == DictValue )
        is = true;

    return is;
}

QQtDict::EDictType QQtDict::getType() const
{
    return m_type;
}

void QQtDict::setType ( QQtDict::EDictType type )
{
    m_type = type;
}

void QQtDict::setValue ( QVariant& value )
{
    m_type = DictValue;
    m_value = value;
}

void QQtDict::setValue ( QList<QQtDict>& list )
{
    m_type = DictList;
    m_list = list;
}

void QQtDict::setValue ( QMap<QString, QQtDict>& map )
{
    m_type = DictMap;
    m_map = map;
}

void QQtDict::setChild ( QList<QQtDict>& list )
{
    setValue ( list );
}

void QQtDict::setChild ( QMap<QString, QQtDict>& map )
{
    setValue ( map );
}

void QQtDict::appendValue ( const QString& value )
{
    m_type = DictList;
    m_list.push_back ( QQtDict ( QVariant ( value ) ) );
}

void QQtDict::appendValue ( const QQtDict& dict )
{
    m_type = DictList;
    m_list.append ( dict );
}

void QQtDict::appendChild ( const QQtDict& dict )
{
    appendValue ( dict );
}

void QQtDict::insertValue ( const QString& key, QQtDict& dict )
{
    m_type = DictMap;
    m_map.insert ( key, dict );
}

void QQtDict::insertChild ( const QString& key, QQtDict& dict )
{
    insertValue ( key, dict );
}

void QQtDict::insertValue ( int index, QQtDict& dict )
{
    m_type = DictList;
    m_list.insert ( index, dict );
}

void QQtDict::appendChild ( const QString& value )
{
    appendValue ( value );
}

void QQtDict::insertChild ( int index, QQtDict& dict )
{
    insertValue ( index, dict );
}

int QQtDict::count() const
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

bool QQtDict::isNull() const
{
    if ( m_type == DictMax )
        return true;

    return false;
}

bool QQtDict::isValid() const
{
    return isNull();
}
bool QQtDict::isEmpty() const
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


bool QQtDict::isList() const
{
    bool is = false;

    if ( !m_type == DictList )
        is = true;

    return is;
}

bool QQtDict::isMap() const
{
    bool is = false;

    if ( !m_type == DictMap )
        is = true;

    return is;

}

QString& QQtDict::getName() const
{
    return ( QString& ) m_name;
}

bool QQtDict::hasKey ( const QString& key ) const
{
    bool has = false;

    if ( m_type == DictMap )
        if ( m_map.contains ( key ) )
            has = true;

    return has;
}

bool QQtDict::hasKey ( const QQtDict& value ) const
{
    bool has = false;

    if ( m_type == DictList )
        if ( m_list.contains ( value ) )
            has = true;

    return has;
}

bool QQtDict::hasChild ( const QString& key ) const
{
    return hasKey ( key );
}

bool QQtDict::hasChild ( const QQtDict& value ) const
{
    return hasKey ( value );
}

void QQtDict::modValue ( QVariant& value )
{
    if ( DictValue == m_type )
    {
        m_value = value;
    }
}

void QQtDict::modValue ( int index, QQtDict& value )
{
    if ( DictList == m_type )
    {
        m_list[index] = value;
    }
}

void QQtDict::modValue ( QString key, QQtDict& value )
{
    if ( DictMap == m_type )
    {
        m_map[key] = value;
    }
}

void QQtDict::modChild ( int index, QQtDict& value )
{
    modValue ( index, value );
}

void QQtDict::modChild ( QString key, QQtDict& value )
{
    modValue ( key, value );
}

void QQtDict::clear()
{
    if ( DictValue == m_type )
    {
        m_value.clear();
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

void QQtDict::remove ( int index )
{
    if ( DictList == m_type )
    {
        m_list.removeAt ( index );
    }
}

void QQtDict::remove ( const QString& key )
{
    if ( DictMap == m_type )
    {
        m_map.remove ( key );
    }
}

QQtDict::QQtDict ( const QQtDict& other, QObject* parent ) :
    QObject ( parent )
{
    *this = other;
}

QQtDict::QQtDict ( const QString name, QQtDict::EDictType type, QObject* parent ) :
    QObject ( parent )
{
    m_name = name;
    m_type = type;
}

QQtDict::QQtDict ( const QQtDict::EDictType type, QObject* parent ) :
    QObject ( parent )
{
    m_type = type;
}

QQtDict::QQtDict ( const QVariant& value, QObject* parent ) :
    QObject ( parent )
{
    m_value = value;
    m_type = DictValue;
}

QQtDict& QQtDict::operator [] ( int index )
{
    return ( QQtDict& ) m_list.operator [] ( index );
}

QQtDict& QQtDict::operator [] ( QString key )
{
    return m_map.operator [] ( key );
}

QQtDict& QQtDict::operator = ( const QMap<QString, QQtDict>& map )
{
    m_map = map;
    return *this;
}

QQtDict& QQtDict::operator = ( const QList<QQtDict>& list )
{
    m_list = list;
    return *this;
}

QQtDict& QQtDict::operator = ( const QQtDict& other )
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

    m_name = other.getName();
    m_type = type;
    return *this;
}

QQtDict& QQtDict::operator = ( const QVariant& value )
{
    m_value = value;
    return *this;
}

bool QQtDict::operator == ( const QQtDict& other ) const
{
    if ( m_type == other.getType() &&
         other.getName() == m_name &&
         other.getList() == m_list &&
         other.getMap() == m_map &&
         other.getValue() == m_value )
        return true;

    return false;
}

QMap<QString, QQtDict>& QQtDict::getMap() const
{
    return ( QMap<QString, QQtDict>& ) m_map;
}

QList<QQtDict>& QQtDict::getList() const
{
    return ( QList<QQtDict>& ) m_list;
}

QVariant& QQtDict::getValue() const
{
    return ( QVariant& ) m_value;
}

QQtDict& QQtDict::getValue ( int index ) const
{
    return ( QQtDict& ) m_list[index];
}

QQtDict& QQtDict::getValue ( const QString& key )
{
    return m_map[key];
}

QQtDict& QQtDict::getChild ( int index )
{
    return m_list[index];
}

QQtDict& QQtDict::getChild ( QString key )
{
    return m_map[key];
}


QDebug operator<< ( QDebug dbg, const QQtDict& d )
{
    dbg.nospace() << "{" <<
                  "\n Type:" << d.getType() <<
                  "\n Count:" << d.count() <<
                  "\n Name:" << d.getName() <<
                  "\n Value:" << d.getValue() <<
                  "\n List:" << d.getList() <<
                  "\n Map:" << d.getMap() <<
                  "\n}";
    return dbg.space();
}
