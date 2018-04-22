#ifndef QQTUDPSERVELPROTOCOL_H
#define QQTUDPSERVELPROTOCOL_H

#include <QObject>
#include <qqt-local.h>
#include "qqtmessage.h"
#include "qqtcore.h"

#define QT_VERSION_DATAGRAM QT_VERSION_CHECK(5,8,0)

#if QT_VERSION > QT_VERSION_DATAGRAM
#include <QNetworkDatagram>
#endif

/*
*/
class QQTSHARED_EXPORT QQtUdpServerProtocol : public QObject
{
    Q_OBJECT
public:
    explicit QQtUdpServerProtocol ( QObject* parent = nullptr ) : QObject ( parent ) {

    }
    virtual ~QQtUdpServerProtocol() {}

#if QT_VERSION > QT_VERSION_DATAGRAM
    qint64 writeDatagram ( const QNetworkDatagram& datagram ) {
        QByteArray dg = datagram.data();
        QHostAddress addr = datagram.destinationAddress();
        int port = datagram.destinationPort();
        emit writeDatagram ( dg, addr, ( quint16 ) port );
    }
#endif

signals:
    qint64 writeDatagram ( const QByteArray& datagram,
                           const QHostAddress& host, quint16 port );

public slots:

protected:
    /**
     * @brief 语义解析器
     * @brief 用户必须继承下去，重写，need override
     * @param 数据包
     * @return 0 no dispatched(others) 1 dispatched(own)
     */
    inline virtual bool dispatcher ( const QByteArray& datagram,
                                     const QHostAddress& host, quint16 port ) {
        return 0;
    }
    /*
     * 这两个dispatcher，任选其一重写。
     */
#if QT_VERSION > QT_VERSION_DATAGRAM
    inline virtual bool dispatcher ( const QNetworkDatagram& ) { return 0; }
#endif

public:
    /**
     * @brief 协议处理器
     * @brief 这个处理器是给QQtUdpSocket用的，不需要用户管理。
     * @param Qt通讯口readAll()读到的bytes
     * @return
     */
    void translator ( const QByteArray& datagram,
                      const QHostAddress& host, quint16 port ) {
        dispatcher ( datagram, host, port );
    }
#if QT_VERSION > QT_VERSION_DATAGRAM
    void translator ( const QNetworkDatagram& datagram ) {
        dispatcher ( datagram );
    }
#endif
};

#endif // QQTUDPSERVELPROTOCOL_H
