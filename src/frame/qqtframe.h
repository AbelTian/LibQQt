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


#define CONFIG_ROOT     QCoreApplication::applicationDirPath()
#define CONFIG_PATH     QString("conf")
#define LOG_PATH        QString("log")
#define AV_PATH         QString("res")
#define SKIN_PATH       QString("skin")
#define FONT_PATH       QString("font")
#define DB_PATH         QString("db")
#define LANG_PATH       QString("lang")
#define CACHE_PATH      QString("cache")

#if defined (__ANDROIDX86__)
#define conf_root(file)  QString("assets:/%1%2").arg("").arg(file)
#define conf_res(file)   QString("assets:/%1/%2").arg("res").arg(file)
#define conf_skin(file)  QString("assets:/%1/%2").arg("skin").arg(file)
#define conf_font(file)  QString("assets:/%1/%2").arg("font").arg(file)
#define conf_db(file)    QString("assets:/%1/%2").arg("db").arg(file)
#define conf_lang(file)  QString("assets:/%1/%2").arg("lang").arg(file)
#define conf_conf(file)  QString("assets:/%1/%2").arg("conf").arg(file)
#define conf_log(file)   QString("assets:/%1/%2").arg("log").arg(file)
#define conf_cache(file) QString("assets:/%1/%2").arg("cache").arg(file)
#elif defined (__ANDROID__)
#define conf_root(file)  QString("://%1%2").arg("").arg(file)
#define conf_res(file)   QString("://%1/%2").arg("res").arg(file)
#define conf_skin(file)  QString("://%1/%2").arg("skin").arg(file)
#define conf_font(file)  QString("://%1/%2").arg("font").arg(file)
#define conf_db(file)    QString("://%1/%2").arg("db").arg(file)
#define conf_lang(file)  QString("://%1/%2").arg("lang").arg(file)
#define conf_conf(file)  QString("://%1/%2").arg("conf").arg(file)
#define conf_log(file)   QString("://%1/%2").arg("log").arg(file)
#define conf_cache(file) QString("://%1/%2").arg("cache").arg(file)
#else
#define conf_root(file)  QDir(CONFIG_ROOT).absoluteFilePath(QString("%1%2").arg("").arg(file))
#define conf_res(file)   QDir(CONFIG_ROOT).absoluteFilePath(QString("%1/%2").arg(AV_PATH).arg(file))
#define conf_skin(file)  QDir(CONFIG_ROOT).absoluteFilePath(QString("%1/%2").arg(SKIN_PATH).arg(file))
#define conf_font(file)  QDir(CONFIG_ROOT).absoluteFilePath(QString("%1/%2").arg(FONT_PATH).arg(file))
#define conf_db(file)    QDir(CONFIG_ROOT).absoluteFilePath(QString("%1/%2").arg(DB_PATH).arg(file))
#define conf_lang(file)  QDir(CONFIG_ROOT).absoluteFilePath(QString("%1/%2").arg(LANG_PATH).arg(file))
#define conf_conf(file)  QDir(CONFIG_ROOT).absoluteFilePath(QString("%1/%2").arg(CONFIG_PATH).arg(file))
#define conf_log(file)   QDir(CONFIG_ROOT).absoluteFilePath(QString("%1/%2").arg(LOG_PATH).arg(file))
#define conf_cache(file) QDir(CONFIG_ROOT).absoluteFilePath(QString("%1/%2").arg(CACHE_PATH).arg(file))
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
