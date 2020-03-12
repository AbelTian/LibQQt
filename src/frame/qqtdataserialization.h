#ifndef QQTDATASERIALIZATION_H
#define QQTDATASERIALIZATION_H

#include <QObject>

#include <qqtdictionary.h>

#include <qqt-local.h>
/**
 * @brief The QQtDataSerialization class
 * 数据序列化、反序列化
 *
 * 原理：
 * 内部有QByteArray，按照以下格式，通过serialize/unserialize序列化到QByteArray里，和从QByteArray里反序列化到内部字典里。
 *
 * Buffer:
 * |quint32 header|quint32 size|quint8* json_data|quint32 checksum|quint32 tail|
 * 内部字典，不建议用户使用:
 * dict[0-...]=Value;
 * data段保存的是压缩的json结构数据，用户通过此类提供的操作符更改内容。
 */
class QQTSHARED_EXPORT QQtDataSerialization : public QObject
{
    Q_OBJECT

public:
    explicit QQtDataSerialization ( QObject* parent = 0 )
        : QObject ( parent ) {}
    virtual ~QQtDataSerialization() {}

    /**
     * <<
     **/
    QQtDataSerialization& operator<< ( std::nullptr_t ) { return *this; }

    QQtDataSerialization& operator<< ( bool i );
    QQtDataSerialization& operator<< ( float f );
    QQtDataSerialization& operator<< ( double f );
    QQtDataSerialization& operator<< ( const char* str );

    QQtDataSerialization& operator<< ( quint8 i );
    QQtDataSerialization& operator<< ( quint16 i );
    QQtDataSerialization& operator<< ( quint32 i );
    QQtDataSerialization& operator<< ( quint64 i );

    QQtDataSerialization& operator<< ( qint8 i );
    QQtDataSerialization& operator<< ( qint16 i );
    QQtDataSerialization& operator<< ( qint32 i );
    QQtDataSerialization& operator<< ( qint64 i );

    QQtDataSerialization& operator<< ( qfloat16 f );
    QQtDataSerialization& operator<< ( qreal r );

    /**
     * >>
     **/
    QQtDataSerialization& operator>> ( std::nullptr_t& ptr ) { ptr = nullptr; return *this; }

    QQtDataSerialization& operator>> ( bool& i );
    QQtDataSerialization& operator>> ( float& f );
    QQtDataSerialization& operator>> ( double& f );
    QQtDataSerialization& operator>> ( char*& str );

    QQtDataSerialization& operator>> ( qint8& i );
    QQtDataSerialization& operator>> ( qint16& i );
    QQtDataSerialization& operator>> ( qint32& i );
    QQtDataSerialization& operator>> ( qint64& i );

    QQtDataSerialization& operator>> ( quint8& i );
    QQtDataSerialization& operator>> ( quint16& i );
    QQtDataSerialization& operator>> ( quint32& i );
    QQtDataSerialization& operator>> ( quint64& i );

    QQtDataSerialization& operator>> ( qfloat16& f );
    QQtDataSerialization& operator>> ( qreal& r );

    QQtDataSerialization& operator>> ( QImage& f );

    void serialize(){
        quint32 header = 0x77EE;
        quint32 size = 0;
        QByteArray json_data;
        quint32 checksum = 0;
        quint32 tail = 0x77FF;

        json_data = mDict.toJson(QJsonDocument::Compact);
        size = 4 + 4 + json_data.size() + 4 + 4;
        for(int i = 0; i < json_data.size(); i++){
            char check = json_data.data()[i];
            if(checksum +check>0x77FFFFFF)
                checksum = 0;
            checksum = checksum + (int)check;
        }
        QByteArray& bytes = mBytes;
        bytes << header << size << json_data << checksum << tail;
    }
    void unserialize(){
        quint32 header = 0x77EE;
        quint32 size = 0;
        QByteArray json_data;
        quint32 checksum = 0;
        quint32 tail = 0x77FF;

        QByteArray& bytes = mBytes;
        bytes >> header >> size;
        int json_size = size - (4 + 4 + 4 + 4);
        json_data.resize(json_size);
        bytes >> json_data;
        bytes >> checksum >> tail;

        QQtDictionary& dict = mDict;
        dict.fromJson(json_data);
    }

    //输入、输出
    QByteArray& data() { return mBytes; }
    const QByteArray& data() const { return mBytes; }

    /**
     * operator [] 操作第几个字段
     */
    QQtDictionary& operator[] ( int index ) {
        return mDict[index];
    }
    //直接操作 [0-][...]
    //QQtDictionary& dictionary() { return mDict; }
    //const QQtDictionary& dictionary() const { return mDict; }

    void dump();
    void clear();
    void seek(int index);
protected:

private:
    QQtDictionary mDict;
    quint32 mIndex;

    QByteArray mBytes;
};

#endif // QQTDATASERIALIZATION_H

