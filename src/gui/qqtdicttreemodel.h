#ifndef QQTDICTTREEMODEL_H
#define QQTDICTTREEMODEL_H

#include <qqttreemodel.h>
#include <qqtdictionary.h>
#include <qqt-local.h>

/**
 * @brief The QQtDictTreeModel class
 * 把Dict的子节点全都加载到TreeModel
 */
class QQTSHARED_EXPORT QQtDictTreeModel : public QQtTreeModel
{
    Q_OBJECT
public:
    explicit QQtDictTreeModel ( QObject* parent = 0 );

    //里面用的是外面的dictionary句柄，所以外部句柄必须保持存在。
    void setDictionary ( QQtDictionary* dict );
    QQtDictionary* dictionary();

    //这里会更新内部的pdict；
    virtual void query ( QQtDictionary& dict );

    //无论用户选中哪个Item，这个函数都会计算第一列从根到叶子的值列表。
    virtual QStringList getFullName ( const QModelIndex& index );

    //查看是否是叶子节点，是否有孩子
    bool isLeafNode ( const QModelIndex& index );

    //查看是否是Root节点，是否有父亲。这种节点可能有多个。
    bool isRootNode ( const QModelIndex& index );

signals:

public slots:

    // QQtDictTreeModel interface
protected:
    virtual bool query ( QString condition ) override;
    virtual void setFilePath ( QString dictfile ) override;

protected:
    virtual void packDictionaryToTreeModel ( const QQtDictionary& node, QStandardItem* pobject );

private:
    QQtDictionary* pdict;

#if 0
    // QAbstractItemModel interface
    // 一般EditRole和DisplayRole保存一样的数据。
public:
    virtual QVariant data ( const QModelIndex& index, int role ) const override {
        //根据index的column从字典中获取数据返回。
        if ( !pdict )
            return QVariant();

        //返回默认的也可以，二选一。
    }
    virtual bool setData ( const QModelIndex& index, const QVariant& value, int role ) override {
        //根据index的column向字典中设置数据。
        if ( !pdict )
            return false;

        //返回默认的也可以，二选一。
    }
#endif
};

#endif // QQTDICTTREEMODEL_H
