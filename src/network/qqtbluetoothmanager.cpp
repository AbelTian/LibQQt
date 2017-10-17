#include "qqtbluetoothmanager.h"

QQtBluetoothManager* QQtBluetoothManager::_instance = NULL;

QQtBluetoothManager *QQtBluetoothManager::Instance(QObject *parent)
{
    if(_instance)
        return _instance;
    _instance = new QQtBluetoothManager(parent);
    return _instance;
}

void QQtBluetoothManager::changeAdapter(QBluetoothAddress &adapterAddress)
{
    if(serviceDiscoveryAgent)
        delete serviceDiscoveryAgent;
    serviceDiscoveryAgent = new QBluetoothServiceDiscoveryAgent(adapterAddress, this);

    connect(serviceDiscoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SIGNAL(addService(QBluetoothServiceInfo)));
    connect(serviceDiscoveryAgent, SIGNAL(finished()), this, SIGNAL(serviceScanFinished()));

    if(deviceDiscoveryAgent)
        delete deviceDiscoveryAgent;
    deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(adapterAddress, this);

    connect(deviceDiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SIGNAL(addDevice(QBluetoothDeviceInfo)));
    connect(deviceDiscoveryAgent, SIGNAL(finished()), this, SIGNAL(deviceScanFinished()));

    setAutoScan(true);
}

void QQtBluetoothManager::powerOff()
{
    setHostMode(HostPoweredOff);
}

bool QQtBluetoothManager::isPowerOn()
{
    HostMode mode = hostMode();
    if(mode == HostPoweredOff)
        return false;
    return true;
}

bool QQtBluetoothManager::isDiscoverable()
{
    HostMode mode = hostMode();
    if(mode == HostDiscoverable)
        return true;
    return false;
}

void QQtBluetoothManager::setAutoScan(bool scan)
{
    if(scan)
    {
        bAutoScan = true;
        deviceDiscoveryAgent->start();
        serviceDiscoveryAgent->clear();
        serviceDiscoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
    }
    else
    {
        bAutoScan = false;
        deviceDiscoveryAgent->stop();
        serviceDiscoveryAgent->stop();
    }

}

void QQtBluetoothManager::setDiscoverable(bool able)
{
    if(able)
        setHostMode(HostDiscoverable);
    else
        setHostMode(HostConnectable);
}

void QQtBluetoothManager::getRemoteService(QBluetoothAddress &remoteAddress)
{
    serviceDiscoveryAgent->setRemoteAddress(remoteAddress);
    serviceDiscoveryAgent->clear();
    serviceDiscoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
}

QQtBluetoothManager::QQtBluetoothManager(QObject *parent) :
    QBluetoothLocalDevice(parent),
    serviceDiscoveryAgent(nullptr),
    deviceDiscoveryAgent(nullptr),
    bAutoScan(true)
{
    QBluetoothAddress adapterAddress = address();
    changeAdapter(adapterAddress);
}
