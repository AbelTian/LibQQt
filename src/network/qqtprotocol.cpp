#include "qqtprotocol.h"

QQtProtocol::QQtProtocol(QObject *parent) : QObject(parent)
{

}

QQtProtocol::~QQtProtocol()
{

}

#define pline2() pline() << metaObject()->className()

void QQtProtocol::translator(const QByteArray &bytes)
{
    // queued conn and queued package;
    // direct conn and direct package;

    static QByteArray sqbaBlockOnNet;
    sqbaBlockOnNet += bytes;
    //qint64 aaa = bytesAvailable();
    //pline() << aaa;

    do
    {
        quint16 nBlockLen = this->splitter(sqbaBlockOnNet);

        pline2() << sqbaBlockOnNet.size() << "..." << nBlockLen;

        if (sqbaBlockOnNet.length() < nBlockLen || nBlockLen < minlength())
        {
            /*
             * 收到数据不足或者解析包长小于最小包长
             */
            return;
        }
        else if (nBlockLen > maxlength())
        {
            /*
             * 数据包长超过了最大长度
             */
            sqbaBlockOnNet.clear();
            pline2() << "forbidden package" << sqbaBlockOnNet.length() << nBlockLen;
            return;
        }
        else if (sqbaBlockOnNet.length() > nBlockLen)
        {
            /*
             * 粘包
             * 还没有处理完毕，数据已经接收到，异步信号处理出现这种异常
             * 疑问:如果异步调用这个函数绘出现什么问题？正常情况，同步获取数据，异步处理；检测异步获取并且处理会有什么状况
             */
            pline2() << "stick package" << sqbaBlockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize(nBlockLen);
            sqbaBlockOnNet >> netData;
            dispatcher(netData);
            continue;
        }
        /*
         * 正常分发
         */
        dispatcher(sqbaBlockOnNet);
        break;
    }
    while (1);

    sqbaBlockOnNet.clear();
}
