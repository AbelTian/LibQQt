#include "qqtserialport.h"
#include "qqtcore.h"

QQTSerialPort::QQTSerialPort(QObject* parent) : QSerialPort(parent)
{
    //connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)) );
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()));
    //connect(this, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
    //connect(this, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
}

QQTSerialPort::~QQTSerialPort()
{
    if (isOpen())
        close();
}

void QQTSerialPort::installProtocol(QQtProtocol* stack)
{
    if (m_protocol)
        return;

    m_protocol = stack;
    connect(m_protocol, SIGNAL(write(const QByteArray&)), this, SLOT(write(const QByteArray&)));
}

void QQTSerialPort::uninstallProtocol(QQtProtocol* stack)
{
    Q_UNUSED(stack)
    if (!m_protocol)
        return;

    disconnect(m_protocol, SIGNAL(write(const QByteArray&)), this, SLOT(write(const QByteArray&)));
    m_protocol = NULL;
}

QQtProtocol* QQTSerialPort::installedProtocol()
{
    return m_protocol;
}

void QQTSerialPort::readyReadData()
{
    QByteArray bytes;
    bytes = readAll();
    m_protocol->translator(bytes);
}
