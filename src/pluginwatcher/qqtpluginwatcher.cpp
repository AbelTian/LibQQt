
#include "qqtpluginwatcher.h"

#ifdef __QT4__
#include <QWSServer>
#include <QMouseDriverFactory>
#endif

QQtPluginWatcher* QQtPluginWatcher::_instance = NULL;
QQtPluginWatcher::QQtPluginWatcher(QObject* parent) :
    QThread(parent)
{
    m_devType = E_NULLDEV;
    m_devStat = E_NULLSTAT;
    m_storage = "/mnt/usb_sda1";

    //qDebug("tid=%#x %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__);
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotDeviceDriver()), Qt::DirectConnection);

    start();

    moveToThread(this); //Let bool event(QEvent *e) be in another thread
    watcher = new QDeviceWatcher;
    watcher->moveToThread(this);
    watcher->appendEventReceiver(this);
    connect(watcher, SIGNAL(deviceAdded(QString)), this, SLOT(slotDeviceAdded(QString)), Qt::DirectConnection);
    connect(watcher, SIGNAL(deviceChanged(QString)), this, SLOT(slotDeviceChanged(QString)), Qt::DirectConnection);
    connect(watcher, SIGNAL(deviceRemoved(QString)), this, SLOT(slotDeviceRemoved(QString)), Qt::DirectConnection);
    watcher->start();
}

QQtPluginWatcher* QQtPluginWatcher::Instance()
{
    if (_instance)
        return _instance;

    _instance = new QQtPluginWatcher();
    return _instance;
}

void QQtPluginWatcher::slotDeviceAdded(const QString& dev)
{
    qDebug("tid=%#llx %s: add %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));

    if ("/dev/input/event1" == dev)
        m_devType = E_MOUSE;
    else if ("/dev/input/event2" == dev)
        m_devType = E_KEYBOARD;
    else if ("/dev/sda1" == dev)
        m_devType = E_STORAGE;

    m_devStat = E_ADD;
    timer->start(1000);
}

void QQtPluginWatcher::slotDeviceRemoved(const QString& dev)
{
    qDebug("tid=%#llx %s: remove %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));
    m_devStat = E_RM;
    timer->start(1000);
}

void QQtPluginWatcher::slotDeviceChanged(const QString& dev)
{
    qDebug("tid=%#llx %s: change %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));
}

void QQtPluginWatcher::slotDeviceDriver()
{
#ifdef __EMBEDDED_LINUX__

    if (E_MOUSE == m_devType)
    {
        if (E_ADD == m_devStat)
            QWSServer::setCursorVisible(true);
        else if (E_RM == m_devStat)
            QWSServer::setCursorVisible(false);
    }
    else if (E_STORAGE == m_devType)
    {
        if (E_ADD == m_devStat)
            emit storageChanged(E_ADD);
        else if (E_RM == m_devStat)
            emit storageChanged(E_RM);
    }
    else
#endif
        if (E_KEYBOARD == m_devType)
            return;
}

bool QQtPluginWatcher::event(QEvent* e)
{
    if (e->type() == QDeviceChangeEvent::registeredType())
    {
        QDeviceChangeEvent* event = (QDeviceChangeEvent*)e;
        QString action("Change");

        if (event->action() == QDeviceChangeEvent::Add)
            action = "Add";
        else if (event->action() == QDeviceChangeEvent::Remove)
            action = "Remove";

        //qDebug("tid=%#x event=%d %s: %s %s", (quintptr)QThread::currentThreadId(), e->type(), __PRETTY_FUNCTION__, qPrintable(action), qPrintable(event->device()));
        event->accept();
        return true;
    }

    return QObject::event(e);
}
