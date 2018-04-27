#ifndef QQTHGBLUETOOTHSERVER_H
#define QQTHGBLUETOOTHSERVER_H

#include <QBluetoothServer>
#include "qqthgprotocol.h"
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtHgBluetoothServer : public QBluetoothServer
{
    Q_OBJECT
public:
    explicit QQtHgBluetoothServer ( QBluetoothServiceInfo::Protocol serverType, QObject* parent = nullptr );
    ~QQtHgBluetoothServer();

    void installProtocol ( QQtHgProtocol* stack );
    void uninstallProtocol ( QQtHgProtocol* stack );
    QQtHgProtocol* installedProtocol();

signals:

public slots:

signals:

private slots:
    void comingNewConnection();

private:
    QQtHgProtocol* m_protocol;
};

#endif // QQTHGBLUETOOTHSERVER_H
