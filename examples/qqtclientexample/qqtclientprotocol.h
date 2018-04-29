#ifndef QQTCLIENTPROTOCOL_H
#define QQTCLIENTPROTOCOL_H

#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqttcpserver.h>

class QQtClientMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtClientMessage ( QObject* parent = nullptr ) {
    }
    ~QQtClientMessage() {

    }

    quint16& getASize() {
        return asize;
    }
    const quint16& getASize() const {
        return asize;
    }

    quint8& getACmd() {
        return acmd;
    }
    const quint8& getACmd() const {
        return acmd;
    }
    QByteArray& getAData() {
        return adata;
    }
    const QByteArray& getAData() const {
        return adata;
    }

    quint16& getBSize() {
        return bsize;
    }
    const quint16& getBSize() const {
        return bsize;
    }

    quint8& getBCmd() {
        return bcmd;
    }
    const quint8& getBCmd() const {
        return bcmd;
    }
    QByteArray& getBData() {
        return bdata;
    }
    const QByteArray& getBData() const {
        return bdata;
    }

    void translate() {
        asize = 2 + 1 + adata.size();
    }


private:
    //发送格式
    quint16 asize;
    quint8 acmd;
    QByteArray adata;

    //接收格式
    quint8 bstart;
    quint16 bsize;
    quint8 bcmd;
    QByteArray bdata;
    quint8 bend;

    // QQtMessage interface
public:
    //把报文这条流解析出字段
    virtual void parser ( const QByteArray& l0 ) override {
        QByteArray l = l0;
        l >> bstart;
        l >> bsize;
        l >> bcmd;
        bdata.resize ( bsize - 1 - 2 - 1 - 1 );
        l >> bdata;
        l >> bend;
    }
    //把报文字段组装成流
    virtual void packer ( QByteArray& l ) const override {
        l << asize;
        l << acmd;
        l << adata;
    }
};

QDebug& operator << ( QDebug&, const QQtClientMessage& msg );


//业务层总是用这个协议工作，读来到的，写出去的。
class QQtClientProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtClientProtocol ( QObject* parent = nullptr ) {

    }
    ~QQtClientProtocol() {

    }

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand1 ( const QQtClientMessage& msg ) {
        //what do you want to do?
        pline() << msg.getBData();
        emit signalServerSay ( msg.getBData() );
    }
    void recvCommand2 ( const QQtClientMessage& msg ) {
        //what do you want to do?
        pline() << msg.getBData();
        emit signalServerSay ( msg.getBData() );
    }

    void sendA1Command ( QString data ) {
        QQtClientMessage msg;
        msg.getACmd() = 0x01;
        msg.getAData() = data.toLocal8Bit();
        msg.translate();

        QByteArray l;
        msg.packer ( l );
        write ( l );
    }

signals:
    //给业务层发的信号
    void signalServerSay ( QString h0 );

public slots:

    // QQtProtocol interface
protected:
    //报文的最小长度
    virtual quint16 minlength() override {
        return 0x03;
    }
    //报文的最大长度
    virtual quint16 maxlength() override {
        return 0x07FF;
    }

    virtual quint16 splitter ( const QByteArray& l ) override { //stream
        if ( l.size() < 3 )
            return 0;

        QByteArray s0 = l.left ( 3 );
        quint8 start = 0;
        quint16 size = 0;

        s0 >> start;
        s0 >> size;
        pline() << start << size;
        return size;
    }

    //报文现在被切开，发了进来，第二个字节是cmd，解析出来，在函数里处理处理数据，告诉业务层，拿到数据了干点什么。
    virtual bool dispatcher ( const QByteArray& m ) override { //message

        bool ret = true;

        QQtClientMessage qMsg;
        qMsg.parser ( m );
        pline() << qMsg;

        switch ( qMsg.getBCmd() ) {
            case 0x01://protocol command 1
                recvCommand1 ( qMsg );
                break;

            case 0x0A://protocol command 2
                recvCommand2 ( qMsg );
                break;

            default:
                ret = false;
                pline() << "receive unknown command:" << hex << qMsg.getBCmd();
                break;
        }

        return ret;
    }
};

//业务层初始化一下这个实例，总是从这里获取协议句柄进行对外读写。
QQtClientProtocol* QQtClientConnectionInstance ( QObject* parent = 0 );
QQtClientProtocol* QQtClientUdpConnectionInstance ( QObject* parent = 0 );

#endif // QQTCLIENTPROTOCOL_H
