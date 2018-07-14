#ifndef QQTCORE_H
#define QQTCORE_H

#include "qglobal.h"
#include "qqt-qt.h"
#include <qqt-local.h>

#ifndef __MSVC_UTF8_SUPPORT__
//在源码里有这个定义以外，还要求源文件为utf-8 with bom格式
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
#elif defined(__LINUX__) || defined(__EMBEDDED_LINUX__)
#include "qqtlinux.h"
#elif defined (__ANDROID__)
#include "qqtandroid.h"
#elif defined (__DARWIN__)  || defined(__IOS__)
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

#define WARNING "Warning"
#define NOTICE "Notice"


QQTSHARED_EXPORT void QQtSleep ( int millsecond );
QQTSHARED_EXPORT void QQtSleepSignal ( int millsecond, const QObject* obj, const char* signal );

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#define pline() qDebug() << __FILE__ << __LINE__/*QString("%1").arg(__LINE__, 3, 10)*/ << __func__
#define ptime() pline() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz")
#define p2line() qDebug() << QString(__FILE__).split('/').last() << QString("%1").arg(__LINE__, 3, 10) << __func__
//-----------------------
#define perr(req, rsl) if(req == rsl) pline() << hex << rsl
#define pmeta(inst) pline() << inst->metaObject()->className()
#define pdebug() qDebug()
#define pdebug_nospace() qDebug().nospace()
#define packline() pline() << qDebug().nospace()

QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const quint8& r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const quint16& r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const quint32& r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const quint64& r );

QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const qint8& r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const qint16& r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const qint32& r );
QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const qint64& r );

QQTSHARED_EXPORT QByteArray& operator<< ( QByteArray& l, const QByteArray& r );

QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, quint8& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, quint16& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, quint32& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, quint64& r );

QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, qint8& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, qint16& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, qint32& r );
QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, qint64& r );

QQTSHARED_EXPORT QByteArray& operator>> ( QByteArray& l, QByteArray& r );


/**
 * @brief The QQtBlock class
 * QMutex，QSemphore，QCondation在gui线程会锁定gui，而我希望在gui线程中堵塞但是不要锁定gui
 * 这个block应用场合为gui线程内部，不适用线程之间
 * 仅仅锁定一次和解锁一次，多次锁定和解锁无用途。
 */
class QQTSHARED_EXPORT QQtBlock : public QObject
{
public:
    explicit QQtBlock ( QObject* parent = 0 ) : QObject ( parent ), m_lock ( 0 ) {}

    //0x7FFFFFFF
    bool lock ( int millsecond = 0x7FFFFFFF ) {
        //m_lock++;
        m_lock = 1;

        timer.restart();

        while ( timer.elapsed() < millsecond ) {
            if ( m_lock <= 0 )
                break;

            QApplication::processEvents();
        }

        if ( timer.elapsed() >= millsecond )
            return false;

        return true;
    }

    void unlock() {
        //m_lock--;
        m_lock = 0;
    }

    bool isLocked() {
        if ( m_lock <= 0 )
            return false;

        return true;
    }

private:
    int m_lock;
    QElapsedTimer timer;
};

#endif // QQTCORE_H
