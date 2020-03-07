#ifndef QQTDATAPERSISTENCE_H
#define QQTDATAPERSISTENCE_H

#include <QObject>
#include <QTimer>
#include <QReadWriteLock>

#include <qqtdictionary.h>

#include <qqt-local.h>

/**
 * @brief The QQtDataPersistence class
 * 数据持久化类
 *
 * 支持：
 * 设置持久化保存间隔
 * 支持设置保存格式
 * 支持开启、关闭持久化功能，关闭后就是个普通的字典类
 *
 * 原理：
 * 初始化数据格式、数据文件
 * 开启数据持久化功能，同时 根据数据格式读取数据文件初始化内部字典。
 * 有一个Timer，持续加锁读取内部字典，根据数据格式，保存到数据文件。
 * 用户可以持续加锁，读取、写入内部的字典。
 *
 * 使用方法：
 * QQtDataPersistence keep_inst;
 * keep_inst.PrepareDataPersistence(); //打开持久化功能。
 * keep_inst.ExitDataPersistence(); //退出持久化功能。普通buffer，不保存数据。
 *
 * keep_inst.start(); //开始持久化数据操作 每次操作都需要开启和关闭
 * QQtDictionary& handler = keep_inst.dictionary(); //可以操作的数据句柄
 * handler["key1"]["key2"] = "value1";
 * ...
 * keep_inst.stop(); //停止持久化数据操作
 */
class QQTSHARED_EXPORT QQtDataPersistence : public QObject
{
    Q_OBJECT

public:
    explicit QQtDataPersistence ( QObject* parent = 0 );
    virtual ~QQtDataPersistence();

    enum DataFormat
    {
        JsonData,
        XmlData,
        YamlData,
        IniData,
        PropertiesData,

        MaxFormat
    };
    //数据格式
    void setDataFormat ( DataFormat format = JsonData );
    DataFormat dataFormat() const;

    //持久化保存文件
    void setDataFile ( const QString& fileName );
    QString dataFile() const;

    //打开数据持久化
    void prepareDataPersistence();
    //关闭数据持久化
    void exitDataPersistence();

    //1! 开启
    void start();

    //2! 操作
    QQtDictionary& dictionary();

    //3! 关闭
    void stop();

    //持久化数据保存周期 [default:1000ms]
    int timerInterval() const;
    void setTimerInterval ( int millSecond = 1000 );

private slots:
    void slotTimeOut();

protected:

private:
    QReadWriteLock mLock;
    QQtDictionary mDict;

    QTimer* mTimer;
    int mTimerInterval;
    DataFormat mDataFormat;
    QString mFileName;
};

#endif // QQTDATAPERSISTENCE_H

