#ifndef QQTTREEMODEL_H
#define QQTTREEMODEL_H

#include <QStandardItemModel>
#include <qqt-local.h>

/**
 * this is a interface class
 * define the tree model's functions name.
 */

class QQTSHARED_EXPORT QQtTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit QQtTreeModel(QObject* parent = 0);

    //对于纯虚函数，如果内部重写了，MSVC14编译不过，gcc可以编译过。
    //对于虚函数，带有返回值的必须返回，否则MSVC14编译不过，gcc可以编译过。
    /**
     * @brief query
     * @param condition
     * @return
     */
    virtual bool query(QString condition){ return false; }
    /**
     * @brief setFilePath
     * @param name
     */
    virtual void setFilePath(QString name){}

signals:

public slots:
};

#endif // QQTTREEMODEL_H
