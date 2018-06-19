#ifndef KONGZHIQIUDPPROTOCOL_H
#define KONGZHIQIUDPPROTOCOL_H

#include <qqtprotocol.h>
#include <qqtcore.h>
#include <kongzhiqiudpmessage.h>
#include <cedianudpserver.h>

class KongzhiqiUdpProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit KongzhiqiUdpProtocol ( QObject* parent = nullptr );
    virtual ~KongzhiqiUdpProtocol() {}
    //起动命令
    void sendStartMessage ( const QHostAddress& address, quint16 port, const KongzhiqiUdpMessage& st );
    void sendStartMessage ( const QHostAddress& address, quint16 port, const QByteArray msg );
    void sendStartMessage ( const QNetworkDatagram& dg );
    //停机命令
    void sendStopMessage ( const QHostAddress& address, quint16 port, const KongzhiqiUdpMessage& st );
    void sendStopMessage ( const QHostAddress& address, quint16 port, const QByteArray msg );
    void sendStopMessage ( const QNetworkDatagram& dg );
    //频率调节命令
    void sendFreMessage ( const QHostAddress& address, quint16 port, const KongzhiqiUdpMessage& st );
    void sendFreMessage ( const QHostAddress& address, quint16 port, const QByteArray msg );
    void sendFreMessage ( const QNetworkDatagram& dg );
    //励磁调节命令
    void sendVolMessage ( const QHostAddress& address, quint16 port, const KongzhiqiUdpMessage& st );
    void sendVolMessage ( const QHostAddress& address, quint16 port, const QByteArray msg );
    void sendVolMessage ( const QNetworkDatagram& dg );
    //并网命令
    void sendSynMessage ( const QHostAddress& address, quint16 port, const KongzhiqiUdpMessage& st );
    void sendSynMessage ( const QHostAddress& address, quint16 port, const QByteArray msg );
    void sendSynMessage ( const QNetworkDatagram& dg );
    //解列命令
    void sendStepoutMessage ( const QHostAddress& address, quint16 port, const KongzhiqiUdpMessage& st );
    void sendStepoutMessage ( const QHostAddress& address, quint16 port, const QByteArray msg );
    void sendStepoutMessage ( const QNetworkDatagram& dg );
signals:

public slots:
};

KongzhiqiUdpProtocol* kongzhiqiUdpServer ( QObject* parent = 0 );

#endif // KONGZHIQIUDPPROTOCOL_H
