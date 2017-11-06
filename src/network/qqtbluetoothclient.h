#ifndef QQTBLUETOOTHCLIENT_H
#define QQTBLUETOOTHCLIENT_H

#include <qbluetoothsocket.h>
#include "qqtprotocol.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtBluetoothClient : public QBluetoothSocket
{
    Q_OBJECT
public:
    explicit QQtBluetoothClient(QBluetoothServiceInfo::Protocol socketType = QBluetoothServiceInfo::RfcommProtocol, QObject* parent = nullptr);
    explicit QQtBluetoothClient(QObject* parent = nullptr);

    /**
     * @brief setServiceInfo
     * 设置目标蓝牙地址
     */
    void setServiceInfo(const QBluetoothServiceInfo& serviceinfo) { m_serviceInfo = serviceinfo; }
    void setServiceAddress(const QBluetoothAddress& address) { m_serverIP = address; }
    /**
     * @brief setServicePort
     * @param p
     * 设置目标蓝牙端口 和UUID选择一个就可以
     */
    void setServicePort(quint16 p = 8888) { m_PORT = p; }
    void setServiceUUid(const QBluetoothUuid& uuid) { m_uuid = uuid; }

    void installProtocol(QQtProtocol* stack);
    void uninstallProtocol(QQtProtocol* stack);
    QQtProtocol* installedProtocol();

    void sendConnectMessage();
    int sendDisConnectFromHost();

signals:

public slots:

signals:
    void signalConnecting();
    void signalConnectSucc();
    void signalConnectFail();//
    void signalDisConnectSucc();//maybe
    void signalDisConnectFail();//
    void signalUpdateProgress(qint64 value);


private slots:
    void socketStateChanged(QBluetoothSocket::SocketState);
    void socketErrorOccured(QBluetoothSocket::SocketError);
    void socketConnected();
    void socketDisconnect();
    void updateProgress(qint64);

protected slots:
    void readyReadData();

private:
    void connectToSingelHost();
    void initSocket();

    QQtProtocol* m_protocol;

    QBluetoothServiceInfo m_serviceInfo;
    QBluetoothAddress m_serverIP;
    quint16 m_PORT;
    QBluetoothUuid m_uuid;
};

#endif // QQTBLUETOOTHCLIENT_H
