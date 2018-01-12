#ifndef QQTUDPPROTOCOL_H
#define QQTUDPPROTOCOL_H

#include <QObject>
#include <qqt-local.h>
#include "qqtmessage.h"
#include "qqtcore.h"
#include <QNetworkDatagram>

/*
*/
class QQTSHARED_EXPORT QQtUdpProtocol : public QObject
{
    Q_OBJECT
public:
    explicit QQtUdpProtocol ( QObject* parent = nullptr );
    virtual ~QQtUdpProtocol() {}

signals:
    qint64 writeDatagram ( const QNetworkDatagram& );
public slots:
protected:
    /**
     * @brief 语义解析器
     * @brief 用户必须继承下去，重写，need override
     * @param 数据包
     * @return 0 no dispatched(others) 1 dispatched(own)
     */
    inline virtual bool dispatcher ( const QNetworkDatagram& ) { return 0; }
public:
    /**
     * @brief 协议处理器
     * @brief 这个处理器是给QQtSocketUdpSocket用的，不是给客户用的。
     * @param Qt通讯口readAll()读到的bytes
     * @return
     */
    void translator ( const QNetworkDatagram& dg );
};

#endif // QQTUDPPROTOCOL_H
