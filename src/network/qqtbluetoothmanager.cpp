#include "qqtbluetoothmanager.h"
#include "qqtcore.h"

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
    if(adapterAddress!=m_adapterAddress)
        m_adapterAddress = adapterAddress;

    if(deviceDiscoveryAgent) {
        deviceDiscoveryAgent->stop();
        delete deviceDiscoveryAgent;
    }
    for(slitor = sl.begin(); slitor!= sl.end(); slitor++) {
        QBluetoothServiceDiscoveryAgent* sa = (QBluetoothServiceDiscoveryAgent*)*slitor;
        sa->stop();
        sa->clear();
        delete sa;
    }

    sl.clear();

    deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(adapterAddress, this);


    connect(deviceDiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SIGNAL(addDevice(QBluetoothDeviceInfo)));
    connect(deviceDiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(slot_addDevice(QBluetoothDeviceInfo)));
    connect(deviceDiscoveryAgent, SIGNAL(finished()),
            this, SIGNAL(deviceScanFinished()));

    setAutoScan(bAutoScan);
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
    bAutoScan = scan;
    if(scan)
    {
        deviceDiscoveryAgent->start();
    }
    else
    {
        deviceDiscoveryAgent->stop();
    }

}

void QQtBluetoothManager::setDiscoverable(bool able)
{
    if(able)
        setHostMode(HostDiscoverable);
    else
        setHostMode(HostConnectable);
}

void QQtBluetoothManager::refresh()
{
    changeAdapter(m_adapterAddress);
}

QList<QBluetoothDeviceInfo> QQtBluetoothManager::getDeviceList()
{
    if(deviceDiscoveryAgent)
        return deviceDiscoveryAgent->discoveredDevices();
    //empty
    return QList<QBluetoothDeviceInfo>();
}

QList<QBluetoothServiceInfo> QQtBluetoothManager::getServiceList(QBluetoothAddress &address)
{
    for(slitor = sl.begin(); slitor!= sl.end(); slitor++) {
        QBluetoothServiceDiscoveryAgent* sa = (QBluetoothServiceDiscoveryAgent*)*slitor;
        if (sa->remoteAddress() == address) {
            return sa->discoveredServices();
        }
    }
    //empty
    return QList<QBluetoothServiceInfo>();
}

void QQtBluetoothManager::slot_addDevice(QBluetoothDeviceInfo info)
{
    pline() << info.address() << info.name();
    QBluetoothServiceDiscoveryAgent* serviceDiscoveryAgent = new QBluetoothServiceDiscoveryAgent(m_adapterAddress, this);
    connect(serviceDiscoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SIGNAL(addService(QBluetoothServiceInfo)));
    connect(serviceDiscoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(slot_addService(QBluetoothServiceInfo)));
    connect(serviceDiscoveryAgent, SIGNAL(finished()),
            this, SIGNAL(serviceScanFinished()));
    serviceDiscoveryAgent->setRemoteAddress(info.address());
    serviceDiscoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
    sl.append(serviceDiscoveryAgent);
}

void QQtBluetoothManager::slot_addService(QBluetoothServiceInfo info)
{
    pline() << info;
}

QQtBluetoothManager::QQtBluetoothManager(QObject *parent) :
    QBluetoothLocalDevice(parent),
    deviceDiscoveryAgent(nullptr),
    bAutoScan(true)
{
    m_adapterAddress = address();
    changeAdapter(m_adapterAddress);
}
