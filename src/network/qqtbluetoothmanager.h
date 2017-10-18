#ifndef QQTBLUETOOTHMANAGER_H
#define QQTBLUETOOTHMANAGER_H

#include <qbluetoothglobal.h>

#include <qbluetoothuuid.h>
#include <qbluetoothaddress.h>

#include <qbluetoothlocaldevice.h>
#include <qbluetoothserviceinfo.h>

#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothservicediscoveryagent.h>

#include "qqt-local.h"
#include <QMap>
#include <QList>

class QQTSHARED_EXPORT QQtBluetoothManager : public QBluetoothLocalDevice
{
    Q_OBJECT
public:
    static QQtBluetoothManager *Instance(QObject* parent = 0);
    /**
     * @brief changeAdapter
     * @param adapterAddress
     * local device
     */
    void changeAdapter(QBluetoothAddress& adapterAddress);
    void powerOff();
    bool isPowerOn();
    bool isDiscoverable();
    void setAutoScan(bool scan = true);
    void setDiscoverable(bool able = true);
    void refresh();
    /**
     * @brief getDeviceList
     * remote device
     */
    QList<QBluetoothDeviceInfo> getDeviceList();
    QList<QBluetoothServiceInfo> getServiceList(QBluetoothAddress& address);
signals:
    /**
     * @brief addDevice
     * working signals
     */
    void addDevice(QBluetoothDeviceInfo);
    void deviceScanFinished();
    void addService(QBluetoothServiceInfo);
    void serviceScanFinished();


public slots:
private slots:
    void slot_addDevice(QBluetoothDeviceInfo);
    void slot_addService(QBluetoothServiceInfo);
protected:
private:
    explicit QQtBluetoothManager(QObject *parent = nullptr);
    static QQtBluetoothManager* _instance;

    QBluetoothDeviceDiscoveryAgent* deviceDiscoveryAgent;
    QList<QBluetoothServiceDiscoveryAgent*> sl;
    QList<QBluetoothServiceDiscoveryAgent*>::Iterator slitor;
    bool bAutoScan;
    QBluetoothAddress m_adapterAddress;
};

#endif // QQTBLUETOOTHMANAGER_H
