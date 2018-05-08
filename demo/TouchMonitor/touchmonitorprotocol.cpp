#include "touchmonitorprotocol.h"

QDebug& operator << ( QDebug& dbg, const TouchMonitorMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << hex << msg.cmd() << oct << msg.x() << msg.y() << "}";
    return dbg.space();
}
