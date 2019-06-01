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
    Login_Request,
    Login_Success,
};


enum
{
    Event_TypeId,
    Event_TypeName,
};


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


#define CONFIG_ROOT     QString(".")
#define CONFIG_PATH     QString(CONFIG_ROOT + "/conf")
#define LOG_PATH        QString(CONFIG_ROOT + "/log")
#define AV_PATH         QString(CONFIG_ROOT + "/res")
#define SKIN_PATH       QString(CONFIG_ROOT + "/skin")
#define FONT_PATH       QString(CONFIG_ROOT + "/font")
#define DB_PATH         QString(CONFIG_ROOT + "/db")
#define LANG_PATH       QString(CONFIG_ROOT + "/lang")

#if defined (__ANDROIDX86__)
#define qrc(file)   QString("%1/%2").arg("assets:/").arg(file)
#define res(file)   QString("%1/%2").arg("assets:/res").arg(file)
#define skin(file)  QString("%1/%2").arg("assets:/skin").arg(file)
#define font(file)  QString("%1/%2").arg("assets:/font").arg(file)
#define db(file)    QString("%1/%2").arg("assets:/db").arg(file)
#define lang(file)  QString("%1/%2").arg("assets:/lang").arg(file)
#elif defined (__ANDROID__)
#define qrc(file)   QString("%1/%2").arg("://").arg(file)
#define res(file)   QString("%1/%2").arg("://res").arg(file)
#define skin(file)  QString("%1/%2").arg("://skin").arg(file)
#define font(file)  QString("%1/%2").arg("://font").arg(file)
#define db(file)    QString("%1/%2").arg("://db").arg(file)
#define lang(file)  QString("%1/%2").arg("://lang").arg(file)
#else
#define qrc(file)   QDir().absoluteFilePath(QString("%1/%2").arg(CONFIG_ROOT).arg(file))
#define res(file)   QDir().absoluteFilePath(QString("%1/%2").arg(AV_PATH).arg(file))
#define skin(file)  QDir().absoluteFilePath(QString("%1/%2").arg(SKIN_PATH).arg(file))
#define font(file)  QDir().absoluteFilePath(QString("%1/%2").arg(FONT_PATH).arg(file))
#define db(file)    QDir().absoluteFilePath(QString("%1/%2").arg(DB_PATH).arg(file))
#define lang(file)  QDir().absoluteFilePath(QString("%1/%2").arg(LANG_PATH).arg(file))
#endif

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
