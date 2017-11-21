/******************************************************************************
    Name: description
    Copyright (C) 2011-2015 Wang Bin <wbsecg1@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#ifndef QHOTPLUGWATCHER_H
#define QHOTPLUGWATCHER_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include "qdevicewatcher.h"
#include <QTimer>
#include <qqt-local.h>

#ifndef __GNUC__
#define __PRETTY_FUNCTION__  __FUNCTION__
#endif

class QQTSHARED_EXPORT QQtPluginWatcher : public QThread
{
    Q_OBJECT
public:
    static QQtPluginWatcher* Instance();

    enum
    {
        E_NULLDEV,
        E_MOUSE,
        E_KEYBOARD,
        E_STORAGE,
        E_MAXDEV,
    };

    enum
    {
        E_NULLSTAT,
        E_ADD,
        E_RM,
        E_CHANGE,
        E_MAXSTAT,
    };

    quint32 deviceType() { return m_devType; }
    quint32 deviceStat() { return m_devStat; }
    QString upanMountPath() { return m_storage; }
    QString printerFile() { return "/dev/usb/lp0"; }

signals:
    void storageChanged ( int stat );

public slots:
    void slotDeviceAdded ( const QString& dev );
    void slotDeviceRemoved ( const QString& dev );
    void slotDeviceChanged ( const QString& dev );
    void slotDeviceDriver();

protected:
    virtual bool event ( QEvent* e );

private:

private:
    QDeviceWatcher* watcher;
    explicit QQtPluginWatcher ( QObject* parent = 0 );
    static QQtPluginWatcher* _instance;
    quint32 m_devType;
    quint32 m_devStat;
    QString m_storage;
    QTimer* timer;
};

#endif // QHOTPLUGWATCHER_H
