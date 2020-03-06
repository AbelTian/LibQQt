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
};

#endif // QQTDICTTREEMODEL_H
