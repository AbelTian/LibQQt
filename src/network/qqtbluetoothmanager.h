#ifndef QQTBLUETOOTHMANAGER_H
#define QQTBLUETOOTHMANAGER_H

#include <qbluetoothglobal.h>

#include <qbluetoothuuid.h>
#include <qbluetoothaddress.h>

#include <qbluetoothlocaldevice.h>
#include <qbluetoothserviceinfo.h>

#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothservicediscoveryagent.h>

class QQtBluetoothManager : public QBluetoothLocalDevice
{
    Q_OBJECT
public:
    static QQtBluetoothManager *Instance(QObject* parent = 0);

    void changeAdapter(QBluetoothAddress& adapterAddress);
    void powerOff();
    bool isPowerOn();
    bool isDiscoverable();

    void setAutoScan(bool scan = true);
    void setDiscoverable(bool able = true);

    void getRemoteService(QBluetoothAddress& remoteAddress);

signals:
    void addService(QBluetoothServiceInfo);
    void addDevice(QBluetoothDeviceInfo);
    void deviceScanFinished();
    void serviceScanFinished();
public slots:
private:
    explicit QQtBluetoothManager(QObject *parent = nullptr);
    static QQtBluetoothManager* _instance;

    QBluetoothServiceDiscoveryAgent *serviceDiscoveryAgent;
    QBluetoothDeviceDiscoveryAgent *deviceDiscoveryAgent;

    bool bAutoScan;
};

#endif // QQTBLUETOOTHMANAGER_H
