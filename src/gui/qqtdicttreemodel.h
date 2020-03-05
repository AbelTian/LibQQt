#ifndef QQTDICTTREEMODEL_H
#define QQTDICTTREEMODEL_H

#include <qqttreemodel.h>
#include <qqtdictionary.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtDictTreeModel : public QQtTreeModel
{
    Q_OBJECT
public:
    explicit QQtDictTreeModel ( QObject* parent = 0 );

    //里面用的是外面的dictionary句柄，所以外部句柄必须保持存在。
    void setDictionary ( QQtDictionary* dict );
    QQtDictionary* dictionary();

    virtual bool query ( QString condition ) override;

signals:

public slots:

    // QQtDictTreeModel interface
protected:
    virtual void setFilePath ( QString dictfile ) override;

protected:

    virtual void parseDictNodeToModel ( const QQtDictionary& node, QStandardItem& item );

private:
    QQtDictionary* pdict;
};

#endif // QQTDICTTREEMODEL_H
