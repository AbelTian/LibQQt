#ifndef __QQT_WIDGETS_DEFINE_H__
#define __QQT_WIDGETS_DEFINE_H__

#include <QWidget>
#include <QImage>
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
    BTN_PRESS = 1,
    BTN_HOVER = 2,

    BTN_UNCHECK = BTN_NORMAL,
    BTN_CHECK = BTN_PRESS,

    BTN_ENABLE = BTN_NORMAL,
    BTN_DISABLE = 4,

    BTN_MAX = 5
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

typedef struct QQTSHARED_EXPORT tagBtnImageTable
{
    QImage mImage[BTN_MAX];

    tagBtnImageTable();

    const QImage& image ( int index ) const;
    QImage& image ( int index );

    void setStateImage ( int index, const QImage& image );

    void setNormal ( const QImage& normal, const QImage& press );
    void setHover ( const QImage& hover );
    void setDisable ( const QImage& disable );

    const QImage& operator[] ( int index ) const;
    QImage& operator [] ( int index );
} TBtnImageTable;

/**
 * 主窗口。针对屏幕
 */
QQTSHARED_EXPORT void moveHCenter ( QWidget* w );
QQTSHARED_EXPORT void moveVCenter ( QWidget* w );
QQTSHARED_EXPORT void moveCenter ( QWidget* w );
QQTSHARED_EXPORT void moveFull ( QWidget* w );
QQTSHARED_EXPORT void moveLeft ( QWidget* w );
QQTSHARED_EXPORT void moveRight ( QWidget* w );
QQTSHARED_EXPORT void moveTop ( QWidget* w );
QQTSHARED_EXPORT void moveBottom ( QWidget* w );

/**
 * 子窗口。针对parent
 * 此处指定的parent控件，必须是w的parent。
 */
QQTSHARED_EXPORT void moveHCenter ( QWidget* w, QWidget* parent );
QQTSHARED_EXPORT void moveVCenter ( QWidget* w, QWidget* parent );
QQTSHARED_EXPORT void moveCenter ( QWidget* w, QWidget* parent );
QQTSHARED_EXPORT void moveFull ( QWidget* w, QWidget* parent );
QQTSHARED_EXPORT void moveLeft ( QWidget* w, QWidget* parent );
QQTSHARED_EXPORT void moveRight ( QWidget* w, QWidget* parent );
QQTSHARED_EXPORT void moveTop ( QWidget* w, QWidget* parent );
QQTSHARED_EXPORT void moveBottom ( QWidget* w, QWidget* parent );


#endif //__QQT_WIDGETS_DEFINE_H__
