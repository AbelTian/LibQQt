#include "qqtserialport.h"
#include "qqtcore.h"

QQtSerialPort::QQtSerialPort(QObject* parent) : QSerialPort(parent)
{
    //connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)) );
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()));
    //connect(this, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
    //connect(this, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
}

QQtSerialPort::~QQtSerialPort()
{
    if (isOpen())
        close();
}

void QQtSerialPort::installProtocol(QQtProtocol* stack)
{
    if (m_protocol)
        return;

    m_protocol = stack;
    connect(m_protocol, SIGNAL(write(const QByteArray&)), this, SLOT(write(const QByteArray&)));
}

void QQtSerialPort::uninstallProtocol(QQtProtocol* stack)
{
    Q_UNUSED(stack)

    if (!m_protocol)
        return;

    disconnect(m_protocol, SIGNAL(write(const QByteArray&)), this, SLOT(write(const QByteArray&)));
    m_protocol = NULL;
}

QQtProtocol* QQtSerialPort::installedProtocol()
{
    return m_protocol;
}

void QQtSerialPort::readyReadData()
{
    QByteArray bytes;
    bytes = readAll();
    m_protocol->translator(bytes);
}
