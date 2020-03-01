#ifndef QQTDICTIONARY_H
#define QQTDICTIONARY_H

#include <QObject>
#include <QList>

class QJsonDocument;
class QJsonValue;
class QDomDocument;
class QDomNode;

#include <qqtorderedmap.h>
#include <qqtcore.h>
#include <qqt-local.h>

/*
 * 简化使用
 * 遍历时
 */
class QQtDictionary;
typedef QMap<QString, QQtDictionary> QQtDictionaryMap;
typedef QMapIterator<QString, QQtDictionary> QQtDictionaryMapIterator;
typedef QMutableMapIterator<QString, QQtDictionary> QQtDictionaryMapConstIterator;

typedef QList<QQtDictionary> QQtDictionaryList;
typedef QListIterator<QQtDictionary> QQtDictionaryListIterator;
typedef QMutableListIterator<QQtDictionary> QQtDictionaryListConstIterator;

/**
 * @brief The QQtDictionary class
 * QQt 字典
 * 字典当中包含
 * 有序tuple 操作方式 dict[0] = ["","","",5] dict[max-1] = {""="",""="",""="",""=""}
 * 不支持无序tuple 操作方式 无
 * 包含具名映射 操作方式 dict["cccc"] = {""="", ""=""} dict["eeee"] = ["", "", ""]
 * 接受嵌套访问 操作方式 dict["cccc"][0]["eeeee"]
 * 通过重载函数来实现类型的变化，不建议使用中更改类型。
 * 比json和xml的数据结构要庞大。toJson toXML fromJson fromXML
 * QVariant 不能直接获取到真实数据，改变必须使用临时变量，而且，接口设计也不够灵活，存入和取出都不太方便。
 * QQtDictionary封装了QVariant，实现直接操作真实数据。提供大量操作符。存取数据方便快捷，类型多样。
 */
class QQTSHARED_EXPORT QQtDictionary
{
    Q_ENUMS ( EDictType )

public:
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

    /*explicit 函数只能作为构造函数，不能作为拷贝构造函数，拷贝构造函数不可加*/
    explicit QQtDictionary ();
    virtual ~QQtDictionary ();

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
    bool hasChild ( const QQtDictionary& value ) const;

    /*获取数据*/
    /*获取全部数据*/
    /*获取当前字典的全部数据*/
    /*保存为[key]=[value]的*/
    QMap<QString, QQtDictionary>& getMap() const;
    /*保存为index=[value]*/
    QList<QQtDictionary>& getList() const ;

    /*获取单个数据*/
    /*保存为value的*/
    QVariant& getValue();
    const QVariant& getValue() const;

    QQtDictionary& getChild ( int index );
    QQtDictionary& getChild ( const QString& key );
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
    void setChild ( const QList<QQtDictionary>& list );
    /*whole value map*/
    void setChild ( const QMap<QString, QQtDictionary>& map );

    /*自己本身没有孩子，添加一个个的孩子*/
    /*index = int*/
    void addChild ( const QString& value );
    void addChild ( const QQtDictionary& dict );

    /*自己本身有孩子，添加一个个的孩子*/
    /*index = int, 会在之前之后插入，现更改为会替换存在的index*/
    /*index = string, 会替换存在的index*/
    void insertChild ( int index, const QString& value );
    void insertChild ( int index, const QQtDictionary& dict );
    void insertChild ( const QString& key, const QString& value );
    void insertChild ( const QString& key, const QQtDictionary& dict );

    /*操作数据，改变数据*/
    void modValue ( const QVariant& value );
    /*没有这个数据会无效*/
    void modChild ( int index, const QQtDictionary& value );
    void modChild ( const QString& key, const QQtDictionary& value );

    /*删除数据*/
    void clear ( );
    void remove ( int index );
    void remove ( const QString& key );

    /*深拷贝*/
    QQtDictionary ( const QQtDictionary& other );
    QQtDictionary ( const QVariant& value );
    QQtDictionary ( const EDictType type );

    /*操作符*/
    /*警告：可读、可写*/
    /*don't out of range? no, it is ok now.*/
    QQtDictionary& operator [] ( int index );
    const QQtDictionary& operator[] ( int index ) const;
    QQtDictionary& operator [] ( const QString& key );
    const QQtDictionary operator[] ( const QString& key ) const;

    QQtDictionary& operator = ( const QMap<QString, QQtDictionary>& map );
    QQtDictionary& operator = ( const QList<QQtDictionary>& list );
    QQtDictionary& operator = ( const QQtDictionary& other );
    QQtDictionary& operator = ( const QVariant& value );
    bool operator == ( const QQtDictionary& other ) const;

    /*与其他数据结构兼容*/
    QString toXML();
    void fromXML ( const QByteArray& xml );
    QByteArray toJson ( QJsonDocument::JsonFormat format = QJsonDocument::Compact );
    void fromJson ( const QByteArray& json );

    //update for new using
    template <typename T>
    bool operator == ( const T& inst ) const {
        return *this == QVariant ( inst );
    }
    bool operator == ( const QVariant& var ) const {
        return *this == QQtDictionary ( var );
    }

    //内部类型转换
    //toValue() toList() toMap(); 不丢失数据方式。

protected:
    virtual void parseJsonValue ( const QJsonValue& value, QQtDictionary& parent );
    virtual void packDictionaryToJsonValue ( const QQtDictionary& node, QJsonValue& result );

    virtual void parseDomNode ( const QDomNode& value, QQtDictionary& parent );
    virtual void packDictionaryToDomElement ( const QQtDictionary& node, QDomNode& result );
signals:

public slots:

private:
    /*节点类型，指示性变量*/
    EDictType m_type;

    /*节点的可能内容枚举*/
    /*叶子：是个数据*/
    /*值保存在这里*/
    QVariant m_value;
    /*不是叶子列表，是个叶子列表，是个叶子列表的值*/
    /*列表保存在这里*//*不如仅仅使用map方便*/
    QList<QQtDictionary> m_list; //[index]
    /*不是叶子映射，是个子字典，是个叶子，是个叶子的值组合*/
    /*映射保存在这里，QStirng可以升级为QVariant*/
    QMap<QString, QQtDictionary> m_map;
    /*是个列表和子字典，这是错误的，不可能的*/
};

QQTSHARED_EXPORT QDebug operator<< ( QDebug dbg, const QQtDictionary& d );

#endif // QQTDICTIONARY_H
