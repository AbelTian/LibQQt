#ifndef QQTWEBSOCKETSERVER_H
#define QQTWEBSOCKETSERVER_H

#include <QWebSocketServer>
#include <qqtwebsocketclient.h>
#include <qqtprotocolmanager.h>
#include <qqtcore.h>

/**
 * @brief The QQtWebSocketServer class
 * please handleConnection
 */
class QQTSHARED_EXPORT QQtWebSocketServer : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit QQtWebSocketServer ( const QString& serverName, SslMode secureMode,
                                  QObject* parent = nullptr );
    virtual ~QQtWebSocketServer() {}

    void installProtocolManager ( QQtProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtProtocolManager* stackGroup );
    QQtProtocolManager* installedProtocolManager();

public:
    QQtWebSocketClient* findClientByProtocolInstance ( QQtProtocol* protocol );
    QQtWebSocketClient* findClientByIPAddress ( QString ip, quint16 port );
    QList<QQtWebSocketClient*>& clientList() { return m_clientList; }


signals:

private slots:
    void comingNewConnection();
public slots:
    void clientSocketDisConnected();
private:
    QQtProtocolManager* m_protocolManager;
    QList<QQtWebSocketClient*> m_clientList;
};

#endif // QQTWEBSOCKETSERVER_H
