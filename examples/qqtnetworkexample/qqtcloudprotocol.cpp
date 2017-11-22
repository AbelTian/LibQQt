#include "qqtcloudprotocol.h"
#include "qqtversion.h"
#include "qqtcore.h"
#include "qqt-qt.h"

QQtSocketTcpClient* QQTUpgradeClientInstance(QObject* parent)
{
    static QQtSocketTcpClient* cli = NULL;
    if (!cli)
    {
        QStringList ip;
        ip << "222.175.114.244" << "124.133.1.54";
        //"www.QQToo.com"
        cli = new QQtSocketTcpClient(parent);
        cli->SetServerIPAddress(ip);
        cli->SetServerPort(8089);
    }
    return cli;
}

QQtSocketTcpClient* QQTCloudClientInstance(QObject* parent)
{
    static QQtSocketTcpClient* cli = NULL;
    if (!cli)
    {
        QStringList ip;
        ip << "222.175.114.244" << "124.133.1.54";
        cli = new QQtSocketTcpClient(parent);
        cli->SetServerIPAddress(ip);
        cli->SetServerPort(7079);
    }
    return cli;
}


QQTCloudProtocol::QQTCloudProtocol(QObject* parent) : QQtProtocol(parent)
{
    m_isLogined = false;
    m_heartCount = 0;
    m_UID = 0;
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendHeatBeatMessage()));

    connect(this, SIGNAL(signalSendData()), this, SLOT(sendUploadFileData()), Qt::QueuedConnection);
    connect(this, SIGNAL(signalDownData()), this, SLOT(sendDownFileData()), Qt::QueuedConnection);
    connect(this, SIGNAL(signalDownSucc()), this, SLOT(sendDownFileSuccess()), Qt::QueuedConnection);


}

QTCheckVersionResult& QQTCloudProtocol::GetVersionResult() { return m_versionresult; }

QTCloudListDirResult& QQTCloudProtocol::GetDirList() { return m_dirs; }

QTCloudListFileResult& QQTCloudProtocol::GetListedFiles() { return m_files; }

bool QQTCloudProtocol::isLogined() { return m_isLogined; }

void QQTCloudProtocol::startHeartBeat()
{
    m_heartCount = 0;
    /*
     * TODO:心跳检测重连会不会引发这条消息？
     * 如果连接还未成功开始发送心跳包，
     * QNativeSocketEngine::write() was not called in QAbstractSocket::ConnectedState
     */
    timer->start(30 * 1000);
}

void QQTCloudProtocol::stopHeartBeat()
{
    m_heartCount = MAX_HEARDBEAT + 1;
    timer->stop();
}

void QQTCloudProtocol::sendMessage(quint16 cmd, QByteArray& data)
{
    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(cmd);
    qMsg.setData(data);
    qMsg.translate();
    //pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);
}

bool QQTCloudProtocol::dispatcher(const QByteArray& m)
{
    bool ret = true;

    QQTNetworkMessage qMsg;
    qMsg.parser(m);
    //pline() << qMsg;

    switch (qMsg.cmd())
    {
    case _TCPCMD_LOGINRESUALT:
        recvLoginResultMessage(qMsg);
        break;
    case _TCPCMD_HEARTBEATRESP:
        recvHeatBeatResultMessage(qMsg);
        break;
    case _TCPCMD_CHECKVERSIONRSP:
        recvCheckVersionResult(qMsg);
        break;
    case _TCPCMD_RECEIVEDIRLIST:
        recvListDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEADDRESUALT:
        recvAddDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEALTERRESUALT:
        recvModDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEDELETERESUALT:
        recvDelDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEFILELIST:
        recvListFilesResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEPUBLICDIRLIST:
        recvListPubDirResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEPUBLICFILELIST:
        recvListPubFilesResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEFILEINFO:
        recvDownFileResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVEFILEDATA:
        recvDownFileDataResultMessage(qMsg);
        break;
    case _TCPCMD_RECEIVECOMFIREFILEINFO:
        recvUploadFileResult(qMsg);
        break;
    case _TCPCMD_RECEIVECOMFIREFILEDATA:
        recvUploadFileDataResult(qMsg);
        break;
    case _TCPCMD_RECEIVECOMFIREFILE:
        recvUploadFileSuccess(qMsg);
        break;
    default:
        //pline() << "receive unknown command:" << hex << qMsg.cmd();
        ret = false;
        break;
    }

    return ret;
}


void QQTCloudProtocol::sendHeatBeatMessage()
{
    /*
     * 断链判断 如果断链 TODO:
     */
    if (m_heartCount > MAX_HEARDBEAT)
    {
#if 1
        /*
         * 重连策略 30 * 2 s
         */
        static int curp = 0;
        if (curp >= 2)
        {
            curp = 0;
            emit signalReconnectQequest();
            return;
        }
        curp++;
#else
        /*
         * 此处设置重连策略 30s 150s 300s 600s
         */
        static int p[4] = {1, 5, 10, 20};
        static int curp = 0;
        static int curpos = 0;
        if (curp >= p[curpos])
        {
            curp = 0;
            curpos = (curpos + 1) % 4;
            connectToSingelHost();
            return;
        }
        curp++;
#endif
        return;
    }
    pline() << "HeartBeat Count:" << m_heartCount;
    m_heartCount++;
    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_TCPCMD_HEART);
    qMsg.translate();
    pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);
    //waitForBytesWritten();
}

void QQTCloudProtocol::sendLoginMessage()
{
    /*
     * 这个地方可能要改动，串口发过来的时字符串，不是hex
     */
    QSettings set;
    QByteArray _name = set.value("Device/DeviceNo").toByteArray();
    QByteArray _pwd = set.value("Device/Password").toByteArray();

    QString name, pwd;
    for (int i = 0; i < _name.size(); i++)
        name += QString::number((quint8)_name[i], 16);
    for (int i = 0; i < _pwd.size(); i++)
        pwd += QString::number((quint8)_pwd[i], 16);
    name = name.toUpper();
    pwd = pwd.toUpper();

    m_isLogined = false;
    QTCloudLogin t;
    t.m_name = name;
    t.m_password = pwd;
    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_TCPCMD_LOGIN);
    QByteArray d;
    packLoginData(d, t);
    qMsg.setData(d);
    qMsg.translate();
    //pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);
}

void QQTCloudProtocol::sendLogoutMessage()
{
    m_isLogined = false;
    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_TCPCMD_EXIT);
    qMsg.translate();
    //pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);
}

void QQTCloudProtocol::recvConnPoolFullMessage(QQTNetworkMessage&) {}


void QQTCloudProtocol::recvLoginResultMessage(QQTNetworkMessage& qMsg)
{
    m_UID = qMsg.uid();
    QTCloudLoginResult qtLoginResult;
    parseLoginResultData(qtLoginResult, qMsg.data());
    switch (qtLoginResult.m_result)
    {
    case 0x00:
    {
        pline() << "Login success id:" << hex << m_UID;
        m_isLogined = true;
        emit signalLoginSucc();
    }
    break;
    case 0x10:
        pline() << "Other user logined";
        break;
    case 0x11:
        pline() << "User unexisted";
        break;
    case 0x12:
        pline() << "Password error upflowed";
        break;
    case 0x23:
    case 0x22:
    case 0x21:
        pline() << "Password error" << hex << qtLoginResult.m_result;
        break;
    case 0xFF:
    default:
        pline() << "unknown error" << qtLoginResult.m_result;
        break;
    }

    if (0x00 != qtLoginResult.m_result)
        emit signalLoginFail();
}

void QQTCloudProtocol::recvHeatBeatResultMessage(QQTNetworkMessage&)
{
    m_heartCount = 0;
    pline() << "HeartBeat Callback";
}


void QQTCloudProtocol::packCheckVersionData(QByteArray& l, const QTCheckVersion& t)
{
    packKeyWordToByteArray(l, _TCP_SECTION_SOFTWAREID, t.m_softwareid);
    packKeyWordToByteArray(l, _TCP_SECTION_DEVICECODE, t.m_devicecode);
    packKeyWordToByteArray(l, _TCP_SECTION_SOFTWARECODE, t.m_softwarecode);
    packKeyWordToByteArray(l, _TCP_SECTION_VERSION, t.m_version);
}

void QQTCloudProtocol::parseCheckVersionResultData(QTCheckVersionResult& t, const QByteArray& l)
{
    quint32 pos = 0;
    QByteArray b = l;
    t.m_softwareid = parseKeyWordInByteArray(b, _TCP_SECTION_SOFTWAREID, pos);
    t.m_devicecode = parseKeyWordInByteArray(b, _TCP_SECTION_DEVICECODE, pos);
    t.m_softwarecode = parseKeyWordInByteArray(b, _TCP_SECTION_SOFTWARECODE, pos);
    t.m_version = parseKeyWordInByteArray(b, _TCP_SECTION_VERSION, pos);
    t.m_NewSoftwareID = parseKeyWordInByteArray(b, _TCP_SECTION_NEWSOFTWAREID, pos);

    /*
     * 和公共文件区域的一样，郑工服务器端按照
     */
    QByteArray m_Explain = parseKeyWordInByteArray(b, _TCP_SECTION_EXPLAIN, pos);
    QTextCodec* Codec = QTextCodec::codecForName("gbk");
    t.m_Explain = Codec->toUnicode(m_Explain);

    t.m_ReleaseStatus = parseKeyWordInByteArray(b, _TCP_SECTION_RELEASESTAT, pos);
    t.m_ReleaseDate = parseKeyWordInByteArray(b, _TCP_SECTION_RELEASEDATE, pos);
    t.m_FileName = parseKeyWordInByteArray(b, _TCP_SECTION_FILENAME, pos);
    t.m_FileMD5 = parseKeyWordInByteArray(b, _TCP_SECTION_FILEMD5, pos);
    t.m_FileSize = parseKeyWordInByteArray(b, _TCP_SECTION_FILESIZE, pos);
}


void QQTCloudProtocol::sendCheckVersion()
{
    QTCheckVersion t;
    t.m_softwareid = "0";
    t.m_devicecode = "0601";
    t.m_softwarecode = "211100";
    t.m_version = FILE_VERSION;
    quint16 _tcpcmd = _TCPCMD_CHECKVERSION;

    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_tcpcmd);
    QByteArray d;
    packCheckVersionData(d, t);
    qMsg.setData(d);
    qMsg.translate();
    //pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);
}

void QQTCloudProtocol::sendCheckNewVersion()
{
    QTCheckVersion t;
    t.m_softwareid = m_versionresult.m_NewSoftwareID;
    t.m_devicecode = "";
    t.m_softwarecode = "";
    t.m_version = FILE_VERSION;
    quint16 _tcpcmd = _TCPCMD_CHECKVERSION;

    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_tcpcmd);
    QByteArray d;
    packCheckVersionData(d, t);
    qMsg.setData(d);
    qMsg.translate();
    //pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);
}

void QQTCloudProtocol::recvCheckVersionResult(QQTNetworkMessage& qMsg)
{
    parseCheckVersionResultData(m_versionresult, qMsg.data());
    emit signalCheckVersionResult();
}


void QQTCloudProtocol::packListDirData(QByteArray& l, const QTCloudListDir& t)
{
    l = t.m_code.toLatin1();
}

void QQTCloudProtocol::parseListDirResultData(QTCloudListDirResult& r, const QByteArray& l)
{
    quint32 pos = 0;
    QByteArray b = l;
    QByteArray h;
    h = parseKeyWordInByteArray(b, _TCP_SECTION_UPCODE, pos);
    r.m_upcode = h;
    while (pos < b.length())
    {
        _QTCloudListDirResult _r;
        QByteArray __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_ID, pos);
        _r.m_id = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_CODE, pos);
        _r.m_code = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_NAME, pos);
        _r.m_name = __r;
        r.m_dir.push_back(_r);
    }
}

void QQTCloudProtocol::packAddDirData(QByteArray& l, const QTCloudAddDir& t)
{
    packKeyWordToByteArray(l, _TCP_SECTION_UPCODE, t.m_upcode);
    packKeyWordToByteArray(l, _TCP_SECTION_CODE, t.m_code);
    packKeyWordToByteArray(l, _TCP_SECTION_NAME, t.m_name);
}

void QQTCloudProtocol::parseAddDirResultData(QTCloudAddDirResult& t, const QByteArray& l)
{
    quint32 pos = 0;
    QByteArray b = l;
    t.m_upcode = parseKeyWordInByteArray(b, _TCP_SECTION_UPCODE, pos);
    t.m_result = parseKeyWordInByteArray(b, _TCP_SECTION_RESULE, pos);
}

void QQTCloudProtocol::packDelFileData(QByteArray& l, const QTCloudDelFile& t)
{
    packKeyWordToByteArray(l, _TCP_SECTION_CODE, t.m_code);
    packKeyWordToByteArray(l, _TCP_SECTION_ID, t.m_id);
}

void QQTCloudProtocol::parseListFileResultData(QTCloudListFileResult& r, const QByteArray& l)
{
    quint32 pos = 0;
    QByteArray b = l;
    QByteArray h;
    h = parseKeyWordInByteArray(b, _TCP_SECTION_CODE, pos);
    r.m_code = h;
    while (pos < b.length())
    {
        _QTCloudListFileResult _r;
        QByteArray __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_ID, pos);
        _r.m_id = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_NAME, pos);
        _r.m_name = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_SIZE, pos);
        _r.m_size = __r;
        __r = parseKeyWordInByteArray(b, _TCP_SECTION_DATE, pos);
        _r.m_date = __r;
        r.m_file.push_back(_r);
    }
}

void QQTCloudProtocol::packDownDevFileData(QByteArray& l, const QTCloudDownDevFile& t)
{
    l = t.m_id.toLatin1();
}

void QQTCloudProtocol::parseDownDevFileResultData(QTCloudDownDevFileResult& t, const QByteArray& l)
{
    quint32 pos = 0;
    QByteArray b = l;
    t.m_fileno = parseKeyWordInByteArray(b, _TCP_SECTION_FILENO, pos);
    t.m_name = parseKeyWordInByteArray(b, _TCP_SECTION_NAME, pos);
    t.m_length = parseKeyWordInByteArray(b, _TCP_SECTION_LENGTH, pos);
}

void QQTCloudProtocol::packDownDevFileSuccessData(QByteArray& l, const QTCloudDownFileSuccess& t)
{
    l << t.m_fileno;
}

void QQTCloudProtocol::packDownDevFileDataData(QByteArray& l, const QTCloudDownFileData& t)
{
    l << t.m_fileno << t.m_dno;
}

void QQTCloudProtocol::parseDownDevFileDataResultData(QTCloudDownFileDataResult& t, const QByteArray& l)
{
    quint32 pos = 0;
    QByteArray b = l;
    b >> t.m_fileno >> t.m_dno >> t.m_addr >> t.m_dlen;
    t.m_data.resize(t.m_dlen);
    b >> t.m_data;
}

void QQTCloudProtocol::packUploadFileData(QByteArray& l, const QTCloudUploadFile& t)
{
    l = QString(_TCPCMD_DATASENDFILEINFO).arg(t.m_code).arg(t.m_name).arg(t.m_overwrite).arg(t.m_length).toLatin1();
}

void QQTCloudProtocol::parseUploadFileResultData(QTCloudUploadFileResult& t, const QByteArray& l)
{
    QByteArray b = l;
    b >> t.m_fileno >> t.m_state;
}

void QQTCloudProtocol::packUploadFileDataData(QByteArray& l, const QTCloudUploadFileData& t)
{
    l << t.m_fileno << t.m_dno << t.m_addr << t.m_dlen << t.m_data;
}

void QQTCloudProtocol::parseUploadFileDataResultData(QTCloudUploadFileDataResult& t, const QByteArray& l)
{
    QByteArray b = l;
    b >> t.m_fileno >> t.m_dno;
}

void QQTCloudProtocol::parseUploadFileSuccessData(QTCloudUploadFileSuccess& t, const QByteArray& l)
{
    QByteArray b = l;
    b >> t.m_fileno;
}


void QQTCloudProtocol::sendListDirectory(QString code)
{
    QTCloudListDir t;
    t.m_code = code;
    quint16 _tcpcmd = _TCPCMD_SEARCHDIR;
    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_tcpcmd);
    QByteArray d;
    packListDirData(d, t);
    qMsg.setData(d);
    qMsg.translate();
    //pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);
}

void QQTCloudProtocol::sendAddDirectory()
{
    QTCloudAddDir t;
    t.m_upcode = "";
    t.m_code = "";
    t.m_name = "Method2";
    quint16 _tcpcmd = _TCPCMD_ADDDIR;
    QByteArray d;
    packAddDirData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendModDirectory()
{
    QTCloudModDirName t;
    t.m_upcode = "";
    t.m_code = "";
    t.m_name = "Method2";
    quint16 _tcpcmd = _TCPCMD_ALTERDIR;

    QByteArray d;
    //(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendDelDirectory()
{
    QTCloudDelDir t;
    t.m_upcode = "";
    t.m_code = "";
    t.m_name = "Method2";
    quint16 _tcpcmd = _TCPCMD_DELETEDIR;
    QByteArray d;
    //(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::recvAddDirResultMessage(QQTNetworkMessage&) {}

void QQTCloudProtocol::recvDelDirResultMessage(QQTNetworkMessage&) {}

void QQTCloudProtocol::recvModDirResultMessage(QQTNetworkMessage&) {}

void QQTCloudProtocol::sendListFiles(QString code)
{
    QTCloudListFile t;
    t.m_code = code;
    quint16 _tcpcmd = _TCPCMD_SEARCHFILE;
    QByteArray d;
    packListDirData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendDelFile(QString code, QString id)
{
    QTCloudDelFile t;
    t.m_code = code;
    t.m_id = id;
    quint16 _tcpcmd = _TCPCMD_DELETEFILE;
    QByteArray d;
    packDelFileData(d, t);
    sendMessage(_tcpcmd, d);
    pline() << t.m_code << t.m_id;
}

void QQTCloudProtocol::sendListPubDirectory()
{
    QTCloudListPubDir t;
    t.m_code = "";
    quint16 _tcpcmd = _TCPCMD_SEARCHPUBLICDIR;
    QByteArray d;
    packListDirData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendListPubFiles()
{
    QTCloudListPubFile t;
    t.m_code = "";
    quint16 _tcpcmd = _TCPCMD_SEARCHPUBLICFILE;
    QByteArray d;
    packListDirData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendDownDevFiles(const QString& id, const QString& localfile)
{
    m_downfileresult.m_localfile = localfile;
    m_work = 1;
    QTCloudDownDevFile t;
    t.m_id = id;
    quint16 _tcpcmd = _TCPCMD_DOWNLOADFILE;
    QByteArray d;
    packDownDevFileData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendDownPubFiles()
{
    QTCloudDownPubFile t;
    _QTCloudListFileResult _result;
    foreach (_result, m_pubfiles.m_file)
    {
        break;
    }
    t.m_id = _result.m_id;
    quint16 _tcpcmd = _TCPCMD_DOWNLOADPUBFILE;
    QByteArray d;
    packDownDevFileData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendDownFileData()
{
    pline() << m_downfiledata.m_fileno << m_downfiledata.m_dno;
    quint16 _tcpcmd = _TCPCMD_COMFIREFILEINFO;
    QByteArray d;
    packDownDevFileDataData(d, m_downfiledata);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendCancelDown()
{
    QTCloudCancelDownFile t;
    t.m_fileno = m_downfiledata.m_fileno;
    quint16 _tcpcmd = _TCPCMD_CANCELREVFILE;
    m_work = 0;
    emit signalCancelDown();;
    QByteArray d;
    packDownDevFileSuccessData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendDownFileSuccess()
{
    QTCloudDownFileSuccess t;
    t.m_fileno = m_downfiledata.m_fileno;
    quint16 _tcpcmd = _TCPCMD_DOWNFILEOK;
    QByteArray d;
    packDownDevFileSuccessData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::sendUploadFile(const QString& code, const QString& cloudname, const QString& localfile)
{
    m_uploadfile.m_code = code;
    m_uploadfile.m_name = cloudname;
    m_uploadfile.m_localfile = localfile;
    QFileInfo f(m_uploadfile.m_localfile);
    m_uploadfile.m_length = QString::number(f.size());
    m_uploadfile.m_overwrite = _TCP_RESULT_TRUE;
    quint16 _tcpcmd = _TCPCMD_SENDFILEINFO;
    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_tcpcmd);
    QByteArray d;
    packUploadFileData(d, m_uploadfile);
    qMsg.setData(d);
    qMsg.translate();
    //pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);
    //waitForBytesWritten(-1);
}

void QQTCloudProtocol::sendUploadFileData()
{
    m_uploadfiledata.m_addr = m_uploadfiledata.m_dno * _TCP_BLOCKDATA_SIZE;
    QFile f(m_uploadfile.m_localfile);
    f.open(QIODevice::ReadOnly);
    if (f.isOpen())
    {
        f.seek(m_uploadfiledata.m_addr);
        m_uploadfiledata.m_data = f.read(_TCP_BLOCKDATA_SIZE);
    }
    f.close();
    m_uploadfiledata.m_dlen = m_uploadfiledata.m_data.length();
    quint16 _tcpcmd = _TCPCMD_SENDFILEDATA;
    QQTNetworkMessage qMsg;
    qMsg.setUid(m_UID);
    qMsg.setCmd(_tcpcmd);
    QByteArray d;
    packUploadFileDataData(d, m_uploadfiledata);
    qMsg.setData(d);
    qMsg.translate();
    pline() << qMsg;
    QByteArray b;
    qMsg.packer(b);
    write(b);

    pline() << m_uploadfile.m_name << m_uploadfile.m_localfile << m_uploadfiledata.m_fileno << m_uploadfiledata.m_dno << m_uploadfiledata.m_addr << m_uploadfiledata.m_dlen;
}

void QQTCloudProtocol::sendCancelUpload()
{
    QTCloudCancelUploadFile t;
    t.m_fileno = m_uploadfiledata.m_fileno;
    quint16 _tcpcmd = _TCPCMD_CANCELSENDFILE;
    QByteArray d;
    packDownDevFileSuccessData(d, t);
    sendMessage(_tcpcmd, d);
    emit signalCancelUpload();
}

void QQTCloudProtocol::sendDownUpgradeFile(const QString& id, const QString& localfile)
{
    m_downfileresult.m_localfile = localfile;
    m_work = 1;
    QTCloudDownDevFile t;
    t.m_id = id;
    quint16 _tcpcmd = _TCPCMD_DOWNUPGRADEFILE;
    QByteArray d;
    packDownDevFileData(d, t);
    sendMessage(_tcpcmd, d);
}

void QQTCloudProtocol::recvListDirResultMessage(QQTNetworkMessage& qMsg)
{
    m_dirs.m_upcode = "";
    m_dirs.m_dir.clear();
    parseListDirResultData(m_dirs, qMsg.data());
    pline() << m_dirs.m_upcode;
    _QTCloudListDirResult _result;
    foreach (_result, m_dirs.m_dir)
    {
        /*
         * 这里保存到model中
         */
        pline() << _result.m_id << _result.m_code << _result.m_name;
    }
    emit signalListDirOK();
}

void QQTCloudProtocol::recvListFilesResultMessage(QQTNetworkMessage& qMsg)
{
    m_files.m_code = "";
    m_files.m_file.clear();
    parseListFileResultData(m_files, qMsg.data());
    pline() << m_files.m_code;
    _QTCloudListFileResult _result;
    foreach (_result, m_files.m_file)
    {
        /*
         * 这里保存到model中
         */
        pline() << _result.m_id << _result.m_name << _result.m_size << _result.m_date;
    }
    emit signalListFileOK();
}

void QQTCloudProtocol::recvListPubDirResultMessage(QQTNetworkMessage& qMsg)
{
    m_pubdirs.m_upcode = "";
    m_pubdirs.m_dir.clear();
    parseListDirResultData(m_pubdirs, qMsg.data());
    pline() << m_pubdirs.m_upcode;
    _QTCloudListDirResult _result;
    foreach (_result, m_pubdirs.m_dir)
    {
        /*
         * 这里保存到model中
         */
        pline() << _result.m_id << _result.m_code << _result.m_name;
    }
}

void QQTCloudProtocol::recvListPubFilesResultMessage(QQTNetworkMessage& qMsg)
{
    m_pubfiles.m_code = "";
    m_pubfiles.m_file.clear();
    parseListFileResultData(m_pubfiles, qMsg.data());
    pline() << m_pubfiles.m_code;
    _QTCloudListFileResult _result;
    foreach (_result, m_pubfiles.m_file)
    {
        /*
         * 这里保存到model中
         */
        pline() << _result.m_id << _result.m_name << _result.m_size << _result.m_date;
    }
}

void QQTCloudProtocol::recvDownFileResultMessage(QQTNetworkMessage& qMsg)
{
    parseDownDevFileResultData(m_downfileresult, qMsg.data());
    pline() << m_downfileresult.m_fileno << m_downfileresult.m_name << m_downfileresult.m_length;
    m_downfiledata.m_fileno = m_downfileresult.m_fileno.toInt();

    QString tmpFile = m_downfileresult.m_localfile;

#ifdef __EMBEDDED_LINUX__
    system(QString("touch %1").arg(tmpFile).toLatin1().data());
#endif

    QFile f(tmpFile);
    f.open(QIODevice::WriteOnly | QIODevice::Truncate);
    pline() << tmpFile << f.size();
    f.close();
    emit signalUpdateProgress(0);
    emit signalDownData();
}

void QQTCloudProtocol::recvDownFileDataResultMessage(QQTNetworkMessage& qMsg)
{
    if (0 == m_work)
        return;
    QTCloudDownFileDataResult result;
    parseDownDevFileDataResultData(result, qMsg.data());
    pline() << result.m_fileno << result.m_dno << result.m_addr <<
            result.m_dlen;// << m_downfiledata.m_data;
    int nFileSize = 0;
    QString tmpFile = m_downfileresult.m_localfile;
    QFile f(tmpFile);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(result.m_data);
    nFileSize = f.size();
    f.close();
    pline() << nFileSize << m_downfileresult.m_length;
    int percent = 0;
    if (nFileSize > 0)
        percent = 100 * nFileSize / m_downfileresult.m_length.toInt();
    emit signalUpdateProgress(percent);
    pline() << percent;
    if (nFileSize < m_downfileresult.m_length.toInt())
    {
        m_downfiledata.m_dno++;
        emit signalDownData();
    }
    else
    {
        m_downfiledata.m_dno = 0;
        emit signalDownSucc();
    }
}

void QQTCloudProtocol::recvUploadFileResult(QQTNetworkMessage& qMsg)
{
    QTCloudUploadFileResult result;
    parseUploadFileResultData(result, qMsg.data());
    pline() << result.m_fileno << result.m_state;
    perr(result.m_state, 0x00) << "ok to send file data";
    perr(result.m_state, 0x01) << "unsupport file type";
    perr(result.m_state, 0x02) << "file too length";
    perr(result.m_state, 0x03) << "too much file";
    perr(result.m_state, 0x04) << "files too long";
    perr(result.m_state, 0x14) << "no much storage";

    if (result.m_state == 0x00)
    {
        m_uploadfiledata.m_fileno = result.m_fileno;
        m_uploadfiledata.m_dno = 0;
        /*
         * 使用Timer确认不是网络速率的原因。
         */
        emit signalUpdateProgress(0);
        emit signalSendData();
    }
}

void QQTCloudProtocol::recvUploadFileDataResult(QQTNetworkMessage& qMsg)
{
    QTCloudUploadFileDataResult result;

    parseUploadFileDataResultData(result, qMsg.data());
    pline() << result.m_fileno << result.m_dno << result.m_dno* _TCP_BLOCKDATA_SIZE << m_uploadfile.m_length.toInt();

    /*
     * 不需要发空串
     */
    m_uploadfiledata.m_dno = result.m_dno + 1;
    int percent = 0;
    if (m_uploadfile.m_length.toInt() > 0)
        percent = 100 * m_uploadfiledata.m_dno * _TCP_BLOCKDATA_SIZE /
                  m_uploadfile.m_length.toInt();

    if (m_uploadfiledata.m_dno * _TCP_BLOCKDATA_SIZE < m_uploadfile.m_length.toInt())
    {
        emit signalSendData();
        emit signalUpdateProgress(percent);
    }
}

void QQTCloudProtocol::recvUploadFileSuccess(QQTNetworkMessage& qMsg)
{
    QTCloudUploadFileSuccess result;
    parseUploadFileSuccessData(result, qMsg.data());
    pline() << result.m_fileno << m_uploadfiledata.m_dno << m_uploadfiledata.m_dno* _TCP_BLOCKDATA_SIZE << m_uploadfile.m_length.toInt() << "upload success";
    emit signalUpdateProgress(100);
    emit signalUploadSucc();
}

void QQTCloudProtocol::packLoginData(QByteArray& l, const QTCloudLogin& t)
{
    l = QString(_TCPCMD_DATALOGIN).arg(t.m_name).arg(t.m_password).toLatin1();
}

void QQTCloudProtocol::parseLoginResultData(QTCloudLoginResult& t, const QByteArray& l)
{
    QByteArray _l = l;
    _l >> t.m_result;
}


QByteArray& QQTCloudProtocol::packKeyWordToByteArray(QByteArray& array, const QString& key, const QString& value)
{
    return array << key.toLatin1() << "=\"" << value.toLatin1() << "\"";
}

QByteArray QQTCloudProtocol::parseKeyWordInByteArray(const QByteArray& array, const QByteArray& section, quint32& pos)
{
    int index = pos, indexTemp = 0;

    index = array.indexOf(section, index);
    index = array.indexOf('\"', index);
    indexTemp = array.indexOf('\"', index + 1);
    pos = indexTemp + 1;
    return array.mid(index + 1, (indexTemp - index - 1));
}

quint16 QQTCloudProtocol::splitter(const QByteArray& s)
{
    QByteArray l = s.left(4);
    quint16 b0 = 0, b1 = 0;
    l >> b0 >> b1;
    return b1;
}

quint16 QQTCloudProtocol::minlength()
{
    return 16;
}

quint16 QQTCloudProtocol::maxlength()
{
    return 32768;
}
