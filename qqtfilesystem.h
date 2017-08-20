#ifndef QQTFILESYSTEM_H
#define QQTFILESYSTEM_H

#include <QDir>
#include <QFileInfo>
#include "qqtdefine.h"
#include "qqtcloudprotocol.h"

class QQTFileInfo
{
public:
    QQTFileInfo(){}

    QQTFileInfo setFileInfo(const QFileInfo &fileinfo)
    {
        m_prot = "local://";
        m_fileType = fileinfo.isDir() ? "dir" : "file";
        m_path = fileinfo.path();
        m_filePath = fileinfo.filePath();
        m_abslutFilePath = fileinfo.absoluteFilePath();
        m_upcode;
        m_code;
        m_id;
        m_fileName = fileinfo.fileName();
        m_size = fileinfo.size();
        m_date = fileinfo.lastModified().toString("yyyy/MM/dd hh:mm");
        return *this;
    }

    QQTFileInfo &operator=(const QQTFileInfo &fileinfo)
    {
        m_prot = fileinfo.m_prot;
        m_fileType = fileinfo.m_fileType;
        m_path = fileinfo.m_path;
        m_filePath = fileinfo.m_filePath;
        m_abslutFilePath = fileinfo.m_abslutFilePath;
        m_upcode = fileinfo.m_upcode;
        m_code = fileinfo.m_code;
        m_id = fileinfo.m_id;
        m_fileName = fileinfo.m_fileName;
        m_size = fileinfo.m_size;
        m_date = fileinfo.m_date;
        return *this;
    }

    QString m_fileType;
    QString m_prot;
    QString m_path;
    QString m_filePath;
    QString m_abslutFilePath;
    QString m_upcode;
    QString m_code;
    QString m_id;
    QString m_fileName;
    QString m_size;
    QString m_date;
};


class QQTFilesInfo
{
public:
    QQTFilesInfo(){}

    int size()
    {
        return m_filelist.size();
    }
    void clear()
    {
        m_prot = "";
        m_path = "";
        m_upcode = "";
        m_code = "";
        m_filelist.clear();
    }
    void push_back(QQTFileInfo f)
    {
        m_prot = f.m_prot;
        m_path = f.m_path;
        m_upcode = f.m_upcode;
        m_code = f.m_code;
        m_filelist.push_back(f);
    }
    QQTFilesInfo &operator = (const QQTFilesInfo& f)
    {
        m_prot = f.m_prot;
        m_path = f.m_path;
        m_upcode = f.m_upcode;
        m_code = f.m_code;
        m_filelist = f.m_filelist;
        return *this;
    }

    QString m_prot;
    QString m_path;
    QString m_upcode;
    QString m_code;
    QList<QQTFileInfo> m_filelist;
};


/**
 * @brief The QQTFileSystem class
 * 继承QObject不允许拷贝或者QSqlDatabase
 * 规格要求：QSqlDatabase
 * "local://"
 * "htp://"
 * "QQTFS":"QQTCFS"-"FS"
 * 组织变化小 PC之间变化大
 */
class QQTFileSystem : public QObject
{
    Q_OBJECT
public:
    QQTFileSystem(QObject* parent = 0);
    ~QQTFileSystem();

    /*
     * 如果需要使用htp协议，就可以使用
     */
    bool open();
    bool close();
    bool isOpen();
    bool isQueryed();

    //QQTfs -> path
    /*
     * 假设已经将QQT网络硬盘映射到htp:/
     * 本地硬盘已经映射到local:/
     */
    void addwangluocipanYingshe();
    /*
     * 所有的操作都不会逃出当前路径，默认当前路径
     */
    void setRootPath();
    /*
     * 如果是映射中的路径，自动按照协议进行查询
     * 如果是其他路径，那么按照本地协议进行查询那么按照协议格式来作为输入参数很合理
     */
    bool query(QString path = "local:///");
    QQTFilesInfo& record();

    void create();//
    void del(QString filePath = "htp://Method");
    void copy(QString src = "local://Method/system.db",
              QString dst = "htp://Method");
    void cancel();

    void parse(QString path, QString& protocolName, QString& files);
    QQTFileInfo findFile(QString srcFile);

    void setHostName();
    void setUserName();
    void setPassword();
    void setPort();
    inline void setNameFilter(QString filter)
    { m_nameFileter = filter; }
    inline void setFilter(QDir::Filters filter = QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot)
    { m_filter = filter; }
    inline void setSorting(QDir::SortFlags sort = QDir::DirsFirst | QDir::Name)
    { m_sort = sort; }

public slots:

signals:
    void result();
    //void openSucc();
    //void openFail();
    void status(int nPecent);
    //void delSucc();
    //void delFail();
    void copySucc(QString dst);
    void copyFail(QString dst);
private slots:
    void queryFilesResult();
    void openLock();
    void testOpenSucc();
    void testOpenSuccOther();
    void slotUploadSuccess();
private:
    enum {
        EAUTO,
        EQUERY,
        EDOWN,
        EUPLOAD,
    };

    //traslation instance
    QQTClient* m_client;
    //translation protocol
    QQTCloudProtocol* m_protocol;
    QQTFilesInfo m_rootDir;
    QQTFilesInfo m_methodDir;
    QQTFilesInfo m_dataDir;
    QQTFilesInfo m_result;
    QString m_nameFileter;
    QDir::Filters m_filter;
    QDir::SortFlags m_sort;
    QQTBlock m_block;
    QString m_dst;
    QString m_src;
};

QQTFileSystem* QQTFileSystemInstance(QObject* parent = 0);

#endif // QQTFILESYSTEM_H
