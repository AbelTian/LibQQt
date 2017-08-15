#ifndef QQTDEFINE_H
#define QQTDEFINE_H

#include <QWidget>
#include <QUuid>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include <QElapsedTimer>
#include <QDesktopWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__WIN__) || defined (__WIN64__)
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2
#else
typedef bool BOOL;
#endif

typedef int		s32;
typedef unsigned int   u32;
typedef unsigned char	u8;
typedef unsigned short  u16;
typedef short           s16;
typedef char            s8;
typedef long int		s64;
typedef unsigned long int u64;
typedef unsigned char uint8_t;

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR   1
#endif

#ifndef SEEK_END
#define SEEK_END   2
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL   0
#endif

#ifndef nullptr
#define nullptr 0
#endif

enum {
    Auth_Id = 0,
    Auth_Name,
    Auth_Passwd,
    Auth_Authrity,
    Auth_Creater,
    Auth_CreateTime,
    Auth_Comment,
};

enum {
    Lib_Id = 0,
    Lib_Name,
    Lib_Creater,
    Lib_CreateTime,
    Lib_Comment,
};

enum {
    Authority_Id = 0,
    Authority_Level,
};

enum {
    Method_Id = 0,
    Method_Name,
    Method_Type,
    Method_Vessel,
};

enum {
    Stage_Id = 0,
    Stage_Index,
    Stage_Vessel,
    Stage_Timeramp,
    Stage_Presspsi,
    Stage_Tempture,
    Stage_Hold,
    Stage_MethodId,
};


enum{
    Type_Standard = 0,
    Type_Temprature,
    Type_Stressure,
    Type_Extract,
};

enum {
    Login_Request,
    Login_Success,
};

enum{
    Language_English,
    Language_Chinese,
};

enum {
    FILE_NAME,
    FILE_SIZE,
    FILE_TYPE,
    FILE_DATE,
    FILE_ID,
    FILE_PATH ,
    FILE_FILEPATH ,

    FILE_MAX,
};

enum {
    DIR_NAME,
    DIR_CODE,
    DIR_PATH,
    DIR_MAX,
};

enum {
    Event_ID,
    Event_Name,
    Event_Time,
    Event_User,
    Event_Content,
};

enum {
    Event_TypeId,
    Event_TypeName,
};


typedef enum tagSampleEnum{
    ESampleId,
    ESampleMingcheng,
    ESampleBianhao,
    ESampleYangpinliang,
    ESampleYangpindanwei,
    ESampleJieguo,
    ESampleJieguodanwei,
    ESampleCeshiren,
    ESampleCeshishijian,
}ESampleColomn;

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

#define MAX_LEN 1024

#define CONFIG_PATH "./conf/"
#define LOG_PATH "./log/"
#define DB_PATH "./db/"
#define DB_METHOD_PATH "Method/"
#define DB_DATA_PATH "Data/"
#define AV_PATH "./res"
#define DB_TYPE "QSQLITE"
#define DB_PINYIN "PinYin"
#define DB_MANAGER "Manager"
#define DB_QQT "System"
#define DB_USER "User"
#define DB_EXTRACT "Extract"
#define DB_REPORT_P "Data/Method_Time.db"
#define DB_EVENT "SysEvent"
#define DB_DATA "SampleResult"
#define TABLE_USERINFO "User"
#define TABLE_AUTHORITY "Authority"
#define TABLE_LIBRARY "Library"
#define TABLE_METHOD "Method"
#define TABLE_STAGE "Stage"
#define TABLE_EVENT "Event"
#define TABLE_EVTYPE "Type"
#define TABLE_YANGPINDATA "data"

#define WARNING "Warning"
#define NOTICE "Notice"

extern QSqlDatabase managerDB;
extern QString gUserName;
extern QString gPassword;


/*
 * 自定义组件的公共部分
 */
enum
{
    BTN_NORMAL = 0,
    BTN_UNCHECK = BTN_NORMAL,
    BTN_PRESS = 1,
    BTN_CHECK = BTN_PRESS,
    BTN_HOVER,
    BTN_DISABLE,
    BTN_MAX,
};

enum {
    ESSID_STATUS = 0,
    ESSID_NAME,//SSID
    ESSID_TYPE,
    ESSID_ENCRYP,
    ESSID_PASS,
    ESSID_BSSID,
    ESSID_FREQ,
    ESSID_SIGNAL,
    ESSID_FLAG,
    ESSID_MAX,
};

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#define pline() qDebug() << __FILE__ << __LINE__ << __func__
#define perr(var, cond) if(var == cond) pline() << hex << cond
#define ptime() pline() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz")

typedef struct tagBtnIconTable
{
    QString pixmap[BTN_MAX];

    tagBtnIconTable();
    QString pixMap(int index);
    void setPixMap(int index, QString pix);
    void initNormal(QString normal, QString press);
    void initCheck(QString uncheck, QString check);
    void initOther(QString hover, QString disable);
    const QString& operator[] (int index) const;
    QString &operator [](int index);
}TBtnIconTable;

typedef struct tagWifi
{
    QString wifi[ESSID_MAX];

    bool isValid();

#ifdef __MIPS_LINUX__
    tagWifi& operator= (tagWifi& w);
#else
    tagWifi &operator=(const tagWifi &w);
#endif

    const QString &operator[] (int index) const;

    QString& operator[] (int index);
}TWifi;


QByteArray &operator<<(QByteArray &l, const quint8 r);

QByteArray &operator<<(QByteArray &l, const quint16 r);

QByteArray &operator<<(QByteArray &l, const quint32 r);

QByteArray &operator<<(QByteArray &l, const QByteArray &r);

QByteArray &operator>>(QByteArray &l, quint8& r);

QByteArray &operator>>(QByteArray &l, quint16& r);

QByteArray &operator>>(QByteArray &l, quint32& r);

QByteArray &operator>>(QByteArray &l, QByteArray& r);

QByteArray &operator<<(QByteArray &l, const qint16 r);

QByteArray &operator<<(QByteArray &l, const qint32 r);

QByteArray &operator>>(QByteArray &l, qint8& r);

QByteArray &operator>>(QByteArray &l, qint16& r);

QByteArray &operator>>(QByteArray &l, qint32& r);

QByteArray &operator>>(QByteArray &l, QByteArray& r);

QSqlDatabase newDatabaseConn();

void setDatabaseName(QSqlDatabase &db, QString dbName);

void openDatabase(QSqlDatabase &db);

void closeDatabase(QSqlDatabase &db);

void moveCenter(QWidget* w);

void moveRight(QWidget* w);

void msgHandler(QtMsgType, const char *);

void QQTSleep(int millsecond);

#endif // QQTDEFINE_H
