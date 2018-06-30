#ifndef QQTNFCSERVER_H
#define QQTNFCSERVER_H

#include <QObject>
#include <QtNfc>
#include "qqtprotocolmanager.h"
#include "qqtnfcclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * QQtNfcServer
 * 继承自QNearFieldManager，可以搜索target
 * 支持多个target，在protocol就可以完整应付一个target。如果业务层感兴趣，protocol发送消息给protocolManager。
 *
 */
class QQTSHARED_EXPORT QQtNfcServer : public QNearFieldManager
{
    Q_OBJECT
public:
    explicit QQtNfcServer ( QObject* parent = Q_NULLPTR );
    virtual ~QQtNfcServer();

    void installProtocolManager ( QQtProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtProtocolManager* stackGroup );
    QQtProtocolManager* installedProtocolManager();

    /**
     * 以下和用户无关
     */
protected slots:
    //把target转移给内部target
    void hasPendingTarget ( QNearFieldTarget* target );
    //删除target，删除内部target
    void hasTargetLosted ( QNearFieldTarget* target );

protected:
private:
    QQtNfcClient* findInstanceByUid ( QByteArray uid );
    QQtProtocolManager* m_protocolManager;
    QList<QQtNfcClient*> m_clientList;
};

#endif // QQTNFCSERVER_H
