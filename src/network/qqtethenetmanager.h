#ifndef QQTETHMANAGER_H
#define QQTETHMANAGER_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <qthread.h>
#include "qqtcore.h"
#include "qqt-local.h"
#include "qqtnetwork.h"

class QQTSHARED_EXPORT QQtNetWorkClearThread : public QThread
{
    Q_OBJECT
public:
    QQtNetWorkClearThread ( QObject* parent = 0 ) : QThread ( parent ) {
    }
signals:
    void cleared();
    void notcleared();

    // QThread interface
protected:
    void run();
};

class QQTSHARED_EXPORT QQtDHCPThread : public QThread
{
    Q_OBJECT
public:
    QQtDHCPThread ( QObject* parent = 0 ) : QThread ( parent ) {
    }
    void setnet ( QString eth = "eth0" ) {net = eth;}
signals:
    void passed ( QString );
    // QThread interface
protected:
    void run();
private:
    QString net;
};

// thread unsafe
/**
 * @brief The QQtEthenetManager class
 * 原理：
 * S1:系统启动，调用init_net.sh
 * S2:系统运行，用户通过页面设置WiFi或者有线的IP等，或者设置为自动获取。
 *      保存IP到配置文件，启动时显示到用户页面上
 *      保存IP等到init_net.sh，系统启动时，网络连接状态正常。
 *      保存WiFi设置等到/etc/wpa_supplicant.conf
 * S3:用户插拔网线，WiFi自动切换为有线。
 * S4:用户重启系统，进入S1.
 *
 * 使用说明：
 * 调用QQtEthnetManager::Instance(parent)，并且连接相应的WiFi信号和用户的槽
 * 通过wifiList()，显示给用户看WiFi列表。每5s自动更新一次。在槽当中调用并更新界面
 * 通过setCurrentWiFi()更换用户连接的WiFi。用户点击更改输入密码了，就调这个保存。会自动配置WiFi和根据用户IP或者DHCP重来连接新WiFi。
 *
 *
 */
class QQTSHARED_EXPORT QQtEthenetManager : public QObject
{
    Q_OBJECT
public:
    static QQtEthenetManager* Instance ( QObject* parent = 0 );

    QList<TWifi>& wifiList() { return m_wifiList; }
    inline TWifi currentWifi() { return m_curWifi; }
    bool setCurrentWifi ( QString bssid_mac, QString password = "" );
    void setRefresh ( bool ref = true ) { ref ? m_workTimer->start ( 5000 ) : m_workTimer->stop(); }
    void setDHCP ( bool bUse = false ) { m_bUseDHCP = bUse; }
    void setAddr ( QString ip, QString mask, QString gw, QString dns );
    void getAddr ( QString& ip, QString& mask, QString& gw, QString& dns );
    /**
     * @brief configIPAddress
     * wpa_suplicant.conf
     * init_net.sh
     * ipaddr.conf
     */
    void ipconfig();
    QString currentNetName();
    QTimer* workTimer() { return m_workTimer; }

signals:
    /*
     * 没有配置就会发送这个信号
     */
    void sigScanning();
    /*
     * 断开连接的状态
     */
    void sigDisConnected();
    /*
     * 正在连接的状态
     */
    void sigConnecting();
    /*
     * 连接成功的状态
     */
    void sigConnected();
    /*
     * Wifi列表更新 之上状态改变会影响list中wifi的标志位。
     */
    void sigRefreshed();
    /*
     * Wifi状态改变
     */
    void sigStatusChanged ( QString status );
    /*
     * 有线连接上
     */
    void sigLanConnected();
    /*
     * 有线断开
     */
    void sigLanDisConnected();
    /*
     * 网络线路连接上
     */
    void sigNetworkClear();
    /*
     * 网络线路断开
     */
    void sigNetworkNotClear();

private slots:
    void refreshWifiList();
    void refreshWifiStatus();
    void checkLanConnection();
    void DhcpPassed ( QString netname );
    void checkNetworkClear();

private:
    explicit QQtEthenetManager ( QObject* parent = 0 );
    void readStatus();
    void restoreWifi();
    bool restartWifi();
    void saveScript();
    void config();

signals:

public slots:
private:
    static QQtEthenetManager* _instance;
    QTimer* m_workTimer;
    QList<TWifi> m_wifiList;
    TWifi m_curWifi;
    bool m_bUseDHCP;
    QString m_netName;
    QQtDHCPThread* m_thread;
    QQtNetWorkClearThread* m_clearThread;
    QString m_status;
};

#endif // QQTETHMANAGER_H
