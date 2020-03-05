#ifndef QQTFTPTREEMODEL_H
#define QQTFTPTREEMODEL_H

#include <QObject>
#include "qqt-local.h"

/**
 * @brief The QQtFTPTreeModel class
 * 将FTP解析到QQtDictionary里，然后写入Model。
 * 未实现
 */
class QQTSHARED_EXPORT QQtFTPTreeModel : public QObject
{
    Q_OBJECT
public:
    explicit QQtFTPTreeModel ( QObject* parent = 0 );

signals:

public slots:
};

#endif // QQTFTPTREEMODEL_H
