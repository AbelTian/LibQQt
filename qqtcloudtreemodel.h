#ifndef QQTCLOUDTREEMODEL_H
#define QQTCLOUDTREEMODEL_H

#include <QStandardItemModel>
#include "qqtfilesystem.h"

class QQTCloudTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit QQTCloudTreeModel(QObject *parent, QQTFileSystem* fs);

    /*
     * 从查询结果中过滤出rootpath里面的内容进行保存；
     */
    void setRootPath();
    /*
     * 过滤，排序
     */
    inline void setNameFilter(QString filter)
    { m_fs->setNameFilter(filter); }
    inline void setFilter(QDir::Filters filter = QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot)
    { m_fs->setFilter(filter); }
    inline void setSorting(QDir::SortFlags sort = QDir::DirsFirst | QDir::Name)
    { m_fs->setSorting(sort); }

    bool query(QString path);

    bool removeRow(int arow, const QModelIndex &aparent);

    QList<QStandardItem*> findItems(const QString &text,
                                    Qt::MatchFlags flags = Qt::MatchExactly,
                                    int column = 0) const;
    QList<QStandardItem *> findItems(const QModelIndex& parent, const QString &text,
                                    Qt::MatchFlags flags = Qt::MatchExactly,
                                    int column = 0) const;
signals:

public slots:

private slots:
    void result();

private:
    QQTFileSystem* m_fs;
    QString m_path;
};

#endif // QQTCLOUDTREEMODEL_H
