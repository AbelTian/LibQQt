#ifndef QQTSYSTEMINFO_H
#define QQTSYSTEMINFO_H

#include <QObject>
#include <qqt-local.h>
#include <qqtcore.h>

#if defined (Q_OS_WIN32) || defined( Q_OS_WIN64)
#pragma once
#pragma comment(lib,"Kernel32.lib")
#pragma comment(lib,"Psapi.lib")
#include <Windows.h>
#include <TlHelp32.h>
#include <direct.h>
#include <winternl.h>
#include <Psapi.h>
#endif
#include <QMap>


typedef struct tDiskInfo
{
    tDiskInfo() {}
    quint64 mSize; //B
    quint64 mAvalableSize; //B
} TDiskInfo;

typedef struct tDiskTable
{
    tDiskTable() {}
    quint64 mNum;
    QList<TDiskInfo> mList;
} TDiskTable;

typedef struct tMemInfo
{
    tMemInfo() {}
} TMemInfo;

typedef struct tMemTable
{
    tMemTable() {}
    quint64 mTotalSize;//B
    quint64 mAvalableSize;//B
    quint64 mNum;
    QList<TMemInfo> mList;
} TMemTable;

typedef struct tCPUInfo
{
    tCPUInfo() {}
    quint64 mCoreNum;
    quint64 mThreadNumPerCore;
    quint64 mRate;
} TCPUInfo;

typedef struct tCPUTable
{
    tCPUTable() {}
    quint64 mNum;
    QList<TCPUInfo> mList;
} TCPUTable;

class QQTSHARED_EXPORT QQtSystemInfo : public QObject
{
    Q_OBJECT
public:
    explicit QQtSystemInfo ( QObject* parent = nullptr );

    bool getCPUInfo ( TCPUTable& cpuInfo ) {
#if defined(Q_OS_WIN)
        SYSTEM_INFO systemInfo;
        GetSystemInfo ( &systemInfo );

        TCPUInfo info;
        info.mCoreNum = systemInfo.dwNumberOfProcessors;
        cpuInfo.mNum = 1;
        cpuInfo.mList.push_back ( info );

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
            return true;
    }
    bool getMEMInfo ( TMemTable& memInfo ) {
#if defined (Q_OS_WIN)
#define MB (1024 * 1024)
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof ( statex );
        GlobalMemoryStatusEx ( &statex );

        memInfo.mTotalSize = statex.ullTotalPhys;
        memInfo.mAvalableSize = statex.ullAvailPhys;
        memInfo.mNum = 1;

        qDebug() << QStringLiteral ( "物理内存使用率:" ) << statex.dwMemoryLoad;
        qDebug() << QStringLiteral ( "物理内存总量:" ) << statex.ullTotalPhys / MB;
        qDebug() << QStringLiteral ( "可用的物理内存:" ) << statex.ullAvailPhys / MB;
        qDebug() << QStringLiteral ( "系统页面文件大小:" ) << statex.ullTotalPageFile / MB;
        qDebug() << QStringLiteral ( "系统可用页面文件大小:" ) << statex.ullAvailPageFile / MB;
        qDebug() << QStringLiteral ( "虚拟内存总量:" ) << statex.ullTotalVirtual / MB;
        qDebug() << QStringLiteral ( "可用的虚拟内存:" ) << statex.ullAvailVirtual / MB;
        qDebug() << QStringLiteral ( "保留（值为0）:" ) << statex.ullAvailExtendedVirtual / MB;
#else
#endif
        return true;
    }
    bool getDiskInfo ( TDiskTable& diskInfo ) {
#if defined (Q_OS_WIN)

#else
#endif
        return true;
    }

signals:

public slots:

private:
};

#endif // QQTSYSTEMINFO_H
