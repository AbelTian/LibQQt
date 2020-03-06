#ifndef QQTDICTTABLEMODEL_H
#define QQTDICTTABLEMODEL_H

#include <QStandardItemModel>
#include <qqtdictionary.h>
#include <qqt-local.h>

/**
 * @brief The QQtDictTableModel class
 * 把dict[0-][0-]结构的字典加载到Table里。
 *
 * 未实现，QStandardItem无法正常显示，似乎是这个Model不是这个？
 */
class QQTSHARED_EXPORT QQtDictTableModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit QQtDictTableModel ( QObject* parent = 0 );

    //里面用的是外面的dictionary句柄，所以外部句柄必须保持存在。
    void setDictionary ( QQtDictionary* dict );
    QQtDictionary* dictionary();

    //这里会更新内部的pdict；
    virtual void query ( QQtDictionary& dict );

signals:

public slots:

    // QQtDictTableModel interface
public:

protected:

private:

protected:

private:
    QQtDictionary* pdict;
};

#endif // QQTDICTTABLEMODEL_H
