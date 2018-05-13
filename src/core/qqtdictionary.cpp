#include "qqtdictionary.h"

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

void QQtDictionary::setChild ( const QVariant& value )
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

void QQtDictionary::appendChild ( const QString& value )
{
    appendChild ( QQtDictionary ( QVariant ( value ) ) );
}

void QQtDictionary::appendChild ( const QQtDictionary& dict )
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
    m_type = DictList;
    m_list[index] = value;
}

void QQtDictionary::modChild ( QString key, const QQtDictionary& value )
{
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



QDebug& operator<< ( QDebug& dbg, const QQtDictionary& d )
{
    if ( d.getType() == QQtDictionary::DictMax )
    {
        dbg << "\n{"
            << "\n"
            << "  Type:" << d.getTypeName()
            << "\n"
            << "  Value:" << d.getValue()
            << "\n}";
    }
    else if ( d.getType() == QQtDictionary::DictValue )
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

        if ( d.getType() == QQtDictionary::DictList )
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
        else if ( d.getType() == QQtDictionary::DictMap )
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

