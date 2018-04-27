#ifndef QQTHGTCPPROTOCOL_H
#define QQTHGTCPPROTOCOL_H

#include <QObject>
#include <qqt-local.h>
#include "qqtcore.h"
#include "qqthgprotocol.h"

/**
 * @brief The QQtHgTcpProtocol class
 * very good ideology and impliment
 */
class QQTSHARED_EXPORT QQtHgTcpProtocol : public QQtHgProtocol
{
    Q_OBJECT
public:
    explicit QQtHgTcpProtocol ( QObject* parent = 0 );
    virtual ~QQtHgTcpProtocol();

    /*以下和用户无关*/
public:
    /**
     * @brief 协议处理器
     * 这个处理器是给HgSocket用的，不是给客户用的。
     * ProtocolManager，安装了这个协议，需要用户句柄。
     * @param Qt通讯口readAll()读到的bytes
     * @return
     */
    void translator ( const QAbstractSocket* client, QByteArray& bytes );
};

#endif // QQTHGTCPPROTOCOL_H
