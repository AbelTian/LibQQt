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

QString QQtDictNode::getTypeName() const
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
    //list类
    //append函数，会引用外部变量，push_back是不是在list内部生成了新的实例？
    //m_list.append ( dict );
    m_list.push_back ( dict );
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

    //对于list，不同于map，list当中value相等就是包含。
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
    m_type = DictValue;
    *this = value;
}

QQtDictNode& QQtDictNode::operator [] ( int index )
{
    m_type = DictList;

    /*如果index>count，补全*/
    //pline() << m_list.count() << index;

    //list size = 4, 最大index = 3。新 index = 4, 添加，新index才可以使用，否则out of range。
    if ( m_list.size() < index + 1 )
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



QDebug& operator<< ( QDebug& dbg, const QQtDictNode& d )
{
    if ( d.getType() == QQtDictNode::DictMax )
    {
        dbg << "\n{"
            << "\n"
            << "  Type:" << d.getTypeName()
            << "\n"
            << "  Value:" << d.getValue()
            << "\n}";
    }
    else if ( d.getType() == QQtDictNode::DictValue )
    {
        dbg << "\n{"
            << "\n"
            << "  Type:" << d.getTypeName()
            << "\n"
            << "  Value:" << d.getValue()
            << "\n}";
    }
    else
    {
        dbg << "\n{"
            << "\n"
            << "  Type:" << d.getTypeName()
            << "\n"
            << "  Count:" << d.count();

        if ( d.getType() == QQtDictNode::DictList )
        {
            dbg << "\n"
                << "  List:" << "{";
            for ( int i = 0; i < d.getList().size(); i++ )
            {
                dbg << "\n"
                    << "    id:" << i << "Type:" << d[i].getTypeName() << "Value:" << d[i].getValue();
            }
            dbg << "\n"
                << "  }";
        }
        else if ( d.getType() == QQtDictNode::DictMap )
        {
            dbg << "\n"
                << "  Map:" << "{";
            foreach ( QString key, d.getMap().keys() )
            {
                dbg << "\n"
                    << "    id:" << key << "Type:" << d[key].getTypeName() << "Value:" << d[key].getValue();
            }
            dbg << "\n"
                << "  }";
        }

        dbg << "\n}";
    }

    return dbg.space();
}
