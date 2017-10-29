#ifndef QQTWEBCLIENT_H
#define QQTWEBCLIENT_H

#include <QtWebSockets/QWebSocket>

class QQtWebClient : public QWebSocket
{
    Q_OBJECT
public:
    explicit QQtWebClient(QObject* parent = nullptr,
                          const QString& origin = QString(),
                          QWebSocketProtocol::Version version = QWebSocketProtocol::VersionLatest);

signals:

public slots:

private:
};

#endif // QQTWEBCLIENT_H
