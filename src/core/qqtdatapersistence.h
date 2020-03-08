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
 * 如果文件不存在，将会自动创建文件。
 *
 * 原理：
 * 初始化数据格式、数据文件
 * 开启数据持久化功能，同时 根据数据格式读取数据文件初始化内部字典。
 * 有一个Timer，持续加锁读取内部字典，根据数据格式，保存到数据文件。
 * 用户可以持续加锁，读取、写入内部的字典。
 *
 * 注意事项：
 * 这个类对持久化存储数据文件的访问是非独占式，
 * 最后一次写文件者决定文件内容。
 *
 * 使用方法：
 * QQtDataPersistence keep_inst;
 * keep_inst.PrepareDataPersistence(); //打开持久化功能。once。
 *
 * keep_inst.start(); //开始持久化数据操作 每次操作都需要开启和关闭
 * QQtDictionary& handler = keep_inst.dictionary(); //可以操作的数据句柄
 * handler["key1"]["key2"] = "value1";
 * ...
 * keep_inst.stop(); //停止持久化数据操作
 *
 * keep_inst.ExitDataPersistence(); //退出持久化功能。普通buffer，不再保存数据。
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

    //持久化保存文件 [+初始化字典]
    void setDataFile ( const QString& fileName );
    QString dataFile() const;

    //打开数据持久化 [+初始化字典]
    void prepareDataPersistence();
    //关闭数据持久化
    void exitDataPersistence();

    //1! 开启
    void start();

    //2! 操作
    QQtDictionary& dictionary();

    //内外字典相同，就不会写文件，可以通过这里改变。
    //用户需要强制写入的时候。
    //内部字典使用了重载操作符技术，虽然方便了操作，可是某些需要代码实现的功能，不能自动实现，需要用户手动调用。比如：操作开关，强制写入。
    //为内存服务，内部不方便总是写文件，所以，麻烦用户有必要自己强制写入。
    void force_write();

    //3! 关闭
    void stop();

    //持久化数据保存周期 [default:1000ms]
    int timerInterval() const;
    void setTimerInterval ( int millSecond = 1000 );
private slots:
    void slotTimeOut();

protected:
    virtual void parseContentToDictionary();
    virtual void packDictionaryToContent ( QByteArray& bytes );

    //方便函数。文件不存在会创建。
    virtual void readFile ( QByteArray& bytes );
    virtual void writeFile ( const QByteArray& bytes );

private:
    QReadWriteLock mLock;
    QQtDictionary mDict;
    bool bForceWrite;

    QTimer* mTimer;
    int mTimerInterval;
    DataFormat mDataFormat;
    QString mFileName;
};

#endif // QQTDATAPERSISTENCE_H

