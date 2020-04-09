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

//使用QQtPushButton直接[]运算，在嵌入式板子上表现不正常，所以使用ImageTable。
struct QQTSHARED_EXPORT TBtnImageTable
{
    TBtnImageTable();

    void setStateImage ( int index, const QString& image );
    void setNormal ( const QString& normal, const QString& press );
    void setCheck ( const QString& uncheck, const QString& check );
    void setOther ( const QString& hover, const QString& disable );
    void setHover ( const QString& hover );
    void setDisable ( const QString& disable );

    void setStateImage ( int index, const QImage& image );
    void setNormal ( const QImage& normal, const QImage& press );
    void setCheck ( const QImage& uncheck, const QImage& check );
    void setOther ( const QImage& hover, const QImage& disable );
    void setHover ( const QImage& hover );
    void setDisable ( const QImage& disable );

    const QImage& operator[] ( int index ) const;
    QImage& operator [] ( int index );

    const QImage& image ( int index ) const;
    QImage& image ( int index );

    //深拷贝
    TBtnImageTable ( const TBtnImageTable& other );
    TBtnImageTable& operator = ( const TBtnImageTable& other );

    QImage mImage[BTN_MAX];
};

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
