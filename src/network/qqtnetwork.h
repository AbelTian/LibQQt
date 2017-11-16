#ifndef QQTNETWORKDEFINE_H
#define QQTNETWORKDEFINE_H

#include <QWidget>
#include <QUuid>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include <QElapsedTimer>
#include <QDesktopWidget>
#include <QDebug>
#include <qqt-local.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum
{
    ESSID_STATUS = 0,
    ESSID_NAME,//SSID
    ESSID_TYPE,
    ESSID_ENCRYP,
    ESSID_PASS,
    ESSID_BSSID,
    ESSID_FREQ,
    ESSID_SIGNAL,
    ESSID_FLAG,
    ESSID_MAX,
};


#ifdef __cplusplus
}
#endif  /* __cplusplus */


typedef struct QQTSHARED_EXPORT tagWifi
{
    QString wifi[ESSID_MAX];

    bool isValid();

#ifdef __EMBEDDED_LINUX__
    tagWifi& operator= (tagWifi& w);
#else
    tagWifi& operator=(const tagWifi& w);
#endif

    const QString& operator[](int index) const;

    QString& operator[](int index);
} TWifi;



#endif // QQTNETWORKDEFINE_H
