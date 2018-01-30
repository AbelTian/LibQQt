#include "kongzhiqiudpmessage.h"

KongzhiqiUdpMessage::KongzhiqiUdpMessage(QObject *parent) : QQtMessage(parent)
{
    quint8 mDesType = 1;
    quint8 mCommand = 0;
}

//控制器数据没有数据接收，只有控制命令发送，所以不需要实现parser函数
void KongzhiqiUdpMessage::parser(const QByteArray &)
{

}

//控制命令组包packer函数
void KongzhiqiUdpMessage::packer(QByteArray & command) const
{
    //写入包头 0-5
    command << 0x31;
    command << 0x20;
    command << 0x30;
    command << 0x30;
    command << 0x33;
    command << 0x30;
    //写入空格 6
    command << 0x20;
    //写入目标控制器类型 7-8
    command << 0x30;
    command << (mDesType + 0x30);
    //写入控制命令 9-10
    command << 0x30;
    command << (mCommand + 0x30);
    //写入包尾 11-13
    command << 0x31;
    command << 0x31;
    command << 0x31;
}
