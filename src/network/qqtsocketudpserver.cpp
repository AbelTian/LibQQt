#include "qqtsocketudpserver.h"
#include "qqtnetwork.h"
#include <QNetworkDatagram>
#include <QNetworkInterface>

QQtSocketUdpServer::QQtSocketUdpServer ( QObject* parent ) : QUdpSocket ( parent )
{
    m_thread = new QThread ( this );
    moveToThread ( m_thread );
}

QQtSocketUdpServer::~QQtSocketUdpServer()
{
    stopListening();
}

void QQtSocketUdpServer::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;

    m_protocol = stack;
}

void QQtSocketUdpServer::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    m_protocol = NULL;
}

QQtProtocol* QQtSocketUdpServer::installedProtocol()
{
    return m_protocol;
}

void QQtSocketUdpServer::startListening()
{
    m_thread->start();

    while ( 1 )
    {
        bool hasNew = hasPendingDatagrams();

        if ( !hasNew )
            continue;

        qint64 size = pendingDatagramSize();
        pline() << "new msg size:" << size;

        QNetworkDatagram da = receiveDatagram();
        //...
    }
}

void QQtSocketUdpServer::stopListening()
{
    m_thread->exit();
    close();
}
