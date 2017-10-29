#ifndef QQTCLOUDPROTOCOL_H
#define QQTCLOUDPROTOCOL_H

#include <QTimer>
#include "qqtprotocol.h"
#include "qqtnetworkmessage.h"
#include "qqtclient.h"

#define _TCPCMD_HEART                     0x0010
#define _TCPCMD_HEARTBEATRESP             0x8010

#define _TCPCMD_REGISTER                  0x0101
#define _TCPCMD_REGISTERRESUALT           0x8101

#define _TCPCMD_VERIFYCODE                0x0105
#define _TCPCMD_RECEIVEVERIFYBMP          0x8105

#define _TCPCMD_EXIT                      0x0104
#define _TCPCMD_NEXTAREA                  0x1010
#define _TCPCMD_NEXTMACHINE               0x1011

#define _TCPCMD_LOGIN                     0x0102
#define _TCPCMD_LOGINRESUALT              0x8102


#define _TCPCMD_RECEIVEDIRYES             0x4f4b
#define _TCPCMD_RECEIVEDIRNO

#define _TCPCMD_SEARCHDIR                 0x0200
#define _TCPCMD_ADDDIR                    0x0201
#define _TCPCMD_ALTERDIR                  0x0202
#define _TCPCMD_DELETEDIR                 0x0203
#define _TCPCMD_SEARCHFILE                0x0204
#define _TCPCMD_DELETEFILE                0x0205
#define _TCPCMD_SEARCHPUBLICDIR           0x0210
#define _TCPCMD_SEARCHPUBLICFILE          0x0211

#define _TCPCMD_SENDFILEINFO              0x0321
#define _TCPCMD_SENDFILEDATA              0x0322
#define _TCPCMD_CANCELSENDFILE            0x0323

#define _TCPCMD_DOWNLOADFILE              0x0303
#define _TCPCMD_DOWNLOADPUBFILE           0x0304
#define _TCPCMD_COMFIREFILEINFO           0x0311
#define _TCPCMD_CANCELREVFILE             0x0312
#define _TCPCMD_DOWNFILEOK                0x0313

#define _TCPCMD_RECEIVEDIRLIST            0x8200
#define _TCPCMD_RECEIVEADDRESUALT         0x8201
#define _TCPCMD_RECEIVEALTERRESUALT       0x8202
#define _TCPCMD_RECEIVEDELETERESUALT      0x8203
#define _TCPCMD_RECEIVEFILELIST           0x8204
#define _TCPCMD_RECEIVEPUBLICDIRLIST      0x8210
#define _TCPCMD_RECEIVEPUBLICFILELIST     0x8211

#define _TCPCMD_RECEIVEFILEINFO           0x8311
#define _TCPCMD_RECEIVEFILEDATA           0x8312
#define _TCPCMD_RECEIVECOMFIREFILEINFO    0x8321
#define _TCPCMD_RECEIVECOMFIREFILEDATA    0x8322
#define _TCPCMD_RECEIVECOMFIREFILE        0x8323


#define _TCPCMD_CHECKVERSION              0x0400
#define _TCPCMD_CHECKVERSIONRSP           0x8400

#define _TCPCMD_DOWNUPGRADEFILE           0x0411

#define _TCP_SECTION_SOFTWAREID                     "SOFTWAREID"
#define _TCP_SECTION_DEVICECODE                     "INSTRUMENTCODE"
#define _TCP_SECTION_SOFTWARECODE                     "SOFTWARECODE"
#define _TCP_SECTION_VERSION                     "VERSION"
#define _TCP_SECTION_NEWSOFTWAREID                     "NEWSOFTWAREID"
#define _TCP_SECTION_EXPLAIN                     "EXPLAIN"
#define _TCP_SECTION_RELEASESTAT                     "RELEASESTATUS"
#define _TCP_SECTION_RELEASEDATE                     "RELEASEDATE"
#define _TCP_SECTION_FILENAME                     "FILENAME"
#define _TCP_SECTION_FILEMD5                     "FILEMD5"
#define _TCP_SECTION_FILESIZE                     "FILESIZE"

#define _TCP_SECTION_UPCODE                    "UPCODE"
#define _TCP_SECTION_ID                        "ID"
#define _TCP_SECTION_CODE                      "CODE"
#define _TCP_SECTION_NAME                      "NAME"
#define _TCP_SECTION_SIZE                      "SIZE"
#define _TCP_SECTION_DATE                      "DATE"
#define _TCP_SECTION_FILENO                    "FILENO"
#define _TCP_SECTION_LENGTH                    "LENGTH"
#define _TCP_SECTION_RESULE                     "RESULT"

#define _TCP_RESULT_OK                          "OK"
#define _TCP_RESULT_FAIL                        "FF"
#define _TCP_RESULT_TRUE                        "TRUE"
#define _TCP_RESULT_FALSE                       "FALSE"

#define _TCP_SECTION_USERNAME                  "USERNAME"
#define _TCP_SECTION_PASSWORD                  "PASSWORD"

typedef struct tagTankLogin
{
    QString m_name;
    QString m_password;
}QTCloudLogin;

typedef struct tagTankLoginReuslt
{
    quint8 m_result;
}QTCloudLoginResult;

typedef struct tagQTCloudListDir
{
    QString m_code;
}QTCloudListDir, QTCloudListFile, QTCloudListPubDir, QTCloudListPubFile;

typedef struct tag_QTCloudListDirResult
{
    QString m_id;
    QString m_code;
    QString m_name;
}_QTCloudListDirResult;

typedef struct tagQTCloudListDirResult
{
    QList<_QTCloudListDirResult> m_dir;
    QString m_upcode;
}QTCloudListDirResult, QTCloudListPubDirResult;

typedef struct tagTankAddDir
{
    QString m_upcode;
    QString m_code;
    QString m_name;
}QTCloudAddDir, QTCloudModDirName, QTCloudDelDir;

typedef struct tagQTCloudDelFile
{
    QString m_code;
    QString m_id;
}QTCloudDelFile;

typedef struct tagQTCloudAddDirResult
{
    QString m_upcode;
    QString m_result;
}QTCloudAddDirResult, QTCloudDelDirResult, QTCloudModDirNameResult;

typedef struct tag_QTCloudListFileResult
{
    QString m_id;
    QString m_name;
    QString m_size;
    QString m_date;
}_QTCloudListFileResult;

typedef struct tagQTCloudListFileResult
{
    QList<_QTCloudListFileResult> m_file;
    QString m_code;
}QTCloudListFileResult, QTCloudListPubFileResult;

typedef struct tagTankDownDevFile
{
    QString m_id;
}QTCloudDownDevFile, QTCloudDownPubFile;

typedef struct tagQTCloudDownFileData
{
    tagQTCloudDownFileData()
    {
        m_fileno = 0;
        m_dno = 0;
    }

    quint32 m_fileno;
    quint32 m_dno;
}QTCloudDownFileData, QTCloudUploadFileDataResult;

typedef struct tagQTCloudCancelDownFile
{
    quint32 m_fileno;
}QTCloudCancelDownFile, QTCloudDownFileSuccess, QTCloudCancelUploadFile, QTCloudUploadFileSuccess;

typedef struct tagQTCloudDownFileResult
{
    QString m_fileno;
    QString m_name;
    QString m_length;
    //local
    QString m_localfile;
}QTCloudDownDevFileResult, QTCloudDownPubFileResult;

typedef struct tagQTCloudDownFileDataResult
{
    tagQTCloudDownFileDataResult()
    {
        m_fileno = 0;
        m_dno = 0;
        m_addr = 0;
        m_dlen = 0;
        m_data.clear();
    }

    quint32 m_fileno;
    quint32 m_dno;
    quint32 m_addr;
    quint16 m_dlen;
    QByteArray m_data;
}QTCloudDownFileDataResult, QTCloudUploadFileData;

typedef struct tagTankUploadFile
{
    QString m_code;
    QString m_name;
    QString m_overwrite;
    QString m_length;
    //local
    QString m_localfile;
}QTCloudUploadFile;

typedef struct tagTankUploadFileResult
{
    tagTankUploadFileResult()
    {
        m_fileno = 0;
        m_state = 0;
    }

    quint32 m_fileno;
    quint8 m_state;
}QTCloudUploadFileResult;


typedef struct tagQTCheckVersion
{
    QString m_softwareid;
    QString m_devicecode;
    QString m_softwarecode;
    QString m_version;
}QTCheckVersion;

typedef struct tagQTCheckVersionResult
{
    QString m_softwareid;
    QString m_devicecode;
    QString m_softwarecode;
    QString m_version;
    QString m_NewSoftwareID;
    QString m_Explain;
    QString m_ReleaseStatus;
    QString m_ReleaseDate;
    QString m_FileName;
    QString m_FileMD5;
    QString m_FileSize;
}QTCheckVersionResult;


#define _TCPCMD_DATALOGIN                "USERNAME=\"%1\"PASSWORD=\"%2\""
#define _TCPCMD_DATAADDDIR               "UPCODE=\"%1\"CODE=\"%2\"NAME=\"%3\""
#define _TCPCMD_DATAALTERDIR             "UPCODE=\"%1\"ID=\"%2\"NAME=\"%3\""
#define _TCPCMD_DATADELETEDIR            "UPCODE=\"%1\"ID=\"%2\""
#define _TCPCMD_DATADELETEFILE           "CODE=\"%1\"ID=\"%2\""
#define _TCPCMD_DATASENDFILEINFO         "CODE=\"%1\"NAME=\"%2\"OVERWRITE=\"%3\"LENGTH=\"%4\""
#define MAX_HEARDBEAT 10

class QQTCloudProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQTCloudProtocol(QObject *parent = 0);

    QTCheckVersionResult& GetVersionResult();
    QTCloudListDirResult& GetDirList();
    QTCloudListFileResult& GetListedFiles();
    bool isLogined();
    void startHeartBeat();
    void stopHeartBeat();

signals:
    void signalLoginSucc();//
    void signalLoginFail();
    void signalLogoutSucc();
    void signalLogoutFail();//?
    void signalReconnectQequest();//app do client.connect.
    void signalCancelDown();
    void signalDownSucc();
    void signalListDirOK();
    void signalListFileOK();
    void signalUpdateProgress(int percent);

    void signalCancelUpload();
    void signalUploadSucc();

signals:
    void signalSendData();
    void signalDownData();
    void signalCheckVersionResult();
protected:
    quint8 m_work;
private:
    QTCheckVersionResult m_versionresult;
    QTCloudUploadFile m_uploadfile;
    QTCloudUploadFileData m_uploadfiledata;
    QTCloudListDirResult m_dirs;
    QTCloudListFileResult m_files;
    QTCloudListPubDirResult m_pubdirs;
    QTCloudListPubFileResult m_pubfiles;
    QTCloudDownDevFileResult m_downfileresult;
    QTCloudDownFileData m_downfiledata;
private:
    quint32 m_UID;
    qint8 m_heartCount;
    QTimer* timer;
    bool m_isLogined;

signals:


public slots:
    /*
     * 服务器需要解析收到的命令，而此处不需要，所以客户端和服务器代码分开编写。
     */
    void sendHeatBeatMessage();
    void recvHeatBeatResultMessage(QQTNetworkMessage&);

    /*
     * 和PC的协议中，不登陆不能进行任何操作，所以此处登陆；
     */
    void sendLoginMessage();
    void recvLoginResultMessage(QQTNetworkMessage&);

    void sendLogoutMessage();
    void recvConnPoolFullMessage(QQTNetworkMessage&);

    void sendCheckVersion();
    void sendCheckNewVersion();
    void recvCheckVersionResult(QQTNetworkMessage &);

    void sendListDirectory(QString code = "");
    void recvListDirResultMessage(QQTNetworkMessage&);

    void sendAddDirectory();
    void sendModDirectory();
    void sendDelDirectory();
    void recvAddDirResultMessage(QQTNetworkMessage&);
    void recvDelDirResultMessage(QQTNetworkMessage&);
    void recvModDirResultMessage(QQTNetworkMessage&);

    void sendListFiles(QString code = "001");
    void sendListPubDirectory();
    void sendListPubFiles();
    void recvListFilesResultMessage(QQTNetworkMessage&);
    void recvListPubDirResultMessage(QQTNetworkMessage&);
    void recvListPubFilesResultMessage(QQTNetworkMessage&);

    void sendDelFile(QString code, QString id);
    void sendDownUpgradeFile(const QString& id, const QString& localfile);
    /**
     * @brief sendDownDevFiles
     * @param path 文件下载下来保存的路径
     * @param id
     * @param local 文件下载下来保存的名字
     */
    void sendDownDevFiles(const QString& id, const QString& localfile);
    void sendDownPubFiles();
    void sendDownFileData();
    void sendDownFileSuccess();
    void sendCancelDown();

    void recvDownFileResultMessage(QQTNetworkMessage&);
    void recvDownFileDataResultMessage(QQTNetworkMessage&);

    void sendUploadFile(const QString& code, const QString& cloudname, const QString& localfile);
    void sendUploadFileData();
    void sendCancelUpload();
    void recvUploadFileResult(QQTNetworkMessage&);
    void recvUploadFileDataResult(QQTNetworkMessage&);
    void recvUploadFileSuccess(QQTNetworkMessage&);

    void sendMessage(quint16 cmd, QByteArray& data);

protected:
    void packLoginData(QByteArray& l, const QTCloudLogin& t);
    void parseLoginResultData(QTCloudLoginResult& t, const QByteArray& l);

    void packListDirData(QByteArray& l, const QTCloudListDir& t);
    void parseListDirResultData(QTCloudListDirResult& r, const QByteArray& l);

    void packAddDirData(QByteArray& l, const QTCloudAddDir& t);
    void parseAddDirResultData(QTCloudAddDirResult& r, const QByteArray& l);

    void packDelFileData(QByteArray& l, const QTCloudDelFile& t);

    void parseListFileResultData(QTCloudListFileResult& r, const QByteArray& l);

    void packDownDevFileData(QByteArray& l, const QTCloudDownDevFile& t);
    void parseDownDevFileResultData(QTCloudDownDevFileResult& r, const QByteArray& l);

    void packDownDevFileSuccessData(QByteArray& l, const QTCloudDownFileSuccess& t);

    void packDownDevFileDataData(QByteArray& l, const QTCloudDownFileData& t);
    void parseDownDevFileDataResultData(QTCloudDownFileDataResult& r, const QByteArray& l);

    void packUploadFileData(QByteArray& l, const QTCloudUploadFile& t);
    void parseUploadFileResultData(QTCloudUploadFileResult& r, const QByteArray& l);

    void packUploadFileDataData(QByteArray& l, const QTCloudUploadFileData& t);
    void parseUploadFileDataResultData(QTCloudUploadFileDataResult& t, const QByteArray& l);

    void parseUploadFileSuccessData(QTCloudUploadFileSuccess& t, const QByteArray& l);
    void packCheckVersionData(QByteArray& l, const QTCheckVersion& t);
    void parseCheckVersionResultData(QTCheckVersionResult& t, const QByteArray& l);

protected:
    QByteArray& packKeyWordToByteArray(QByteArray &array, const QString &key, const QString& value);

    QByteArray  parseKeyWordInByteArray(const QByteArray& array, const QByteArray &section, quint32 &pos);

    // QQtProtocol interface
public:
    quint16 minlength() override;
    quint16 maxlength() override;
    quint16 splitter(const QByteArray &s) override;
    bool dispatcher(const QByteArray &m) override;

};


QQTClient *QQTUpgradeClientInstance(QObject *parent);


QQTClient *QQTCloudClientInstance(QObject *parent);


#endif // QQTCLOUDPROTOCOL_H
