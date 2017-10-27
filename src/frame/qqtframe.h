#ifndef QQTFRAMEDEFINE_H
#define QQTFRAMEDEFINE_H


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


#define CONFIG_PATH "./conf/"
#define LOG_PATH "./log/"
#define DB_METHOD_PATH "Method/"
#define DB_DATA_PATH "Data/"
#define AV_PATH "./res"
#define DB_PINYIN "PinYin.db"
#define DB_MANAGER "Manager.db"
#define DB_QQT "System.db"
#define DB_USER "User.db"
#define DB_EXTRACT "Extract.db"
#define DB_REPORT_P "Data/Method_Time.db"
#define DB_EVENT "SysEvent.db"
#define DB_DATA "SampleResult.db"
#define TABLE_USERINFO "User"
#define TABLE_AUTHORITY "Authority"
#define TABLE_LIBRARY "Library"
#define TABLE_METHOD "Method"
#define TABLE_STAGE "Stage"
#define TABLE_EVENT "Event"
#define TABLE_EVTYPE "Type"
#define TABLE_YANGPINDATA "data"

extern QSqlDatabase managerDB;
extern QString gUserName;
extern QString gPassword;


#ifdef __cplusplus
}
#endif  /* __cplusplus */

void qqtFrameMsgHandler(QtMsgType type, const char * msg);


#endif // QQTFRAMEDEFINE_H