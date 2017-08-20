#ifndef QQTFILESYSTEMTREEMODEL_H
#define QQTFILESYSTEMTREEMODEL_H

#include <qqttreemodel.h>

class QQTFileSystemTreeModel : public QQTTreeModel
{
    Q_OBJECT
public:
    explicit QQTFileSystemTreeModel(QObject *parent = 0);

signals:

public slots:

    // QQTTreeModel interface
public:
    bool query(QString condition) override;
    void setFilePath(QString path) override;
};

#endif // QQTFILESYSTEMTREEMODEL_H
