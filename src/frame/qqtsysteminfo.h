#ifndef QQTSYSTEMINFO_H
#define QQTSYSTEMINFO_H

#include <QObject>

typedef struct tDiskInfo
{
    tDiskInfo() {}
    quint32 mSize; //B
    quint32 mAvalableSize; //B
} TDiskInfo;

typedef struct tDiskTable
{
    tDiskTable() {}
    quint32 mNum;
    QList<TDiskInfo> mList;
} TDiskTable;

typedef struct tMemInfo
{
    tMemInfo() {}
} TMemInfo;

typedef struct tMemTable
{
    tMemTable() {}
    quint32 mTotalSize;//B
    quint32 mAvalableSize;//B
    quint32 mNum;
    QList<TMemInfo> mList;
} TMemTable;

typedef struct tCPUInfo
{
    tCPUInfo() {}
    quint32 mCoreNum;
    quint32 mThreadNumPerCore;
    quint32 mRate;
} TCPUInfo;

typedef struct tCPUTable
{
    tCPUTable() {}
    quint32 mNum;
    QList<TCPUInfo> mList;
} TCPUTable;

class QQtSystemInfo : public QObject
{
    Q_OBJECT
public:
    explicit QQtSystemInfo ( QObject* parent = nullptr );

    bool getCPUInfo ( TCPUTable& cpuInfo ) {
#if 0
#if defined(Q_OS_WIN32) || defined (Q_OS_WIN64)
        SYSTEM_INFO systemInfo;
        GetSystemInfo ( &systemInfo );
        qDebug() << QStringLiteral ( "处理器掩码:" ) << systemInfo.dwActiveProcessorMask;
        qDebug() << QStringLiteral ( "处理器个数:" ) << systemInfo.dwNumberOfProcessors;
        qDebug() << QStringLiteral ( "处理器分页大小:" ) << systemInfo.dwPageSize;
        qDebug() << QStringLiteral ( "处理器类型:" ) << systemInfo.dwProcessorType;
        qDebug() << QStringLiteral ( "最大寻址单元:" ) << systemInfo.lpMaximumApplicationAddress;
        qDebug() << QStringLiteral ( "最小寻址单元:" ) << systemInfo.lpMinimumApplicationAddress;
        qDebug() << QStringLiteral ( "处理器等级:" ) << systemInfo.wProcessorLevel;
        qDebug() << QStringLiteral ( "处理器版本:" ) << systemInfo.wProcessorRevision;
#else

#endif
#endif
    }
signals:

public slots:

private:
};

#endif // QQTSYSTEMINFO_H
