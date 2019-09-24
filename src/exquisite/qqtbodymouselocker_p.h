#ifndef QQTBODYMOUSELOCKER_P_H
#define QQTBODYMOUSELOCKER_P_H

#include <QtCore/qglobal.h>
#include <QMouseEvent>
#include <QThread>

class QQtBodyMouseMouseLockerThreadHelper : public QThread
{
    Q_OBJECT

public:
    //建议初始化
    static QQtBodyMouseMouseLockerThreadHelper* instance ( QObject* parent = 0 ) {
        static QQtBodyMouseMouseLockerThreadHelper* helper = 0;
        if ( !helper )
            helper = new QQtBodyMouseMouseLockerThreadHelper ( parent );
        return helper;
    }

    void setTargetGlobalRect ( QRect globalRect );
    QRect getTargetGlobalRect ();

    void startCapture();
    void stopCapture();

private:
    QQtBodyMouseMouseLockerThreadHelper ( QObject* parent = 0 );
    virtual ~QQtBodyMouseMouseLockerThreadHelper();

    // QThread interface
protected:
    virtual void run() override;

private:
    QMutex tex;
    QRect mGlobalRect;
    bool workflag;
};

class QQtBodyMouseLocker;
class QQtBodyMouseLockerPrivate
{
public:
    QQtBodyMouseLockerPrivate ( QQtBodyMouseLocker* q );
    virtual ~QQtBodyMouseLockerPrivate();

    //允许定义区域 QRect(0,0,0,0)为关闭。 = ClipCursor
    void addRect ( const QRect globalRect );
    QRect getRect();

    //允许按照窗口进行定义
    void addWindow ( QWidget* target );

    //允许手动开关
    void startCapture();
    void stopCapture();

private:
    QQtBodyMouseLocker* q_ptr;
    Q_DECLARE_PUBLIC ( QQtBodyMouseLocker )

    QQtBodyMouseMouseLockerThreadHelper* helper;
};

#endif //QQTBODYMOUSELOCKER_P_H
