#ifndef QQTWEBCLIENT_H
#define QQTWEBCLIENT_H

#include <QtWebSockets/QWebSocket>
#include <qqtcore.h>
/**
 * @brief The QQtWebClient class
 * QQtWebSocketClient通过安装QQtWebProtocol来实现和RawSocket相似的通信方式。
 * 暂时不确定QQtWebProtocol是否和QQtProtocol格式相同，所以暂时使用QQtWebProtocol继承QQtProtocol。
 */
class QQtWebSocketClient : public QWebSocket
{
    Q_OBJECT
public:
    explicit QQtWebSocketClient ( QObject* parent = nullptr,
                                  const QString& origin = QString(),
                                  QWebSocketProtocol::Version version = QWebSocketProtocol::VersionLatest );

signals:

public slots:

private:
};

#endif // QQTWEBCLIENT_H
