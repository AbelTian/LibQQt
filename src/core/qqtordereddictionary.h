#ifndef QQTORDEREDDICTIONARY_H
#define QQTORDEREDDICTIONARY_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>

#include <qqtorderedmap.h>

#include <qqtcore.h>
#include <qqt-local.h>

class QOrderedDictionary;
typedef QOrderedMap<QString, QOrderedDictionary> QOrderedDictionaryMap;
typedef QOrderedMapIterator<QString, QOrderedDictionary> QOrderedDictionaryMapIterator;
typedef QMutableMapIterator<QString, QOrderedDictionary> QOrderedDictionaryMutableMapIterator;

typedef QList<QOrderedDictionary> QOrderedDictionaryList;
typedef QListIterator<QOrderedDictionary> QOrderedDictionaryListIterator;
typedef QMutableListIterator<QOrderedDictionary> QOrderedDictionaryMutableListIterator;

/**
 * @brief The QOrderedDictionary class
 * QQt Ordered 字典
 *
 * 使用不排序的map的字典类
 * LinkedHashMap
 * 和QOrderedDictionary一样的功能，仅仅map是不排序的。
 *
 * toJson()   fromJson() 也是不排序的。
 * toXML()    fromXML()  也是不排序的。
 */
class QQTSHARED_EXPORT QOrderedDictionary
{
public:
    /*explicit 函数只能作为构造函数，不能作为拷贝构造函数，拷贝构造函数不可加*/
    explicit QOrderedDictionary ();
    ~QOrderedDictionary ();

    typedef enum tagDictType
    {
        /*只有一个值*/
        DictValue,
        /*是个列表，List不为空，name根据用户设置或许为空*/
        DictList,
        /*是个映射，可能嵌套映射，Map不空，name根据用户设置或许为空*/
        DictMap,

        DictMax
    } EDictType;

    bool isNull() const;
    bool isValid() const;
    bool isEmpty() const;

    bool isValue( ) const;
    bool isList() const;
    bool isMap() const;

    /*遍历字典*/
    int count() const;
    int size() const;

    bool hasChild ( const QString& key ) const;
    bool hasChild ( const QOrderedDictionary& value ) const;

    /*获取数据*/
    /*获取全部数据*/
    /*获取当前字典的全部数据*/
    /*保存为[key]=[value]的*/
    QOrderedMap<QString, QOrderedDictionary>& getMap() const;
    /*保存为index=[value]*/
    QList<QOrderedDictionary>& getList() const ;

    /*获取单个数据*/
    /*保存为value的*/
    QVariant& getValue();
    const QVariant& getValue() const;

    QOrderedDictionary& getChild ( int index );
    QOrderedDictionary& getChild ( const QString& key );
    /*获取一个个孩子*/

    /*类型*/
    EDictType getType() const;
    QString getTypeName() const;

    /*如果设置Value的时候改变了Type，将会以新的Type为准*/
    void setType ( EDictType type );

    //设置value
    template <typename T>
    void setValue ( const T& value ) {
        m_type = DictValue;
        m_value.setValue<T> ( value );
    }
    /*自己本身没有孩子，是个叶子，添加值*/
    void setValue ( const QVariant& value );

    /*插入数据，自动设置type*/
    /*自己本身有孩子，添加全部孩子*/
    /*whole value list*/
    void setChild ( const QList<QOrderedDictionary>& list );
    /*whole value map*/
    void setChild ( const QOrderedMap<QString, QOrderedDictionary>& map );

    /*自己本身没有孩子，添加一个个的孩子*/
    /*index = int*/
    void addChild ( const QString& value );
    void addChild ( const QOrderedDictionary& dict );

    /*自己本身有孩子，添加一个个的孩子*/
    /*index = int, 会在之前之后插入，现更改为会替换存在的index*/
    /*index = string, 会替换存在的index*/
    void insertChild ( int index, const QString& value );
    void insertChild ( int index, const QOrderedDictionary& dict );
    void insertChild ( const QString& key, const QString& value );
    void insertChild ( const QString& key, const QOrderedDictionary& dict );

    /*操作数据，改变数据*/
    void modValue ( const QVariant& value );
    /*没有这个数据会无效*/
    void modChild ( int index, const QOrderedDictionary& value );
    void modChild ( const QString& key, const QOrderedDictionary& value );

    /*删除数据*/
    void clear ( );
    void remove ( int index );
    void remove ( const QString& key );

    /*深拷贝*/
    QOrderedDictionary ( const QOrderedDictionary& other );
    QOrderedDictionary ( const QVariant& value );
    QOrderedDictionary ( const EDictType type );

    /*操作符*/
    /*警告：可读、可写*/
    /*don't out of range? no, it is ok now.*/
    QOrderedDictionary& operator [] ( int index );
    const QOrderedDictionary& operator[] ( int index ) const;
    QOrderedDictionary& operator [] ( const QString& key );
    const QOrderedDictionary operator[] ( const QString& key ) const;

    template <typename T>
    QOrderedDictionary& operator = ( const QList<T>& list1 ) {
        m_type = DictList;
        m_list.clear();
        for ( int i = 0; i < list1.size(); i++ ) {
            const T& v1 = list1[i];
            m_list.push_back ( QOrderedDictionary ( v1 ) );
        }
        return *this;
    }
    QOrderedDictionary& operator = ( const QList<QString>& list );

    QOrderedDictionary& operator = ( const QOrderedMap<QString, QOrderedDictionary>& map );
    QOrderedDictionary& operator = ( const QList<QOrderedDictionary>& list );
    QOrderedDictionary& operator = ( const QOrderedDictionary& other );
    QOrderedDictionary& operator = ( const QVariant& value );
    bool operator == ( const QOrderedDictionary& other ) const;

    //update for new using
    template <typename T>
    bool operator == ( const T& inst ) const {
        return *this == QVariant ( inst );
    }
    bool operator == ( const QVariant& var ) const {
        return *this == QOrderedDictionary ( var );
    }

    //内部类型转换
    //toValue() toList() toMap(); 不丢失数据方式。

    /*与其他数据结构兼容*/
    QByteArray toJson ( int indent = 0 ) const;
    void fromJson ( const QByteArray& json );

    QByteArray toXML ( int indent = -1 ) const;
    void fromXML ( const QByteArray& xml );

    QByteArray toYAML() const;
    void fromYAML ( const QByteArray& yaml );

    //INI, CONF
    QByteArray toINI() const;
    void fromINI ( const QByteArray& ini );

    QByteArray toProperties() const;
    void fromProperties ( const QByteArray& properties );

    //QtCSVLib
    QByteArray toCSV ( const QString& separator = QString ( "," ),
                       const QString& textDelimiter = QString ( "\"" ),
                       const QString& textEncoding = QString ( "UTF-8" )
                     ) const;
    void fromCSV ( const QByteArray& csv,
                   const QString& separator = QString ( "," ),
                   const QString& textDelimiter = QString ( "\"" ),
                   const QString& textEncoding = QString ( "UTF-8" )
                 );

private:
    /*节点类型，指示性变量*/
    EDictType m_type;

    /*节点的可能内容枚举*/
    /*叶子：是个数据*/
    /*值保存在这里*/
    QVariant m_value;
    /*不是叶子列表，是个叶子列表，是个叶子列表的值*/
    /*列表保存在这里*//*不如仅仅使用map方便*/
    QList<QOrderedDictionary> m_list; //[index]
    /*不是叶子映射，是个子字典，是个叶子，是个叶子的值组合*/
    /*映射保存在这里，QStirng可以升级为QVariant*/
    QOrderedMap<QString, QOrderedDictionary> m_map;
    /*是个列表和子字典，这是错误的，不可能的*/
};

QQTSHARED_EXPORT QDebug operator<< ( QDebug dbg, const QOrderedDictionary& d );

#endif // QQTORDEREDDICTIONARY_H

