#ifndef QQTDICTIONARY_H
#define QQTDICTIONARY_H

#include <QObject>
#include <QList>
#include <QMap>
#include <qqtcore.h>
#include <qqt-local.h>


class QQTSHARED_EXPORT QQtDictNode : public QObject
{
    Q_OBJECT
public:
    explicit QQtDictNode ( QObject* parent = nullptr ) :
        QObject ( parent ) {
        m_list.clear();
        m_map.clear();
    }
    virtual ~QQtDictNode() {}
private:
    /*是个list*/
    QList<QVariant> m_list;
    /*是个map*/
    QMap<QString, QVariant> m_map;
};
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
class QQTSHARED_EXPORT QQtDictionary : public QObject
{
    Q_OBJECT
    Q_ENUMS ( EDictType )

public:
    typedef enum tagDictType
    {
        DictValue,
        DictValueList,
        DictValueMap,
        DictList,
        DictMap,
        DictMax
    } EDictType;

    explicit QQtDictionary ( QObject* parent = 0 );
    virtual ~QQtDictionary() {}

    bool isNull();
    bool isValid();
    bool isEmpty();

    bool isValue( );
    bool isList();
    bool isValueList();
    bool isMap();
    bool isValueMap();

    /*获取数据*/
    QString& getName();
    /*获取全部数据*/
    QMap<QString, QQtDictionary>& getMap();
    QList<QQtDictionary>& getList();
    QMap<QString, QVariant>& getValueMap();
    QList<QVariant>& getValueList();
    /*获取单个数据*/
    QVariant& getValue();
    QVariant& getValue ( int index );
    QVariant& getValue ( QString key );
    /*获取一个个孩子*/
    /*list item*/
    QQtDictionary& getChild ( int index );
    /*map item*/
    QQtDictionary& getChild ( QString key );

    /*类型*/
    EDictType getType();
    /*如果设置Value的时候改变了Type，将会以新的Type为准*/
    void setType ( EDictType type );

    /*插入数据，自动设置type*/
    /*自己本身没有孩子，是个叶子，添加值*/
    void setValue ( QVariant& value );
    /*whole value list*/
    void setValue ( QList<QVariant>& list );
    /*whole value map*/
    void setValue ( QMap<QString, QVariant>& map );
    /*自己本身没有孩子，添加一个个的孩子*/
    void addValue ( QVariant& value );
    void insertValue ( QString key, QVariant& value );
    void insertValue ( int index, QVariant& value );
    /*自己本身有孩子，添加全部孩子*/
    /*list*/
    void setChild ( QList<QQtDictionary>& list );
    /*map*/
    void setChild ( QMap<QString, QQtDictionary>& map );
    /*自己本身有孩子，添加一个个的孩子*/
    void addChild ( QQtDictionary& dict );
    void insertChild ( QString key, QQtDictionary& dict );
    void addChild ( int index, QQtDictionary& dict );

    /*遍历字典*/
    int count();
    bool hasValue ( QString key );
    bool hasValue ( QVariant& value );
    /*这个说的就是map和valuemap了*/
    bool hasChild ( QString& key );
    bool hasChild ( QQtDictionary& value );

    /*操作数据，改变数据*/
    void modValue ( QVariant& value );
    void modValue ( int index, QVariant& value );
    void modValue ( QString key, QVariant& value );
    void modChild ( int index, QQtDictionary& value );
    void modChild ( QString key, QQtDictionary& value );

    /*删除数据*/
    void clear ( );
    void remove ( int index );
    void remove ( QString key );

    /*深拷贝*/
    explicit QQtDictionary ( QQtDictionary& other, QObject* parent = 0 );
    explicit QQtDictionary ( QString& name, EDictType type = DictMap, QObject* parent = 0 );
    explicit QQtDictionary ( EDictType type, QObject* parent = 0 );

    /*操作符*/
    QQtDictionary& operator [] ( int index );
    QQtDictionary& operator [] ( QString key );
    QQtDictionary& operator = ( QMap<QString, QVariant>& map );
    QQtDictionary& operator = ( QMap<QString, QQtDictionary>& map );
    QQtDictionary& operator = ( QList<QVariant>& list );
    QQtDictionary& operator = ( QList<QQtDictionary>& list );
    QQtDictionary& operator = ( QQtDictionary& other );
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
    /*叶子：是个值列表*/
    QList<QVariant> m_valueList; //[index]
    /*叶子：是个值字典*/
    QMap<QString, QVariant> m_valueMap;
    /*不是叶子，是个列表*/
    QList<QQtDictionary> m_list; //[index]
    /*不是叶子，是个子字典*/
    QMap<QString, QQtDictionary> m_map;
    /*是个列表和子字典，这是错误的，不可能的*/
};

#endif // QQTDICTIONARY_H
