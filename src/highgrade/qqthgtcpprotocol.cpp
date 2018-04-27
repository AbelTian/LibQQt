#include "qqthgtcpprotocol.h"

QQtHgTcpProtocol::QQtHgTcpProtocol ( QObject* parent ) : QQtHgProtocol ( parent )
{

}

QQtHgTcpProtocol::~QQtHgTcpProtocol()
{

}


void QQtHgTcpProtocol::translator ( const QAbstractSocket* client, QByteArray& bytes )
{
    // queued conn and queued package;
    // direct conn and direct package;
    QByteArray& sqbaBlockOnNet = clientBuffer() [client];
    sqbaBlockOnNet += bytes;
    //qint64 aaa = bytesAvailable();
    //pline() << aaa;

    do
    {
        quint16 nBlockLen = this->splitter ( sqbaBlockOnNet );

        pmeta() << sqbaBlockOnNet.size() << "..." << nBlockLen;

        if ( sqbaBlockOnNet.length() < nBlockLen || nBlockLen < minlength() )
        {
            /*
             * 收到数据不足或者解析包长小于最小包长
             */
            return;
        }
        else if ( nBlockLen > maxlength() )
        {
            /*
             * 数据包长超过了最大长度
             */
            sqbaBlockOnNet.clear();
            pmeta() << "forbidden package" << sqbaBlockOnNet.length() << nBlockLen;
            return;
        }
        else if ( sqbaBlockOnNet.length() > nBlockLen )
        {
            /*
             * 粘包
             * 还没有处理完毕，数据已经接收到，异步信号处理出现这种异常
             * 疑问:如果异步调用这个函数绘出现什么问题？正常情况，同步获取数据，异步处理；检测异步获取并且处理会有什么状况
             */
            pmeta() << "stick package" << sqbaBlockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize ( nBlockLen );
            sqbaBlockOnNet >> netData;
            dispatcher ( client, netData );
            emit notifyForDispatcher ( client, netData );
            continue;
        }

        /*
         * 正常分发
         */
        dispatcher ( client, sqbaBlockOnNet );
        emit notifyForDispatcher ( client, sqbaBlockOnNet );
        break;
    } while ( 1 );

    sqbaBlockOnNet.clear();
}
