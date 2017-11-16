#include "qqtnetwork.h"


bool tagWifi::isValid()
{
    return wifi[ESSID_BSSID].isEmpty() ? false : true;
}

#ifdef __EMBEDDED_LINUX__
tagWifi& tagWifi::operator= (tagWifi& w)
#else
tagWifi& tagWifi::operator=(const tagWifi& w)
#endif
{
    for (int i = ESSID_STATUS; i < ESSID_MAX; i++)
        wifi[i] = w[i];

    return *this;
}

QString& tagWifi::operator[](int index)
{
    if (index < ESSID_STATUS || index >= ESSID_MAX)
        return wifi[0];

    return wifi[index];
}

const QString& tagWifi::operator[](int index) const
{
    return operator [](index);
}
