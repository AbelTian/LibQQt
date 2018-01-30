#include "cedianudpmessage.h"
#include <qqtcore.h>

CedianUdpMessage::CedianUdpMessage(QObject *parent) : QQtMessage(parent)
{
    qreal mVAA = 0;
    qreal mVAB = 0;
    qreal mVAC = 0;
    qreal mVPA = 0;
    qreal mVPB = 0;
    qreal mVPC = 0;
    qreal mIAA = 0;
    qreal mIAB = 0;
    qreal mIAC = 0;
    qreal mIPA = 0;
    qreal mIPB = 0;
    qreal mIPC = 0;
    qreal mFA = 0;
    qreal mFB = 0;
    qreal mFC = 0;
    QString mDateTime =0;

    mqbaVAA.clear();
    mqbaVAB.clear();
}


/*把测点发来的数据解出来*/
void CedianUdpMessage::parser(const QByteArray & data)
{
    QByteArray l = data;
    quint8 DataLen = 0, temp = 0, Month = 0, Day = 0, Hour = 0, Minute = 0, Second =0;
    quint16 Year = 0;
    //跳过包头 0-5
    for (int i=0; i<6 ;i++)
    {
        l >> temp;
        DataLen++;
    }
    //跳过空格 6
    l >> temp;
    DataLen++;
    //日 7-8
    l >> temp;
    mqbaDateTime << temp;
    Day = 10 * (temp - 0x30);
    l >> temp;
    mqbaDateTime << temp;
    Day = Day + (temp - 0x30);
    DataLen = DataLen + 2;
    //月 9-10
    l >> temp;
    mqbaDateTime << temp;
    Month = 10 * (temp - 0x30);
    l >> temp;
    mqbaDateTime << temp;
    Month = Month + (temp - 0x30);
    DataLen = DataLen + 2;
    //年 11-12
    l >> temp;
    mqbaDateTime << temp;
    Year = 10 * (temp - 0x30) + 2000;
    l >> temp;
    mqbaDateTime << temp;
    Year = Year + (temp - 0x30);
    DataLen = DataLen + 2;
    //跳过空格 13
    l >> temp;
    DataLen++;
    //时 14-15
    l >> temp;
    mqbaDateTime << temp;
    Hour = 10 * (temp - 0x30);
    l >> temp;
    mqbaDateTime << temp;
    Hour = Hour + (temp - 0x30);
    DataLen = DataLen + 2;
    //分 16-17
    l >> temp;
    mqbaDateTime << temp;
    Minute = 10 * (temp - 0x30);
    l >> temp;
    mqbaDateTime << temp;
    Minute = Minute + (temp - 0x30);
    DataLen = DataLen + 2;
    //秒 18-19
    l >> temp;
    mqbaDateTime << temp;
    Second = 10 * (temp - 0x30);
    l >> temp;
    mqbaDateTime << temp;
    Second = Second + (temp - 0x30);
    DataLen = DataLen + 2;
    //拼接并赋值给成员变量 年月日时分秒
    mDateTime = QString("%1-%2-%3 %4:%5:%6").arg(Year).arg(Month).arg(Day).arg(Hour).arg(Minute).arg(Second);
    //跳过空格 20
    l >> temp;
    DataLen++;
    //秒内标号 21-22
    l >> temp;
    mqbaBuffer << temp;
    mBuffer = 10 * (temp - 0x30);
    l >> temp;
    mqbaBuffer << temp;
    mBuffer = mBuffer + (temp - 0x30);
    DataLen = DataLen + 2;
    //跳过空格 23
    l >> temp;
    DataLen++;
    //频率mFA 24-30
    l >> temp;
    mqbaFA << temp;
    mFA = (temp - 0x30) * 100000;
    l >> temp;
    mqbaFA << temp;
    mFA = mFA + (temp - 0x30) * 10000;
    l >> temp; //小数点
    mqbaFA << temp;
    l >> temp;
    mqbaFA << temp;
    mFA = mFA + (temp - 0x30) * 1000;
    l >> temp;
    mqbaFA << temp;
    mFA = mFA + (temp - 0x30) * 100;
    l >> temp;
    mqbaFA << temp;
    mFA = mFA + (temp - 0x30) * 10;
    l >> temp;
    mqbaFA << temp;
    mFA = mFA + (temp - 0x30);
    mFA = mFA / 10000;
    DataLen = DataLen + 7;
    //跳过空格 31
    l >> temp;
    DataLen++;
    //频率弃用 32-38
    for (int i=0; i<7 ;i++)
    {
        l >> temp;
        DataLen++;
    }
    //跳过空格 39
    l >> temp;
    DataLen++;

    //电压幅值mVAA 40-45
    l >> temp;
    mqbaVAA << temp;
    mVAA = (temp - 0x30) * 10000;
    l >> temp;
    mqbaVAA << temp;
    mVAA = mVAA + (temp - 0x30) * 1000;
    l >> temp;
    mqbaVAA << temp;
    mVAA = mVAA + (temp - 0x30) * 100;
    l >> temp;  //小数点
    mqbaVAA << temp;
    l >> temp;
    mqbaVAA << temp;
    mVAA = mVAA + (temp - 0x30) * 10;
    l >> temp;
    mqbaVAA << temp;
    mVAA = mVAA + (temp - 0x30);
    mVAA = mVAA / 100;
    DataLen = DataLen + 6;

    //跳过空格 46
    l >> temp;
    DataLen++;
    //电压相位mVPA 47-51
    l >> temp;
    mqbaVPA << temp;
    mVPA = (temp - 0x30) * 1000;
    l >> temp;  //小数点
    mqbaVPA << temp;
    l >> temp;
    mqbaVPA << temp;
    mVPA = mVPA + (temp - 0x30) * 100;
    l >> temp;
    mqbaVPA << temp;
    mVPA = mVPA + (temp - 0x30) * 10;
    l >> temp;
    mqbaVPA << temp;
    mVPA = mVPA + (temp - 0x30);
    mVPA = mVPA / 1000;
    mVPA = mVPA * 57.296;
    DataLen = DataLen + 5;
    //跳过包尾 52-54
    for (int i=0; i<3 ;i++)
    {
        l >> temp;
        DataLen++;
    }
}

//监测点数据只有接收，没有发送，所以不需要实现packer函数
void CedianUdpMessage::packer(QByteArray & l) const
{
}

QDebug operator<<(QDebug dbg, const CedianUdpMessage &c)
{
    //    dbg.nospace() << "{" << hex << c.head() << "|" <<
    //                     hex << c.size() << "=" << dec << c.size() << "|" <<
    //                     hex << c.cmd() << "|" <<
    //                     hex << c.uid() << "|" <<
    //                     c.data().data() << "@" << dec << c.data().size() << "|" <<
    //                     hex << c.sum() << "|" <<
    //                     hex << c.tail() << "}";
    dbg.nospace() << "{" << hex << "}";
    return dbg.space();
}







