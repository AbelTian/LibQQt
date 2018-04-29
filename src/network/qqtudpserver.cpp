#include "qqtudpserver.h"

QQtUdpServer::QQtUdpServer ( QObject* parent ) : QQtUdpClient ( parent )
{
    m_protocolManager = NULL;
}

void QQtUdpServer::installProtocolManager ( QQtProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;
}

void QQtUdpServer::uninstallProtocolManager ( QQtProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )

    if ( !m_protocolManager )
        return;

    m_protocolManager = NULL;
}

QQtProtocolManager* QQtUdpServer::installedProtocolManager()
{
    return m_protocolManager;
}

void QQtUdpServer::clientSocketDisConnected()
{
    QObject* obj = sender();
    QQtUdpClient* clientSocket = ( QQtUdpClient* ) obj;
    QQtProtocol* protocol = clientSocket->installedProtocol();
    clientSocket->uninstallProtocol ( protocol );
    clientSocket->deleteLater();
    protocol->deleteLater();
    m_clientList.removeOne ( clientSocket );
}

QQtUdpClient* QQtUdpServer::findClientByProtocolInstance ( QQtProtocol* protocol )
{
    QListIterator<QQtUdpClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtUdpClient* client = itor.next();
        QQtProtocol* cprotocol = client->installedProtocol();
        if ( cprotocol == protocol )
        {
            return client;
        }
    }
    return NULL;
}

QQtUdpClient* QQtUdpServer::findClientByIPAddress ( QString ip, quint16 port )
{
    QListIterator<QQtUdpClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtUdpClient* client = itor.next();
        QString aip;
        quint16 aport;
        client->getServer ( aip, aport );
        if ( aip == ip && aport == port )
        {
            return client;
        }
    }
    return NULL;
}


void QQtUdpServer::readyReadData()
{
    /*为什么用while?*/ //Qt4 没有那么高级的一次性读取的接口?有
    while ( hasPendingDatagrams() )
    {
        QByteArray bytes;
        QHostAddress address;
        quint16 port;
        recvDatagram ( bytes, address, port );

        QString sip;
        quint16 sport;
        getServer ( sip, sport );
        if ( address.toString() == sip && sport == port )
        {
            //如果，特别的那个目标。
            translator ( bytes );
        }
        else
        {
            QQtUdpClient* clientSocket = findClientByIPAddress ( address.toString(), port );
            if ( !clientSocket )
            {
                clientSocket = new QQtUdpClient ( this );
                clientSocket->setServer ( address.toString(), port );
                connect ( clientSocket, SIGNAL ( disconnected() ), this, SLOT ( clientSocketDisConnected() ) );
                //如果崩溃，对这个操作进行加锁。
                QQtProtocol* protocol = m_protocolManager->createProtocol();
                clientSocket->installProtocol ( protocol );
                m_clientList.push_back ( clientSocket );
            }
            clientSocket->translator ( bytes );
        }
    }
}


