#ifndef QQTHGWEBCLIENT_H
#define QQTHGWEBCLIENT_H

#include <QtWebSockets/QWebSocket>
#include <qqtcore.h>
#include <qqt-local.h>

/**
 * @brief The QQtHgWebSocketClient class
 * QQtHgWebSocketClient 通过安装QQtHgWebProtocol来实现和RawSocket相似的通信方式。
 * 暂时不确定QQtHgWebProtocol是否和QQtHgProtocol格式相同，所以暂时使用QQtHgWebProtocol继承QQtHgProtocol。
 */
class QQTSHARED_EXPORT QQtHgWebSocketClient : public QWebSocket
{
    Q_OBJECT
public:
    explicit QQtHgWebSocketClient ( QObject* parent = nullptr,
                                    const QString& origin = QString(),
                                    QWebSocketProtocol::Version version = QWebSocketProtocol::VersionLatest );

signals:

public slots:

private:
};

#endif // QQTHGWEBCLIENT_H
