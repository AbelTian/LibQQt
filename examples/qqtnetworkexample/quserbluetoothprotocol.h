#ifndef QUSERBLUETOOTHPROTOCOL_H
#define QUSERBLUETOOTHPROTOCOL_H

#include <QObject>
#include "qqtbluetoothclient.h"

class QUserBluetoothProtocol : public QObject
{
    Q_OBJECT
public:
    explicit QUserBluetoothProtocol(QObject* parent = nullptr);

signals:

public slots:
};

QQtSocketBluetoothClient* QQtUserBluetoothClientInstance(QObject* parent = 0);

#endif // QUSERBLUETOOTHPROTOCOL_H
