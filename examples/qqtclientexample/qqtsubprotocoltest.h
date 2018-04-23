#ifndef QQTSUBPROTOCOLTEST_H
#define QQTSUBPROTOCOLTEST_H

#include <qqtprotocol.h>

class QQtSubProtocolTest : public QQtProtocol
{
    Q_OBJECT
public:
    QQtSubProtocolTest(QObject* parent = 0);
    // QQtProtocol interface
public:
    virtual quint16 minlength() override
    {
        return 16;
    }
    virtual quint16 splitter(const QByteArray&) override
    {
        return 14;
    }
};

#endif // QQTSUBPROTOCOLTEST_H
