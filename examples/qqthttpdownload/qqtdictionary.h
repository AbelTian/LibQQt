#ifndef QQTDICTIONARY_H
#define QQTDICTIONARY_H

#include <QObject>
#include <QList>
#include <QMap>
#include <qqtcore.h>
#include <qqt-local.h>

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
class QQTSHARED_EXPORT QQtDict : public QObject
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

    explicit QQtDict ( QObject* parent = 0 );
    virtual ~QQtDict() {}

    bool isNull() const;
    bool isValid() const;
    bool isEmpty() const;

    bool isValue( ) const;
    bool isList() const;
    bool isMap() const;

    /*获取数据*/
    QString& getName() const;
    /*获取全部数据*/
    QMap<QString, QQtDict>& getMap() const;
    QList<QQtDict>& getList() const ;

    /*获取单个数据*/
    QVariant& getValue() const;
    QQtDict& getValue ( int index ) const;
    QQtDict& getValue ( const QString& key );
    /*获取一个个孩子*/
    /*list item*/
    QQtDict& getChild ( int index );
    /*map item*/
    QQtDict& getChild ( QString key );

    /*类型*/
    EDictType getType() const;
    /*如果设置Value的时候改变了Type，将会以新的Type为准*/
    void setType ( EDictType type );

    /*插入数据，自动设置type*/

    /*自己本身没有孩子，是个叶子，添加值*/
    void setValue ( QVariant& value );
    /*自己本身有孩子，添加全部孩子*/
    /*whole value list*/
    void setValue ( QList<QQtDict>& list );
    /*whole value map*/
    void setValue ( QMap<QString, QQtDict>& map );
    /*list*/
    void setChild ( QList<QQtDict>& list );
    /*map*/
    void setChild ( QMap<QString, QQtDict>& map );

    /*自己本身没有孩子，添加一个个的孩子*/
    void appendValue ( const QString& value );
    void appendValue ( const QQtDict& dict );
    void appendChild ( const QString& value );
    void appendChild ( const QQtDict& dict );
    /*自己本身有孩子，添加一个个的孩子*/
    void insertValue ( const QString& key, QQtDict& dict );
    void insertChild ( const QString& key, QQtDict& dict );
    void insertValue ( int index, QQtDict& dict );
    void insertChild ( int index, QQtDict& dict );

    /*遍历字典*/
    int count() const;

    bool hasKey ( const QString& key ) const;
    bool hasKey ( const QQtDict& value ) const;
    bool hasChild ( const QString& key ) const;
    bool hasChild ( const QQtDict& value ) const;

    /*操作数据，改变数据*/
    void modValue ( QVariant& value );
    void modValue ( int index, QQtDict& value );
    void modValue ( QString key, QQtDict& value );
    void modChild ( int index, QQtDict& value );
    void modChild ( QString key, QQtDict& value );

    /*删除数据*/
    void clear ( );
    void remove ( int index );
    void remove ( const QString& key );

    /*深拷贝*/
    explicit QQtDict ( const QQtDict& other, QObject* parent = 0 );
    explicit QQtDict ( const QVariant& value, QObject* parent = 0 );
    explicit QQtDict ( const QString name, EDictType type = DictMap, QObject* parent = 0 );
    explicit QQtDict ( const EDictType type, QObject* parent = 0 );

    /*操作符*/
    /*don't out of range*/
    QQtDict& operator [] ( int index );
    /**/
    QQtDict& operator [] ( QString key );
    QQtDict& operator = ( const QMap<QString, QQtDict>& map );
    QQtDict& operator = ( const QList<QQtDict>& list );
    QQtDict& operator = ( const QQtDict& other );
    QQtDict& operator = ( const QVariant& value );
    bool operator == ( const QQtDict& other ) const;

    /*与其他数据结构兼容*/
    QString toXML();
    QString toJson();
    void fromJson ( QString& jsonContent );
    void fromXML ( QString& xmlContent );

signals:

public slots:

private:
    /*节点类型*/
    EDictType m_type;
    /*节点名字*/
    QString m_name;

    /*节点的可能内容枚举*/
    /*叶子：是个数据*/
    QVariant m_value;
    /*不是叶子列表，是个叶子列表，是个叶子列表的值*/
    QList<QQtDict> m_list; //[index]
    /*不是叶子映射，是个子字典，是个叶子，是个叶子的值组合*/
    QMap<QString, QQtDict> m_map;
    /*是个列表和子字典，这是错误的，不可能的*/
};

QDebug operator<< ( QDebug dbg, const QQtDict& d );

#endif // QQTDICTIONARY_H
