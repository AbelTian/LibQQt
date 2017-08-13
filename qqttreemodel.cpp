#include "qqttreemodel.h"
#include <QStandardItem>

QQTTreeModel::QQTTreeModel(QObject *parent, QQTFileSystem* fs) :
    QStandardItemModel(parent), m_fs(fs)
{
    connect(m_fs, SIGNAL(result()),
            this, SLOT(result()));
}

bool QQTTreeModel::query(QString path)
{
    m_path = path;
    bool ret = m_fs->query(path);

    return ret;
}

bool QQTTreeModel::removeRow(int arow, const QModelIndex &aparent)
{
    //fs
    QString prot, name;
    m_fs->parse(m_path, prot, name);


    QString file = data(index(arow, FILE_FILEPATH, aparent)).toString();

    QString sPath = QString("%1%2").arg(prot).arg(file);
    m_fs->del(sPath);
    return QStandardItemModel::removeRow(arow, aparent);
}

QList<QStandardItem *> QQTTreeModel::findItems(const QString &text, Qt::MatchFlags flags, int column) const
{
    QList<QStandardItem*> l;
    const QModelIndex root = QModelIndex();
    l = findItems(root, text, flags, column);
    return l;
}

QList<QStandardItem *> QQTTreeModel::findItems(const QModelIndex &parent, const QString &text, Qt::MatchFlags flags, int column) const
{
    QList<QStandardItem *> l;

    for(int row = 0; row < rowCount(parent); row++)
    {
        QList<QStandardItem *> ll;

        QModelIndex idx = index(row, column, parent);

        /*
        pline() << rowCount(parent) << row;
        pline() << idx;
        pline() << data(idx).toString() << text;
        pline() << idx.child(0, 0);
        */

        if(idx.child(0, 0).isValid())
        {
            ll = findItems(idx, text, flags, column);
            l += ll;
        }


        /*
        pline() << flags.operator &(Qt::MatchExactly);
        pline() << ( flags & Qt::MatchExactly ) ;
        pline() << flags;
        pline() << flags.testFlag( Qt::MatchExactly );
        */
        if( flags.testFlag( Qt::MatchExactly ) )
        {
            pline();
            if(data(idx).toString() == text)
            {
                l.push_back(itemFromIndex(idx));
                pline();
            }
        }

        if( flags.testFlag( Qt::MatchContains ) )
            if(data(idx).toString().contains( text) ||
                    text.contains(data(idx).toString()))
                l.push_back(itemFromIndex(idx));
    }
    return l;
}

void QQTTreeModel::result()
{


    QString prot, file;
    m_fs->parse(m_path, prot, file);

    pline() << m_path << prot << file;


    QQTFilesInfo files = m_fs->record();

    if(prot != files.m_prot)
        return;        

    QList<QStandardItem*> itemList = findItems(files.m_path, Qt::MatchExactly, FILE_FILEPATH);
    pline() << "find directory num" << itemList.size() << prot << file;

    pline() << itemFromIndex(QModelIndex());

    QModelIndex parent = QModelIndex();

    if(itemList.size() == 0)
    {
        removeRows(0, rowCount());
        setColumnCount(FILE_MAX);
        setRowCount(0);
   }
    else
    {
        QStandardItem *dir = item(itemList.at(0)->row(), 0);
        dir->removeRows(0, dir->rowCount());
        dir->setColumnCount(FILE_MAX);
        dir->setRowCount(0);

        parent = dir->index();
    }

    int row = 0;
    QListIterator<QQTFileInfo> itor(files.m_filelist);
    while(itor.hasNext())
    {
        QQTFileInfo f = itor.next();
        pline() << f.m_path << f.m_fileName << f.m_filePath;
        insertRows(row, 1, parent);
        setData(index(row, FILE_NAME, parent), f.m_fileName);
        setData(index(row, FILE_PATH, parent), f.m_path);
        setData(index(row, FILE_TYPE, parent), f.m_fileType);

        if(f.m_fileType == "dir")
            setData(index(row, FILE_NAME, parent), QIcon("./skin/default/folder.ico") , Qt::DecorationRole);
            else if(f.m_fileType == "file")
            setData(index(row, FILE_NAME, parent), QIcon("./skin/default/file.ico") , Qt::DecorationRole);

setData(index(row, FILE_FILEPATH, parent), f.m_filePath);
        row++;
    }

    submit();
}
