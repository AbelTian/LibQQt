#include "qqtdictionary.h"

QQtDictNode::QQtDictNode ( QObject* parent ) :
    QObject ( parent )
{
    m_type = DictMax;
}

bool QQtDictNode::isValue() const
{
    bool is = false;

    if ( m_type == DictValue )
        is = true;

    return is;
}

QQtDictNode::EDictType QQtDictNode::getType() const
{
    return m_type;
}

void QQtDictNode::setType ( QQtDictNode::EDictType type )
{
    m_type = type;
}

void QQtDictNode::setChild ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
}

void QQtDictNode::setChild ( const QList<QQtDictNode>& list )
{
    m_type = DictList;
    m_list = list;
}

void QQtDictNode::setChild ( const QMap<QString, QQtDictNode>& map )
{
    m_type = DictMap;
    m_map = map;
}

void QQtDictNode::appendChild ( const QString& value )
{
    appendChild ( QQtDictNode ( QVariant ( value ) ) );
}

void QQtDictNode::appendChild ( const QQtDictNode& dict )
{
    m_type = DictList;
    m_list.append ( dict );
}

void QQtDictNode::insertChild ( const QString& key, const QQtDictNode& dict )
{
    m_type = DictMap;
    m_map.insert ( key, dict );
}

void QQtDictNode::insertChild ( int index, const QString& value )
{
    insertChild ( index, QQtDictNode ( QVariant ( value ) ) );
}

void QQtDictNode::insertChild ( int index, const QQtDictNode& dict )
{
    m_type = DictList;
    m_list.insert ( index, dict );
}

void QQtDictNode::insertChild ( const QString& key, const QString& value )
{
    insertChild ( key, QQtDictNode ( QVariant ( value ) ) );
}

int QQtDictNode::count() const
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

bool QQtDictNode::isNull() const
{
    if ( m_type == DictMax )
        return true;

    return false;
}

bool QQtDictNode::isValid() const
{
    return isNull();
}
bool QQtDictNode::isEmpty() const
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


bool QQtDictNode::isList() const
{
    bool is = false;

    if ( m_type == DictList )
        is = true;

    return is;
}

bool QQtDictNode::isMap() const
{
    bool is = false;

    if ( m_type == DictMap )
        is = true;

    return is;

}

bool QQtDictNode::hasChild ( const QString& key ) const
{
    bool has = false;

    if ( m_map.contains ( key ) )
        has = true;

    return has;
}

bool QQtDictNode::hasChild ( const QQtDictNode& value ) const
{
    bool has = false;

    if ( m_list.contains ( value ) )
        has = true;

    return has;
}

void QQtDictNode::modValue ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
}

void QQtDictNode::modChild ( int index, const QQtDictNode& value )
{
    m_type = DictList;
    m_list[index] = value;
}

void QQtDictNode::modChild ( QString key, const QQtDictNode& value )
{
    m_type = DictMap;
    m_map[key] = value;
}

void QQtDictNode::clear()
{
    m_value.clear();
    m_list.clear();
    m_map.clear();
}

void QQtDictNode::remove ( int index )
{
    m_list.removeAt ( index );
}

void QQtDictNode::remove ( const QString& key )
{
    m_map.remove ( key );
}

QQtDictNode::QQtDictNode ( const QQtDictNode& other, QObject* parent ) :
    QObject ( parent )
{
    *this = other;
}

QQtDictNode::QQtDictNode ( const QQtDictNode::EDictType type, QObject* parent ) :
    QObject ( parent )
{
    m_type = type;
}

const QQtDictNode QQtDictNode::operator[] ( const QString& key ) const
{
    return m_map[key];
}

const QQtDictNode& QQtDictNode::operator[] ( int index ) const
{
    return m_list[index];
}

QQtDictNode::QQtDictNode ( const QVariant& value, QObject* parent ) :
    QObject ( parent )
{
    *this = value;
}

QQtDictNode& QQtDictNode::operator [] ( int index )
{
    m_type = DictList;

    /*如果index>count，补全*/
    //pline() << m_list.count() << index;

    if ( m_list.count() < index + 1 )
    {
        int cnt = m_list.count();

        /*相差的数量*///count -> index+1 = index+1 - count

        for ( int i = 0; i < index + 1 - cnt; i++ )
            m_list.append ( QQtDictNode() );
    }

    return ( QQtDictNode& ) m_list.operator [] ( index );
}

QQtDictNode& QQtDictNode::operator [] ( const QString& key )
{
    m_type = DictMap;
    return m_map.operator [] ( key );
}

QQtDictNode& QQtDictNode::operator = ( const QMap<QString, QQtDictNode>& map )
{
    m_type = DictMap;
    m_map = map;
    return *this;
}

QQtDictNode& QQtDictNode::operator = ( const QList<QQtDictNode>& list )
{
    m_type = DictList;
    m_list = list;
    return *this;
}

QQtDictNode& QQtDictNode::operator = ( const QQtDictNode& other )
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

QQtDictNode& QQtDictNode::operator = ( const QVariant& value )
{
    m_type = DictValue;
    m_value = value;
    return *this;
}

bool QQtDictNode::operator == ( const QQtDictNode& other ) const
{
    if ( m_type == other.getType() &&
         other.getList() == m_list &&
         other.getMap() == m_map &&
         other.getValue() == m_value )
        return true;

    return false;
}

QMap<QString, QQtDictNode>& QQtDictNode::getMap() const
{
    return ( QMap<QString, QQtDictNode>& ) m_map;
}

QList<QQtDictNode>& QQtDictNode::getList() const
{
    return ( QList<QQtDictNode>& ) m_list;
}

QVariant& QQtDictNode::getValue() const
{
    return ( QVariant& ) m_value;
}

QQtDictNode& QQtDictNode::getChild ( int index )
{
    return m_list[index];
}

QQtDictNode& QQtDictNode::getChild ( const QString& key )
{
    return m_map[key];
}



QDebug operator<< ( QDebug dbg, const QQtDictNode& d )
{
    dbg.nospace() << "\n{" <<
                  " Type:" << d.getType() <<
                  " Count:" << d.count() <<
                  " Value:" << d.getValue() <<
                  " List:" << d.getList() <<
                  " Map:" << d.getMap() <<
                  "}";
    return dbg.space();
}
