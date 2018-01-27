#include "kongzhiqiudpprotocol.h"

KongzhiqiUdpProtocol::KongzhiqiUdpProtocol(QObject *parent) : QQtUdpProtocol(parent)
{

}

//起动命令
void KongzhiqiUdpProtocol::sendStartMessage(const QHostAddress &address, quint16 port, const KongzhiqiUdpMessage &st)
{
    QByteArray msg;
    st.getCommand() << 1;
    st.packer(msg);
    sendStartMessage(address, port, msg);
}
void KongzhiqiUdpProtocol::sendStartMessage(const QHostAddress &address, quint16 port, const QByteArray msg)
{
    QNetworkDatagram dg;
    dg.setDestination(address, port);
    dg.setData(msg);
    sendStartMessage(dg);
}
void KongzhiqiUdpProtocol::sendStartMessage(const QNetworkDatagram &dg)
{
    writeDatagram(dg);
}

//停机命令
void KongzhiqiUdpProtocol::sendStopMessage(const QHostAddress &address, quint16 port, const KongzhiqiUdpMessage &st)
{
    QByteArray msg;
    st.getCommand() << 2;
    st.packer(msg);
    sendStopMessage(address, port, msg);
}
void KongzhiqiUdpProtocol::sendStopMessage(const QHostAddress &address, quint16 port, const QByteArray msg)
{
    QNetworkDatagram dg;
    dg.setDestination(address, port);
    dg.setData(msg);
    sendStopMessage(dg);
}
void KongzhiqiUdpProtocol::sendStopMessage(const QNetworkDatagram &dg)
{
    writeDatagram(dg);
}

//自动频率调节命令
void KongzhiqiUdpProtocol::sendFreMessage(const QHostAddress &address, quint16 port, const KongzhiqiUdpMessage &st)
{
    QByteArray msg;
    st.getCommand() << 3;
    st.packer(msg);
    sendFreMessage(address, port, msg);
}
void KongzhiqiUdpProtocol::sendFreMessage(const QHostAddress &address, quint16 port, const QByteArray msg)
{
    QNetworkDatagram dg;
    dg.setDestination(address, port);
    dg.setData(msg);
    sendFreMessage(dg);
}
void KongzhiqiUdpProtocol::sendFreMessage(const QNetworkDatagram &dg)
{
    writeDatagram(dg);
}

//自动励磁调节命令
void KongzhiqiUdpProtocol::sendVolMessage(const QHostAddress &address, quint16 port, const KongzhiqiUdpMessage &st)
{
    QByteArray msg;
    st.getCommand() << 4;
    st.packer(msg);
    sendVolMessage(address, port, msg);
}
void KongzhiqiUdpProtocol::sendVolMessage(const QHostAddress &address, quint16 port, const QByteArray msg)
{
    QNetworkDatagram dg;
    dg.setDestination(address, port);
    dg.setData(msg);
    sendVolMessage(dg);
}
void KongzhiqiUdpProtocol::sendVolMessage(const QNetworkDatagram &dg)
{
    writeDatagram(dg);
}

//并网命令
void KongzhiqiUdpProtocol::sendSynMessage(const QHostAddress &address, quint16 port, const KongzhiqiUdpMessage &st)
{
    QByteArray msg;
    st.getCommand() << 5;
    st.packer(msg);
    sendSynMessage(address, port, msg);
}
void KongzhiqiUdpProtocol::sendSynMessage(const QHostAddress &address, quint16 port, const QByteArray msg)
{
    QNetworkDatagram dg;
    dg.setDestination(address, port);
    dg.setData(msg);
    sendSynMessage(dg);
}
void KongzhiqiUdpProtocol::sendSynMessage(const QNetworkDatagram &dg)
{
    writeDatagram(dg);
}

//解列命令
void KongzhiqiUdpProtocol::sendStepoutMessage(const QHostAddress &address, quint16 port, const KongzhiqiUdpMessage &st)
{
    QByteArray msg;
    st.getCommand() << 6;
    st.packer(msg);
    sendStepoutMessage(address, port, msg);
}
void KongzhiqiUdpProtocol::sendStepoutMessage(const QHostAddress &address, quint16 port, const QByteArray msg)
{
    QNetworkDatagram dg;
    dg.setDestination(address, port);
    dg.setData(msg);
    sendStepoutMessage(dg);
}
void KongzhiqiUdpProtocol::sendStepoutMessage(const QNetworkDatagram &dg)
{
    writeDatagram(dg);
}

KongzhiqiUdpProtocol *kongzhiqiUdpServer(QObject *parent){
    static CedianUdpServer* s0 = NULL;
    static KongzhiqiUdpProtocol* p0 = NULL;
    if(!s0 && !p0){
        p0 = new KongzhiqiUdpProtocol(parent);
        s0 = new CedianUdpServer(p0);
        /*通讯端口：绑定本地端口*/
        s0->bind(7200);
        /*通讯端口：给控制器协议*/
        s0->installProtocol(p0);
    }
    return p0;
}
