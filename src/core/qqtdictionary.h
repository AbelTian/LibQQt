#ifndef QQTDICTIONARY_H
#define QQTDICTIONARY_H

#include <QObject>
#include <QList>
#include <QMap>
#include <qqtcore.h>
#include <qqt-local.h>

/*
 * 简化使用
 * 遍历时
 */
class QQtDictNode;
typedef QMap<QString, QQtDictNode> QQtMapNode;
typedef QMapIterator<QString, QQtDictNode> QQtMapNodeIterator;

typedef QList<QQtDictNode> QQtListNode;
typedef QListIterator<QQtDictNode> QQtListNodeIterator;

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
 * QVariant 不能直接获取到真实数据，改变必须使用临时变量。
 * 而且，接口设计也不够灵活，存入和取出都不太方便。
 */
class QQTSHARED_EXPORT QQtDictNode : public QObject
{
    Q_OBJECT
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
    explicit QQtDictNode ( QObject* parent = 0 );
    virtual ~QQtDictNode() {}

    bool isNull() const;
    bool isValid() const;
    bool isEmpty() const;

    bool isValue( ) const;
    bool isList() const;
    bool isMap() const;

    /*遍历字典*/
    int count() const;

    bool hasChild ( const QString& key ) const;
    bool hasChild ( const QQtDictNode& value ) const;

    /*获取数据*/
    /*获取全部数据*/
    QMap<QString, QQtDictNode>& getMap() const;
    QList<QQtDictNode>& getList() const ;

    /*获取单个数据*/
    QVariant& getValue() const;
    QQtDictNode& getChild ( int index );
    QQtDictNode& getChild ( const QString& key );
    /*获取一个个孩子*/

    /*类型*/
    EDictType getType() const;

    /*如果设置Value的时候改变了Type，将会以新的Type为准*/
    void setType ( EDictType type );

    /*插入数据，自动设置type*/
    /*自己本身没有孩子，是个叶子，添加值*/
    void setChild ( const QVariant& value );
    /*自己本身有孩子，添加全部孩子*/
    /*whole value list*/
    void setChild ( const QList<QQtDictNode>& list );
    /*whole value map*/
    void setChild ( const QMap<QString, QQtDictNode>& map );

    /*自己本身没有孩子，添加一个个的孩子*/
    /*index = int*/
    void appendChild ( const QString& value );
    void appendChild ( const QQtDictNode& dict );

    /*自己本身有孩子，添加一个个的孩子*/
    /*index = int, 会在之前之后插入，现更改为会替换存在的index*/
    /*index = string, 会替换存在的index*/
    void insertChild ( int index, const QString& value );
    void insertChild ( int index, const QQtDictNode& dict );
    void insertChild ( const QString& key, const QString& value );
    void insertChild ( const QString& key, const QQtDictNode& dict );

    /*操作数据，改变数据*/
    void modValue ( const QVariant& value );
    void modChild ( int index, const QQtDictNode& value );
    void modChild ( QString key, const QQtDictNode& value );

    /*删除数据*/
    void clear ( );
    void remove ( int index );
    void remove ( const QString& key );

    /*深拷贝*/
    QQtDictNode ( const QQtDictNode& other, QObject* parent = 0 );
    QQtDictNode ( const QVariant& value, QObject* parent = 0 );
    QQtDictNode ( const EDictType type, QObject* parent = 0 );

    /*操作符*/
    /*警告：可读、可写*/
    /*don't out of range*/
    QQtDictNode& operator [] ( int index );
    const QQtDictNode& operator[] ( int index ) const;
    QQtDictNode& operator [] ( const QString& key );
    const QQtDictNode operator[] ( const QString& key ) const;

    QQtDictNode& operator = ( const QMap<QString, QQtDictNode>& map );
    QQtDictNode& operator = ( const QList<QQtDictNode>& list );
    QQtDictNode& operator = ( const QQtDictNode& other );
    QQtDictNode& operator = ( const QVariant& value );
    bool operator == ( const QQtDictNode& other ) const;

    /*与其他数据结构兼容*/
    QString toXML();
    QString toJson();
    void fromJson ( QString& jsonContent );
    void fromXML ( QString& xmlContent );

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
    QList<QQtDictNode> m_list; //[index]
    /*不是叶子映射，是个子字典，是个叶子，是个叶子的值组合*/
    /*映射保存在这里，QStirng可以升级为QVariant*/
    QMap<QString, QQtDictNode> m_map;
    /*是个列表和子字典，这是错误的，不可能的*/
};

QDebug operator<< ( QDebug dbg, const QQtDictNode& d );

#endif // QQTDICTIONARY_H
