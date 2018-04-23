#include "qqtuserprotocol3.h"

QDebug& operator << ( QDebug& dbg, const QQtUserMessage3& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtUserProtocol3* QQtUserConnectionInstance3 ( QObject* parent )
{
    static QQtUserProtocol3* p0 = NULL;
    static QQtSerialPort* s0 = NULL;
    if ( !p0 && !s0 )
    {
        p0 = new QQtUserProtocol3 ( parent );

        s0 = new QQtSerialPort ( parent );
        s0->setPortName ( "/dev/ttyUSB0" );
        s0->setBaudRate ( QQtSerialPort::Baud57600 );
        s0->setDataBits ( QQtSerialPort::Data8 );
        s0->setParity ( QQtSerialPort::NoParity );
        s0->setStopBits ( QQtSerialPort::OneStop );
        s0->setFlowControl ( QQtSerialPort::NoFlowControl );
        s0->open ( QQtSerialPort::ReadWrite );
        s0->installProtocol ( p0 );

    }

    return p0;
}
