#ifndef QQTCORE_H
#define QQTCORE_H

#include "qglobal.h"
#include "qqt-qt.h"
#include <qqt-local.h>

#ifndef __MSVC_UTF8_SUPPORT__
//在源码里有这个定义以外，还要求源文件为utf-8格式
//加在qqt_header.pri里面了，就一下子充分解决了。
//这个定义和CCFLAGS是冲突的，不能并存，只能定义一边。一般选择CCFLAGS。
#ifdef Q_OS_WIN
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#endif
#endif

#if defined(__WIN__)
#include "qqtwin.h"
#elif defined (__ANDROID__)
#include "qqtandroid.h"
#elif defined(__LINUX__)
#include "qqtlinux.h"
#elif defined (__DARWIN__)
#include "qqtdarwin.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__WIN__)
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2
#else
typedef bool BOOL;
#endif

typedef int     s32;
typedef unsigned int   u32;
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef short           s16;
typedef char            s8;
typedef long int        s64;
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


#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#ifndef qintptr
#define qintptr int
#endif
#endif

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

#define MAX_LEN 1024

#ifdef __cplusplus
}
#endif  /* __cplusplus */

//此处加const已经经过测试，不可修改！
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, quint8 r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, quint16 r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, quint32 r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, quint64 r );

QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, qint8 r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, qint16 r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, qint32 r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, qint64 r );

QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, quint8& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, quint16& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, quint32& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, quint64& r );

QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, qint8& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, qint16& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, qint32& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, qint64& r );

QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const QByteArray& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, QByteArray& r );

QQTSHARED_EXPORT bool operator< (  QByteArray& l,  QByteArray& r );
QQTSHARED_EXPORT bool operator== (  QByteArray& l,  QByteArray& r );

//调试模块用的太多了，放在core里。
#include <qqtdebug.h>

#endif // QQTCORE_H
