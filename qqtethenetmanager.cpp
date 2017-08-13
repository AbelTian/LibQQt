#include "qqtethenetmanager.h"
#include "qqtlinux.h"
#include "qqtdefine.h"
#include "qqtgui-qt.h"

QQTEthenetManager* QQTEthenetManager::_instance = NULL;

QQTEthenetManager *QQTEthenetManager::Instance(QObject *parent)
{
    if(_instance)
        return _instance;
    _instance = new QQTEthenetManager(parent);
    return _instance;
}

bool QQTEthenetManager::setCurrentWifi(QString bssid_mac, QString password)
{
    for(QList<TWifi>::Iterator it = m_wifiList.begin();
        it != m_wifiList.end(); it++)
    {
        TWifi wifi = *it;
        if(bssid_mac == wifi[ESSID_BSSID])
        {
            m_status = "";
            m_curWifi = wifi;
            m_curWifi[ESSID_PASS] = password;
            break;
        }
    }

    restoreWifi();

    if(!restartWifi())
        return false;

    return true;
}

void QQTEthenetManager::ipconfig()
{
    saveScript();
    config();
}

QString QQTEthenetManager::currentNetName()
{
    if("eth0" == m_netName)
        return "Wired Lan";
    if("wlan0" == m_netName)
        if("COMPLETED" == m_status)
            return m_curWifi[ESSID_NAME];
    return "";
}

void QQTEthenetManager::readStatus()
{
    /*
     * 从 status 中读取
     */
    char result[MAX_LEN];
    char key[MAX_LEN]; //设置一个合适的长度，以存储每一行输出
    char value[MAX_LEN]; //设置一个合适的长度，以存储每一行输出

    bzero(result, MAX_LEN);
    bzero(key, MAX_LEN);
    bzero(value, MAX_LEN);
    FILE *pp = popen("wpa_cli -iwlan0 status", "r"); //建立管道
    if (!pp)
        return;
    while( fgets(result, sizeof(result), pp) != NULL)
    {
        sscanf(result, "%[^=]=%s", key, value);
        /*
         * 如果这里不用QString包含，会对比地址
         */
        if(QString("wpa_state") == QString(key)) {
            m_curWifi[ESSID_STATUS] = value;
        } else if(QString("bssid") == QString(key)) {
            m_curWifi[ESSID_BSSID] = value;
        } else if(QString("ssid") == QString(key)) {
            m_curWifi[ESSID_NAME] = value;
        }
    }
    pclose(pp);

    return;
}

void QQTEthenetManager::refreshWifiList()
{
    static int scanid = 0;
    if(scanid == 12)
        scanid = 0, system("wpa_cli -iwlan0 scan");
    scanid ++;

    FILE *pp = popen("wpa_cli -iwlan0 scan_r", "r"); //建立管道
    if (!pp)
        return;

    char cmdresult[MAX_LEN]; //设置一个合适的长度，以存储每一行输出
    fgets(cmdresult, sizeof(cmdresult), pp) ; //""

    char bssid[MAX_PATH];
    char frequency[MAX_PATH];
    char signal[MAX_PATH];
    char flag[MAX_PATH];
    char ssid[MAX_PATH];

    m_wifiList.clear();

    while( fgets(cmdresult, sizeof(cmdresult), pp) != NULL)
    {
        sscanf(cmdresult, "%s\t%s\t%s\t%s\t%s\n", bssid, frequency, signal, flag, ssid);

        TWifi wifi;
        wifi[ESSID_NAME] = ssid;
        if( strstr(flag, "WPA"))
            wifi[ESSID_TYPE] = "WPA";
        else
            wifi[ESSID_TYPE] = "WEP";
        if(strstr(flag, "WPA") || strstr(flag, "WEP"))
            wifi[ESSID_ENCRYP] = "YES";
        else
            wifi[ESSID_ENCRYP] = "NO";
        wifi[ESSID_PASS] = "";
        wifi[ESSID_BSSID] = bssid;
        wifi[ESSID_FREQ] = frequency;
        wifi[ESSID_SIGNAL] = signal;
        wifi[ESSID_FLAG] = flag;
        if(wifi[ESSID_BSSID] == m_curWifi[ESSID_BSSID])
            wifi[ESSID_STATUS] = m_curWifi[ESSID_STATUS];
        else
            wifi[ESSID_STATUS] = "";

        m_wifiList.push_back(wifi);

        //pline() << ssid << frequency << signal << flag << bssid << wifi[ESSID_STATUS];
    }

    //pline() << m_wifiList.size();
    pclose(pp); //关闭管道
    emit sigRefreshed();
}

void QQTEthenetManager::refreshWifiStatus()
{
    readStatus();

    if(m_status == m_curWifi[ESSID_STATUS])
        return;

    pline() << m_curWifi[ESSID_BSSID] << m_curWifi[ESSID_NAME] << m_curWifi[ESSID_STATUS];

    m_status = m_curWifi[ESSID_STATUS];
    emit sigStatusChanged(m_status);

    if("COMPLETED" == m_status)
        emit sigConnected();
    else if("SCANNING" == m_status)
        emit sigScanning();
    else if("ASSOCIATING" == m_status)
        emit sigConnecting();
    else if("INACTIVE" == m_status)
        emit sigDisConnected();
    else if("4WAY_HANDSHAKE" == m_status)
        emit sigDisConnected();
    else if("DISCONNECTED" == m_status)
        emit sigDisConnected();
}

void QQTEthenetManager::checkLanConnection()
{
    char cmdbuf[MAX_PATH];
    char cmdresult[MAX_PATH]; //设置一个合适的长度，以存储每一行输出
    bzero(cmdbuf, MAX_PATH);
    bzero(cmdresult, MAX_PATH);
    sprintf(cmdbuf, "cat /sys/class/net/eth0/carrier");
    FILE *pp = popen(cmdbuf, "r"); //建立管道
    fgets(cmdresult, sizeof(cmdresult), pp); //""
    pclose(pp);

    QString netName = m_netName;

    if(strstr(cmdresult, "0"))
        m_netName = "wlan0";
    else
        m_netName = "eth0";

    if(netName != m_netName)
    {
        config();
        if("wlan0" == m_netName)
            emit sigLanDisConnected();
        else
            emit sigLanConnected();
    }

    return;
}

void QQTEthenetManager::DhcpPassed(QString netname)
{
    int sockfd;
    struct ifreq ifr;
    struct sockaddr_in sin;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return;
    }
    strncpy(ifr.ifr_name, netname.toLatin1().data(), IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    //ip
    if(ioctl(sockfd, SIOCGIFADDR, &ifr) <0)
        perror("ioctl");
    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    QString ip = QString(inet_ntoa(sin.sin_addr));
    //mask
    if (ioctl(sockfd, SIOCGIFNETMASK, &ifr) < 0)
        perror("ioctl");
    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    QString mask = QString(inet_ntoa(sin.sin_addr));
    //mac
    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) < 0)
        perror("ioctl");
    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    QString mac = QString(inet_ntoa(sin.sin_addr));
    close(sockfd);
    //gw
    FILE *fp;
    char buf[MAX_PATH];
    char gateway[MAX_PATH];
    bzero(buf, MAX_PATH);
    bzero(gateway, MAX_PATH);
    fp = popen("ip route", "r");
    while(fgets(buf, sizeof(buf), fp) != NULL)
    {
        if(strstr(buf, "default via"))
        {
            sscanf(buf, "%*s%*s%s", gateway);
            break;
        }
    }
    pclose(fp);
    QString gw = gateway;
    //dns
    QFile file("/etc/resolv.conf");
    file.open(QFile::ReadOnly);
    QByteArray nameserver = file.readLine();
    nameserver[nameserver.size()-1] = '\0';
    QList<QByteArray> namelist = nameserver.split(' ');
    QString dns = namelist.size() > 1 ? namelist[1] : gw;
    file.close();

    //pt
    pline() << netname << ip << mask << gw << dns;

    setAddr(ip, mask, gw, dns);
    saveScript();
}

void QQTEthenetManager::checkNetworkClear()
{
    return;
    m_clearThread->start();
}

QQTEthenetManager::QQTEthenetManager(QObject *parent) :
    QObject(parent)
{
    m_bUseDHCP = false;
    m_clearThread = new QQTNetworkClearThread(this);
    connect(m_clearThread, SIGNAL(cleared()), this, SIGNAL(sigNetworkClear()));
    connect(m_clearThread, SIGNAL(notcleared()), this, SIGNAL(sigNetworkNotClear()));
    m_thread = new QQTDhcpThread(this);
    connect(m_thread, SIGNAL(passed(QString)), this, SLOT(DhcpPassed(QString)));
    /*
     * 检查网线
     * 搜索热点
     * 刷新连接状态
     */
    m_workTimer = new QTimer(this);
    m_workTimer->setSingleShot(false);
    connect(m_workTimer, SIGNAL(timeout()), this, SLOT(refreshWifiList()));
    connect(m_workTimer, SIGNAL(timeout()), this, SLOT(refreshWifiStatus()));
    connect(m_workTimer, SIGNAL(timeout()), this, SLOT(checkLanConnection()));
    connect(m_workTimer, SIGNAL(timeout()), this, SLOT(checkNetworkClear()));
#ifdef __MIPS_LINUX__
    m_workTimer->start(5000);
    /*
     * 更新一次，以后一直调用scan_r 5-6s
     */
    system("wpa_cli -iwlan0 scan");
#endif
}

void QQTEthenetManager::restoreWifi()
{
    QString name = m_curWifi[ESSID_NAME];
    QString password = m_curWifi[ESSID_PASS];
    QString encryt = m_curWifi[ESSID_ENCRYP];
    QString type = m_curWifi[ESSID_TYPE];

    char cmdbuf[MAX_PATH];
    char cmdresult[MAX_PATH];

    FILE* fp=fopen("/etc/wpa_supplicant.conf", "wb");
    fprintf(fp, "ctrl_interface=/var/run/wpa_supplicant\nctrl_interface_group=0\nap_scan=1\n\n");
    if("NO" == encryt)
    {
        pline() << "None Encryption";
        fprintf(fp, "network={\n\tssid=%s\n\tkey_mgmt=NONE\n\tpriority=5\n}\n", name.toLatin1().data());
    }
    else if("WEP" == type)
    {
        pline() << "WEP Encryption";
        fprintf(fp, "network={\n\tssid=\"%s\"\n\tkey_mgmt=NONE\n\twep_key0=%s\n\twep_tx_keyidx=0\n\tpriority=5\n\tauth_alg=SHARED\n}\n",
                name.toLatin1().data(), password.toLatin1().data());
    }
    else if("WPA" == type)
    {
        pline() << "WPA Encryption";
        bzero(cmdbuf, MAX_PATH);
        bzero(cmdresult, MAX_PATH);
#if 0
        sprintf(cmdbuf, "wpa_passphrase %s %s | awk 'NR==4{print $1}'", name.toLatin1().data(), wifiPassword.toLatin1().data());
        FILE *pp = popen(cmdbuf, "r"); //建立管道
        fgets(cmdresult, sizeof(cmdresult), pp) ; //""
        pclose(pp);
        fprintf(fp, "network={\n\tssid=\"%s\"\n\tkey_mgmt=WPA-PSK\n\tgroup=TKIP\n\tpairwise=CCMP\n\tproto=WPA\n\t#psk=\"%s\"\n\t%s\tpriority=5\n}\n",
                name, wifiPassword, cmdresult);
#else
        sprintf(cmdbuf, "wpa_passphrase %s %s", name.toLatin1().data(), password.toLatin1().data());
        FILE *pp = popen(cmdbuf, "r"); //建立管道
        while(fgets(cmdresult, sizeof(cmdresult), pp))  //""
        {
            fputs(cmdresult, fp);
        }
        pclose(pp);
#endif
    }
    fclose(fp);
}

bool QQTEthenetManager::restartWifi()
{
    char cmdbuf[MAX_PATH];
    char cmdresult[MAX_PATH]; //设置一个合适的长度，以存储每一行输出
    bzero(cmdbuf, MAX_PATH);
    bzero(cmdresult, MAX_PATH);
    sprintf(cmdbuf, "wpa_cli -iwlan0 reconf");
    FILE *pp = popen(cmdbuf, "r"); //建立管道
    fgets(cmdresult, sizeof(cmdresult), pp); //""
    pclose(pp);

    if(strstr(cmdresult, "FAIL"))
        return false;
    return true;
}

void QQTEthenetManager::saveScript()
{
    QString ip, mask, gw, dns;
    getAddr(ip, mask, gw, dns);

    QFile script("./net.sh");
    script.open(QFile::WriteOnly);
    char cmdbuf[MAX_PATH];
    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "#!/bin/sh\n\n");
    script.write(cmdbuf);

    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "ifconfig eth0 %s netmask %s up\n",
            ip.toLatin1().data(),
            mask.toLatin1().data());
    script.write(cmdbuf);

    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "ifconfig wlan0 %s netmask %s up\n",
            ip.toLatin1().data(),
            mask.toLatin1().data());
    script.write(cmdbuf);

    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "route add default gw %s netmask 0.0.0.0 dev eth0\n",
            gw.toLatin1().data());
    script.write(cmdbuf);

    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "route add default gw %s netmask 0.0.0.0 dev wlan0\n",
            gw.toLatin1().data());
    script.write(cmdbuf);

    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "echo nameserver %s > /etc/resolv.conf\n", dns.toLatin1().data());
    script.write(cmdbuf);

    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "wpa_supplicant -B -Dwext -iwlan0 -c/etc/wpa_supplicant.conf\n");
    script.write(cmdbuf);
    script.close();

    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "chmod +x ./net.sh");
    system(cmdbuf);
}

void QQTEthenetManager::config()
{
    char cmdbuf[MAX_PATH];
    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "ip route | awk '{print $1}' | while read line; do ip route del $line; done");
    system(cmdbuf);
    //system("route");

    if(m_bUseDHCP)
    {
        m_thread->setnet(m_netName);
        m_thread->start();
        return;
    }

    QString ip, mask, gw, dns;
    getAddr(ip, mask, gw, dns);

    pline() << m_netName << ip << mask << gw << dns;

    // add .0 route
    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "ifconfig %s 0.0.0.0 up", m_netName.toLatin1().data());
    system(cmdbuf);
    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "ifconfig %s %s netmask %s",
            m_netName.toLatin1().data(),
            ip.toLatin1().data(),
            mask.toLatin1().data());
    system(cmdbuf);
    QStringList sl = gw.split(".");
    if(sl.size() < 3) { sl.clear(); sl << "0" << "0" << "0" << "0";}
    QString net = QString("%1.%2.%3.0").arg(sl[0]).arg(sl[1]).arg(sl[2]);
#if 0
    /*
     * dhcp后 ifconfig up 引发了添加这条route
     * ifconfig 0.0.0.0 也能引发添加这条route
     */
    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "route add -net %s netmask %s dev %s",
            net.toLatin1().data(),
            mask.toLatin1().data(),
            m_netName.toLatin1().data());
    system(cmdbuf);
#endif
    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "route add default gw %s netmask 0.0.0.0 dev %s",
            gw.toLatin1().data(),
            m_netName.toLatin1().data());
    system(cmdbuf);
    //system("route");
    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "echo nameserver %s > /etc/resolv.conf", dns.toLatin1().data());
    system(cmdbuf);
}

void QQTEthenetManager::setAddr(QString ip, QString mask, QString gw, QString dns)
{
    QSettings netSet;
    netSet.setValue("/Network/IP", ip);
    netSet.setValue("/Network/Gateway", gw);
    netSet.setValue("/Network/Mask", mask);
    netSet.setValue("/Network/DNS", dns);
    netSet.sync();
}

void QQTEthenetManager::getAddr(QString &ip, QString &mask, QString &gw, QString &dns)
{
    QSettings netSet;
    ip = netSet.value("/Network/IP").toString();
    mask = netSet.value("/Network/Mask").toString();
    gw = netSet.value("/Network/Gateway").toString();
    dns = netSet.value("/Network/DNS").toString();
}

void QQTDhcpThread::run()
{
    char cmdbuf[MAX_PATH];
    bzero(cmdbuf, MAX_PATH);
    sprintf(cmdbuf, "udhcpc -i %s", net.toLatin1().data());
    system(cmdbuf);
    emit passed(net);
}


void QQTNetworkClearThread::run()
{
    static bool _bclear = false;
    bool bclear = false;
    char cmdbuf[MAX_PATH];
    char cmdresult[MAX_PATH]; //设置一个合适的长度，以存储每一行输出
    bzero(cmdbuf, MAX_PATH);
    bzero(cmdresult, MAX_PATH);
    sprintf(cmdbuf, "ping 222.175.114.244 -w 2 -c 1");
    FILE *pp = popen(cmdbuf, "r"); //建立管道
    while(fgets(cmdresult, sizeof(cmdresult), pp))
    {
        if(strstr(cmdresult, "1 packets transmitted, 1 packets received, 0% packet loss"))
            bclear = true;
        break;
    }
    pclose(pp);

    if(_bclear != bclear)
    {
        if(bclear)
            emit cleared();
        else
            emit notcleared();
        _bclear = bclear;
    }

    return;
}
