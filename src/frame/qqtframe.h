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
#include <QDir>
#include <qqt-local.h>
#include <qqtsql.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum
{
    Lib_Id = 0,
    Lib_Name,
    Lib_Creater,
    Lib_CreateTime,
    Lib_Comment,
};

enum
{
    Method_Id = 0,
    Method_Name,
    Method_Type,
    Method_Vessel,
};

enum
{
    Stage_Id = 0,
    Stage_Index,
    Stage_Vessel,
    Stage_Timeramp,
    Stage_Presspsi,
    Stage_Tempture,
    Stage_Hold,
    Stage_MethodId,
};

enum
{
    Type_Standard = 0,
    Type_Temprature,
    Type_Stressure,
    Type_Extract,
};

enum
{
    Login_Request,
    Login_Success,
};


enum
{
    Event_TypeId,
    Event_TypeName,
};


typedef enum tagSampleEnum
{
    ESampleId,
    ESampleMingcheng,
    ESampleBianhao,
    ESampleYangpinliang,
    ESampleYangpindanwei,
    ESampleJieguo,
    ESampleJieguodanwei,
    ESampleCeshiren,
    ESampleCeshishijian,
} ESampleColomn;

enum
{
    Language_English,
    Language_Chinese,
};

enum
{
    FILE_NAME,
    FILE_SIZE,
    FILE_TYPE,
    FILE_DATE,
    FILE_ID,
    FILE_PATH,
    FILE_FILEPATH,

    FILE_MAX,
};

enum
{
    DIR_NAME,
    DIR_CODE,
    DIR_PATH,
    DIR_MAX,
};


#define CONFIG_PATH "./conf"
#define LOG_PATH "./log"
#define AV_PATH "./res"
#define SKIN_PATH "./skin"

#if defined (__ANDROIDX86__)
#define res(file) QString("%1/%2").arg("assets:/res").arg(file)
#define skin(file) QString("%1/%2").arg("assets:/skin").arg(file)
#elif defined (__ANDROID__)
#define res(file) QString("%1/%2").arg("://res").arg(file)
#define skin(file) QString("%1/%2").arg("://skin").arg(file)
#else
#define res(file) QDir().relativeFilePath(QString("./res/%1").arg(file))
#define skin(file) QDir().relativeFilePath(QString("./skin/%1").arg(file))
#endif


#define TABLE_LIBRARY "Library"
#define TABLE_METHOD "Method"
#define TABLE_STAGE "Stage"
#define TABLE_EVTYPE "Type"

extern QString gUserName;
extern QString gPassword;
extern int gAuthority;


#ifdef __cplusplus
}
#endif  /* __cplusplus */

void QQt4FrameMsgHandler ( QtMsgType type, const char* msg );
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
void QQt5FrameMsgHandler ( QtMsgType type, const QMessageLogContext& context, const QString& content );
#endif

/*当前登陆用户 是否具有 函数要求的权限*/
bool hasAuthority ( int authId = Auth_Admin );

#endif // QQTFRAMEDEFINE_H
