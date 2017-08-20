#ifndef QQTCLOUDTREEWIDGET_H
#define QQTCLOUDTREEWIDGET_H

#include "qqttreeview.h"
#include "qqtcloudtreemodel.h"
#include "qqtfilesystem.h"

namespace Ui {
class QQTTreeWidget;
}

/**
 * @brief The QQTTreeWidget class
 * 仅仅用于文件系统显示和功能
 */
class QQTCloudTreeWidget : public QQTTreeView
{
    Q_OBJECT

public:
    explicit QQTCloudTreeWidget(QWidget *parent = 0);
    ~QQTCloudTreeWidget();

    bool open()
    { return m_fs->open(); }
    void closeQQTcfs()
    { m_fs->close(); }

    inline QQTFileSystem* fileSystem()
    { return m_fs; }

    /*
     * 从查询结果中过滤出rootpath里面的内容进行保存；
     */
    void setRootPath();
    /*
     * 过滤，排序
     */
    inline void setNameFilter(QString filter)
    { m_model->setNameFilter(filter); }
    inline void setFilter(QDir::Filters filter = QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot)
    { m_model->setFilter(filter); }
    inline void setSorting(QDir::SortFlags sort = QDir::DirsFirst | QDir::Name | QDir::Reversed)
    { m_model->setSorting(sort); }

    void query(QString path = "local://.");
    void removeRow();

private slots:
    void currentRowChanged();
    void clicked(QModelIndex);

private:
    Ui::QQTTreeWidget *ui;
    QQTCloudTreeModel* m_model;
    QQTFileSystem* m_fs;
    QString m_prot;
};

#endif // QQTCLOUDTREEWIDGET_H
