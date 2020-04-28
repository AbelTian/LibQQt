#ifndef QQTFILESYSTEMTREEMODEL_H
#define QQTFILESYSTEMTREEMODEL_H

#include <QFileSystemModel>
#include <qqt-local.h>
/**
 * @brief The QQtFileSystemTreeModel class
 * QFileSystemModel setRootPath 无效
 * QDirModel 没有设置RootPath函数
 * 两者都可以通过QTreeView的setRootIndex来设置RootPath,其实是在QTreeView里面进行过滤。
 * view->setRootIndex ( model->index ( "the/root/path" ) );
 * 废弃，使用QQtDictTreeModel代替。
 */
class QQTSHARED_EXPORT QQtFileSystemTreeModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit QQtFileSystemTreeModel ( QObject* parent = 0 );

signals:

public slots:


protected:

private:
};

#endif // QQTFILESYSTEMTREEMODEL_H
