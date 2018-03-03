#ifndef FILETRANSFERPROTOCOL_H
#define FILETRANSFERPROTOCOL_H

#include <QObject>
#include <qqtmessage.h>
#include <qqtprotocol.h>

class FiletransferMessage: public QQtMessage
{
    Q_OBJECT
public:
    explicit FiletransferMessage ( QObject* parent = 0 ) : QQtMessage ( parent ) {}


    // QQTMessage interface
public:
    virtual void parser ( const QByteArray& l ) override {
    }
    virtual void packer ( QByteArray& l ) const override {
    }
private:
    quint16 header;
    QByteArray body;
    quint32 tail;
};

class FiletransferProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit FiletransferProtocol ( QObject* parent = nullptr );

signals:

public slots:
};

#endif // FILETRANSFERPROTOCOL_H
