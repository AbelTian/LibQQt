#ifndef QQTSINGLETONAPPLICATION_H
#define QQTSINGLETONAPPLICATION_H

#include <QObject>
#include <QQtApplication>
#include <qqt-local.h>
#include <qqtcore.h>
#include <qqtmsgbox.h>

#include <qlocalsocket.h>

class QQtSingleTonLocalClientProtocol;
class QQtLocalClient;
QQtLocalClient* QQtSingleTonLocalClientInstance ( QQtSingleTonLocalClientProtocol*& protocol, QObject* parent = 0 );

class QQtProtocolManager;
class QQtLocalServer;
QQtLocalServer* QQtSingleTonLocalServerInstance ( QQtProtocolManager*& protocol, QObject* parent = 0 );

/**
 * @brief The QQtSingleApplication class
 * 单实例Application。
 *
 * 使用方法：
 * 继承下去，显式调用
 * QQtApplication::setOrganizationName ( "AppName" );
 * QQtApplication::setOrganizationDomain ( "www.appname.com" ); //
 * QQtApplication::setApplicationName ( "AppName" ); //必要。
 * startSingleTonInstance();
 */
class QQTSHARED_EXPORT QQtSingleTonApplication : public QQtApplication
{
    Q_OBJECT
public:
    explicit QQtSingleTonApplication ( int& argc, char** argv );
    virtual ~QQtSingleTonApplication();

    void startSingleTonInstance();

protected slots:
    void slotSocketStateChanged ( QLocalSocket::LocalSocketState );
    void slotConnectSuccess();
    void slotConnectFail();
    void slotAccept();
    void slotReject();

private:
    QQtSingleTonLocalClientProtocol* p0;
    QQtLocalClient* c0;

    QQtProtocolManager* pm0;
    QQtLocalServer* s0;

    bool hasServer;
    bool bAccepted;
};


#endif // QQTSINGLETONAPPLICATION_H
