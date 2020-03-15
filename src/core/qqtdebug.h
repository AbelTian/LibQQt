#ifndef QQTDEBUG_H
#define QQTDEBUG_H


#include <qqt-qt.h>
#include <qqt-local.h>

#define pline() qDebug() << __FILE__ << __LINE__ << __func__
#define ptime() pline() << qPrintable( QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz") )
#define p2line() qDebug() << qPrintable( QString(__FILE__).split('/').last() ) << qPrintable ( QString("%1").arg(__LINE__, 3, 10) ) << __func__

//-----------------------
#define perr(req, rsl) if(req == rsl) pline() << hex << rsl
#define pmeta(inst) pline() << inst->metaObject()->className()
#define pdebug() qDebug()
#define pdebug_nospace() qDebug().nospace()
#define packline() pline() << qDebug().nospace()


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define WARNING "Warning"
#define NOTICE "Notice"

QQTSHARED_EXPORT void QQtSleep ( int millsecond );
QQTSHARED_EXPORT void QQtSleepSignal ( int millsecond, const QObject* obj, const char* signal );

#ifdef __cplusplus
}
#endif  /* __cplusplus */


/**
 * @brief The QQtBlock class
 * QMutex，QSemphore，QCondation在gui线程会锁定gui，而我希望在gui线程中堵塞但是不要锁定gui
 * 这个block应用场合为gui线程内部，不适用线程之间
 * 仅仅锁定一次和解锁一次，多次锁定和解锁无用途。
 */
class QQTSHARED_EXPORT QQtBlock : public QObject
{
public:
    explicit QQtBlock ( QObject* parent = 0 );

    //0x7FFFFFFF
    bool lock ( int millsecond = 0x7FFFFFFF );

    void unlock();

    bool isLocked();

private:
    int m_lock;
    QElapsedTimer timer;
};

//在同一个线程里使用。
//给QQtBlock加个信号和槽就好了。不必要这个东西吧。
class QQTSHARED_EXPORT QQtBlockSignal : public QQtBlock
{
    Q_OBJECT
public:
    explicit QQtBlockSignal ( QObject* parent = 0 );

    void addsignal ( const QObject* obj, const char* signal );

public slots:
    void slotSignalComing();

private:
    class QQtSignalObject
    {
    public:
        const QObject* obj;
        const char* signal;

        QQtSignalObject& operator = ( const QQtSignalObject& other ) {
            obj = other.obj;
            signal = other.signal;
            return *this;
        }

        bool operator == ( const QQtSignalObject& other ) {
            if ( obj == other.obj && signal == other.signal )
                return true;
            return false;
        }
    };

private:
    QList<QQtSignalObject> mSignalList;
};

#endif // QQTDEBUG_H

