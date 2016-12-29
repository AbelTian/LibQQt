#include "qqtfilesystem.h"
#include <QDir>
#include <QDirModel>
#include <QFileSystemModel>
#include <QFileSystemWatcher>

QQTFileSystem::QQTFileSystem(QObject *parent) :
    QObject(parent)
{
    //如果用QQTClientInstance会调用两次connected，来历不明
    //如果把代码移到Open中激发一次connect
    //如果改成new QQTClient，没有问题；
    //疑似：connect函数连接几次调用几次。下面这段打印来自于连接了一次
    //../k1160pro/QQTWidgets/QQTfilesystem.cpp 207 testOpenSucc QQTFileSystem(0x2d262c0)
    //../k1160pro/QQTWidgets/QQTfilesystem.cpp 207 testOpenSucc QQTFileSystem(0x2d262c0)
    //../k1160pro/QQTWidgets/QQTfilesystem.cpp 207 testOpenSucc QQTFileSystem(0x2d2e4c0)
    //../k1160pro/QQTWidgets/QQTfilesystem.cpp 207 testOpenSucc QQTFileSystem(0x2d2e4c0)
    //证明：connect连接几次调用几次，上述情况属于moc偶现bug，多次增量编译容易出现。
    //添加if判断，证明connect，连接几次调用几次,而且内部判断信号和槽的连接，仅仅根据sender和信号的名字来，
    //不论receiver的地址和槽名字，全都发到一次地址的槽里。
    //我猜测，第一次连接上的是不能用的，因为他会接收无数的槽调用；通过尝试，改回来，bug消失。
    //和槽是否存在无关。
    //为了避免再次出现，此处使用new，可是我到处都在用，从widget导出。
    //m_client = new QQTClient(parent);
    m_client = QQTCloudClientInstance(this);
    m_protocol = new QQTCloudProtocol(this);

    m_client->installProtocol(m_protocol);

    connect(m_protocol, SIGNAL(signalLoginSucc()), this, SIGNAL(openSucc()));
    connect(m_protocol, SIGNAL(signalConnectFail()), this, SIGNAL(openFail()));
    connect(m_protocol, SIGNAL(signalLoginSucc()), this, SLOT(openLock()));
    connect(m_protocol, SIGNAL(signalConnectFail()), this, SLOT(openLock()));

    connect(m_protocol, SIGNAL(signalListFileOK()), this, SLOT(queryFilesResult()));
    //下载
    connect(m_protocol, SIGNAL(signalDownSucc()), this, SLOT(slotDownSuccess()));
    connect(m_protocol, SIGNAL(signalCancelDown()), this, SLOT(slotCancelDown()));
    //上传
    connect(m_protocol, SIGNAL(signalUploadSucc()), this, SLOT(slotUploadSuccess()));
    //connect(m_client, SIGNAL(signalCancelUpload()), this, SLOT(slotUploadSuccess()));

    connect(m_protocol, SIGNAL(signalUpdateProgress(int)),
            this, SIGNAL(status(int)));
}

QQTFileSystem::~QQTFileSystem()
{

}

/**
 * @brief QQTFileSystem::open
 * @return
 * 登陆成功，返回true，否则一直返回false
 */
bool QQTFileSystem::open()
{
    //connect none sense?feel?
    m_client->SendConnectMessage();
    m_block.lock(30000);

    if(m_protocol->isLogined())
    {
        pline() << "open ok";
        return true;
    }

    pline() << "open timeout";
    return false;
}

void QQTFileSystem::openLock()
{
    if(m_block.isLocked())
        m_block.unlock();
}

bool QQTFileSystem::close()
{
    if(m_block.isLocked())
    {
        pline() << "close locked";
        m_block.unlock();
    }

    //以关闭为准
    int ret = m_client->SendDisConnectFromHost();

        pline() << "close ok";
    return true;
}

bool QQTFileSystem::isOpen()
{
    return m_protocol->isLogined();
}

bool QQTFileSystem::isQueryed()
{
    if(m_result.size() >0)
        return true;
    else
        return false;
}

bool QQTFileSystem::query(QString path)
{
    QString prot; QString paths;
    parse(path, prot, paths);

    pline() << path << prot << paths;

    if(prot.contains("htp"))
    {
        if(!m_protocol->isLogined())
            return false;

        QString code = "";
        if(paths.isEmpty() || paths == "/" || paths == ".")
        {
            QQTFileInfo f, f2;
            f.m_fileName = "Method";
            f.m_code = "001";
            f.m_path = "/";
            f.m_prot = "htp://";
            f.m_filePath = f.m_path + f.m_fileName;
            f.m_fileType = "dir";

            f2.m_fileName = "Data";
            f2.m_code = "002";
            f2.m_path = "/";
            f2.m_prot = "htp://";
            f2.m_filePath = f2.m_path + f2.m_fileName;
            f2.m_fileType = "dir";

            m_rootDir.clear();
            m_rootDir.push_back(f);            
            m_rootDir.push_back(f2);
            m_rootDir.m_code = "";
            m_rootDir.m_path = "/";
            m_rootDir.m_prot = "htp://";
            m_rootDir.m_upcode = "";
            //OK
            m_result = m_rootDir;
            emit result();
            return true;
        }
        else if(paths.contains("Method"))
            code = "001";
        else if(paths.contains("Data"))
            code = "002";

        m_protocol->sendListFiles(code);
    }

    else if(prot.contains("local"))
    {
        QDir dir(paths);

        pline() << dir.exists();

        if(!dir.exists())
            return false;

        dir.setNameFilters(QDir::nameFiltersFromString(m_nameFileter));
        dir.setFilter(m_filter);
        dir.setSorting(m_sort);

        pline() << dir;

        QFileInfoList list = dir.entryInfoList();

        pline() << list.count();

        m_result.clear();
        QFileInfo qf;
        foreach (qf, list) {
            pline() << qf.fileName() << qf.filePath() << qf.path() << qf.absolutePath() << qf.absoluteFilePath();
            QQTFileInfo f;
            f.setFileInfo(qf);
            f.m_prot = "local://";
            m_result.push_back(f);
            m_result.m_code = "";
            m_result.m_path = qf.path();
            m_result.m_prot = "local://";
            m_result.m_upcode = "";
        }

        //OK
        emit result();
    }

    return true;
}


void QQTFileSystem::queryFilesResult()
{
    QTCloudListFileResult r = m_protocol->GetListedFiles();
    _QTCloudListFileResult _r;

    m_result.clear();
    foreach (_r, r.m_file) {
        QQTFileInfo f;
        f.m_fileName = _r.m_name;
        f.m_id = _r.m_id;
        f.m_size = _r.m_size;
        f.m_date = _r.m_date;
        f.m_prot = "htp://";
        if(r.m_code == "001")
            f.m_path = "/Method";
        else if(r.m_code == "002")
            f.m_path = "/Data";
        f.m_filePath = f.m_path + "/" + f.m_fileName;
        f.m_fileType = "file";
        m_result.push_back(f);
        m_result.m_code = r.m_code;
        m_result.m_path = f.m_path;

        m_result.m_prot = "htp://";
        m_result.m_upcode = "";
    }

    if(r.m_code == "001")
        m_methodDir = m_result;
    else if(r.m_code == "002")
        m_dataDir = m_result;

    emit result();

}

void QQTFileSystem::testOpenSucc()
{
    pline() << this;

}

void QQTFileSystem::testOpenSuccOther()
{
    pline() << this;
}

void QQTFileSystem::slotUploadSuccess()
{
    QString uri;
    QString code;
    if(m_dst.contains("htp"))
        uri = m_dst;
    else
        uri = m_src;

    query(uri);
}

void QQTFileSystem::del(QString filePath)
{
    QString prot; QString files;
    parse(filePath, prot, files);

    pline() << filePath << prot << files;

    if(prot.contains("local"))
    {
        system(QString("rm -f %1").arg(files).toAscii().constData());
        return;
    }

    QString code;
    if(files.contains("Method"))
    {
        m_result = m_methodDir;
        code = "001";
    }
    else
    {
        m_result = m_dataDir;
        code = "002";
    }

    QQTFileInfo f = findFile(files);

    pline() << code << f.m_id << files;
    m_protocol->sendDelFile(code, f.m_id);
}

void QQTFileSystem::copy(QString src, QString dst)
{
    m_src = src;
    m_dst = dst;

    QString srcFile , srcProt;
    parse(src, srcProt, srcFile);

    QString dstFile, dstProt;
    parse(dst, dstProt, dstFile);

    pline() << src << dst;

    //本地
    if(srcProt.contains("local") && dstProt.contains("local"))
    {
        system(QString("cp -fr %1 %2 ")
               .arg(srcFile)
               .arg(dstFile)
               .toAscii().constData());
        ;
    }
    else if(srcProt.contains("htp") && dstProt.contains("htp"))
        ;
    //down
    else if(srcProt.contains("htp") && dstProt.contains("local"))
    {
        QString code;
        if(srcFile.contains("Method"))
        {
            m_result = m_methodDir;
            code = "001";
        }
        else
        {
            m_result = m_dataDir;
            code = "002";
        }

        QQTFileInfo f = findFile(srcFile);

        pline() << code << f.m_id << srcFile << dstFile;
        m_protocol->sendDownDevFiles(f.m_id, dstFile);
    }
    //up
    else if(srcProt.contains("local") && dstProt.contains("htp"))
    {
        QString code;
        if(dstFile.contains("Method"))
        {
            code = "001";
        }
        else if(dstFile.contains("Data"))
        {
            code = "002";
        }

        pline() << code << dstFile << srcFile;

        QStringList dstL = dstFile.split("/");
        QString dst = dstL.last();
        pline() << dst;

        m_protocol->sendUploadFile(code, dst, srcFile);
    }

}

void QQTFileSystem::cancel()
{
    if(m_src.contains("htp") && m_dst.contains("local"))
    {
        m_protocol->sendCancelDown();
    }
    else if(m_src.contains("local") && m_dst.contains("htp"))
    {
        m_protocol->sendCancelUpload();
    }
}

QQTFilesInfo &QQTFileSystem::record()
{
    return m_result;
}

void QQTFileSystem::parse(QString path, QString& protocolName, QString& files)
{
    if(path.contains("htp://"))
        protocolName = "htp://";
    else if(path.contains("local://"))
        protocolName = "local://";
    QStringList p0 = path.split("//");
    files = p0[1];
    //pline() << p0 << files;
}

QQTFileInfo QQTFileSystem::findFile(QString srcFile)
{
    QQTFileInfo f;
    QListIterator<QQTFileInfo> itor(m_result.m_filelist);
    while(itor.hasNext())
    {
        f = itor.next();
        if(srcFile.contains(f.m_fileName))
        {
            //pline() << f.m_fileName << f.m_id << id << srcFile;
            break;
        }
    }

    return f;
}

QQTFileSystem *QQTFileSystemInstance(QObject *parent)
{
    static QQTFileSystem* QQTfs = new QQTFileSystem(parent);
    return QQTfs;
}
