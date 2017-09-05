#ifndef QQTETHMANAGER_H
#define QQTETHMANAGER_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <qthread.h>
#include "qqtcore.h"

class QQTNetworkClearThread : public QThread
{
    Q_OBJECT
public:
    QQTNetworkClearThread(QObject* parent = 0) : QThread(parent) {
    }
signals:
    void cleared();
    void notcleared();

    // QThread interface
protected:
    void run();
};

class QQTDhcpThread : public QThread
{
    Q_OBJECT
public:
    QQTDhcpThread(QObject* parent = 0) : QThread(parent) {
    }
    void setnet(QString eth = "eth0") {net=eth;}
signals:
    void passed(QString);
    // QThread interface
protected:
    void run();
private:
    QString net;
};

// thread unsafe
class QQTEthenetManager : public QObject
{
    Q_OBJECT
public:
    static QQTEthenetManager *Instance(QObject* parent = 0);

    QList<TWifi>& wifiList() { return m_wifiList; }
    inline TWifi currentWifi(){ return m_curWifi; }
    bool setCurrentWifi(QString bssid_mac, QString password = "");
    void setRefresh(bool ref = true) { ref ? m_workTimer->start(5000) : m_workTimer->stop(); }
    void setDHCP(bool bUse = false) { m_bUseDHCP = bUse; }
    void setAddr(QString ip, QString mask, QString gw, QString dns);
    void getAddr(QString& ip, QString& mask, QString& gw, QString& dns);
    /**
     * @brief configIPAddress
     * wpa_suplicant.conf
     * net.sh
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
    void sigStatusChanged(QString status);
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
    void DhcpPassed(QString netname);
    void checkNetworkClear();

private:
    explicit QQTEthenetManager(QObject *parent = 0);
    void readStatus();
    void restoreWifi();
    bool restartWifi();
    void saveScript();
    void config();

signals:

public slots:
private:
    static QQTEthenetManager* _instance;
    QTimer* m_workTimer;
    QList<TWifi> m_wifiList;
    TWifi m_curWifi;
    bool m_bUseDHCP;
    QString m_netName;
    QQTDhcpThread* m_thread;
    QQTNetworkClearThread* m_clearThread;
    QString m_status;
};

#endif // QQTETHMANAGER_H
