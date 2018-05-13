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

    /**
     * @brief query
     * @param condition
     * @return
     */
    virtual bool query(QString condition) = 0;
    /**
     * @brief setFilePath
     * @param name
     */
    virtual void setFilePath(QString name) = 0;

signals:

public slots:
};

#endif // QQTTREEMODEL_H
