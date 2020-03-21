#ifndef QQTSTANDARDPROTOCOL_H
#define QQTSTANDARDPROTOCOL_H

#include <QObject>

#include <qqtdataserialization.h>
#include <qqtprotocol.h>

#include <qqt-local.h>
/**
 * @brief The QQtStandardProtocol class
 * LibQQt提供的标准协议类
 */
class QQTSHARED_EXPORT QQtStandardProtocol : public QQtProtocol
{
    Q_OBJECT

public:
    explicit QQtStandardProtocol ( QObject* parent = 0 )
        : QQtProtocol ( parent ) {}
    virtual ~QQtStandardProtocol() {}

    virtual void sendMessage ( const QQtDataSerialization& data ) {
        //已经序列化好buffer
#if 0
        QQtDataSerialization ds0 = data;
        ds0.serialize(); //数据本地化，补充一次序列化。
#else
        const QQtDataSerialization& ds0 = data;
#endif
        QByteArray bytes = ds0.buffer();
        write ( bytes );
    }

    virtual void recvMessage ( const QQtDataSerialization& data ) {
        //已经反序列化好buffer
        emit notifyToProtocolManager ( this, &data );
        emit readyRead ( data );
    }


signals:
    void readyRead ( const QQtDataSerialization& data );
protected:
private:


    // QQtProtocol interface
public:
    virtual quint16 minlength() override {
        QQtDataSerialization ds0;
        return ds0.minlength();
    }
    virtual quint16 maxlength() override {
        QQtDataSerialization ds0;
        return ds0.maxlength();
    }
    virtual quint16 splitter ( const QByteArray& _l ) override {
        QByteArray bytes = _l.left ( minlength() );
        quint16 header, size;
        bytes >> header >> size;
        return size;
    }
    virtual bool dispatcher ( const QByteArray& _l ) override {
        QQtDataSerialization ds1;
        ds1.buffer() = _l;
        ds1.unserialize();
        recvMessage ( ds1 );
    }
    virtual void initializer() override {
    }
};

#endif // QQTSTANDARDPROTOCOL_H

