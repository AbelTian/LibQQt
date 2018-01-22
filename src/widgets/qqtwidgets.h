#ifndef __QQT_WIDGETS_DEFINE_H__
#define __QQT_WIDGETS_DEFINE_H__

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
#include <qqt-qt.h>
#include "qqt-local.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*
 * 自定义组件的公共部分
 */
typedef enum tagEBtnStatus
{
    BTN_NORMAL = 0,
    BTN_UNCHECK = BTN_NORMAL,
    BTN_PRESS = 1,
    BTN_CHECK = BTN_PRESS,
    BTN_HOVER = 2,
    BTN_DISABLE = 3,
    BTN_MAX,
} EBtnStatus;

#ifdef __cplusplus
}
#endif  /* __cplusplus */

typedef struct QQTSHARED_EXPORT tagBtnIconTable
{
    QString pixmap[BTN_MAX];

    tagBtnIconTable();
    QString pixMap ( int index );
    void setPixMap ( int index, QString pix );
    void initNormal ( QString normal, QString press );
    void initCheck ( QString uncheck, QString check );
    void initOther ( QString hover, QString disable );
    const QString& operator[] ( int index ) const;
    QString& operator [] ( int index );
} TBtnIconTable;


QQTSHARED_EXPORT void moveCenter ( QWidget* w );
QQTSHARED_EXPORT void moveRight ( QWidget* w );
QQTSHARED_EXPORT void moveFull ( QWidget* w );



#endif //__QQT_WIDGETS_DEFINE_H__
