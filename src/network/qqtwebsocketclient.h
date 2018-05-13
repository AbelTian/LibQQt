#ifndef QQTWEBSOCKETCLIENT_H
#define QQTWEBSOCKETCLIENT_H

#include <QtWebSockets/QWebSocket>
#include <qqtprotocol.h>
#include <qqtcore.h>
#include <qqt-local.h>

/**
 * @brief The QQtWebSocketClient class
 * QQtWebSocketClient通过安装QQtProtocol来实现和RawSocket相似的通信方式。
 */
class QQTSHARED_EXPORT QQtWebSocketClient : public QWebSocket
{
    Q_OBJECT
public:
    explicit QQtWebSocketClient ( QObject* parent = nullptr,
                                  const QString& origin = QString(),
                                  QWebSocketProtocol::Version version = QWebSocketProtocol::VersionLatest );

    void installProtocol ( QQtProtocol* stack );
    void uninstallProtocol ( QQtProtocol* stack );
    QQtProtocol* installedProtocol();

signals:

private slots:
    void slotReadData ( const QByteArray& bytes );
    void slotWriteData ( const QByteArray& bytes );

protected:
    /**
     * @brief translator
     * 用于拆分和分发数据报
     * @param bytes
     */
    virtual void translator ( const QByteArray& bytes );

private:
    QQtProtocol* m_protocol;
};

#endif // QQTWEBSOCKETCLIENT_H
