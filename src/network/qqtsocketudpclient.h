#ifndef QQTUDPCLIENT_H
#define QQTUDPCLIENT_H

#include <QUdpSocket>
#include "qqtudpprotocol.h"
#include "qqt-local.h"
#include "qqtcore.h"

class QQtSocketUdpClient : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtSocketUdpClient ( QObject* parent = nullptr );
    virtual ~QQtSocketUdpClient() {}

    void installProtocol ( QQtUdpProtocol* stack );
    void uninstallProtocol ( QQtUdpProtocol* stack );
    QQtUdpProtocol* installedProtocol();

signals:
    void signalConnecting();
    void signalConnectSucc();
    void signalConnectFail();//
    void signalDisConnectSucc();//maybe
    void signalDisConnectFail();//
    void signalUpdateProgress ( qint64 value );
public slots:

protected slots:
    void readyReadData();
private slots:
    void domainHostFound();
    void socketStateChanged ( QAbstractSocket::SocketState );
    void socketErrorOccured ( QAbstractSocket::SocketError );
    void socketConnected();
    void socketDisconnect();
    void updateProgress ( qint64 bytes );
    qint64 slotWriteDatagram ( const QNetworkDatagram& datagram );

private:
    QQtUdpProtocol* m_protocol;
};

#endif // QQTUDPCLIENT_H
