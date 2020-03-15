#ifndef QQTDATASERIALIZATION_H
#define QQTDATASERIALIZATION_H

#include <QObject>

#include <qqtmessage.h>
#include <qqtdictionary.h>

#include <qqt-local.h>
/**
 * @brief The QQtDataSerialization class
 * LibQQt提供的标准报文类，数据序列化、反序列化
 *
 * 原理：
 * Buffer ---- Dict ---- Buffer
 * 内部有QByteArray，按照以下格式，
 * 可以通过serialize/unserialize序列化到QByteArray里，和从QByteArray里反序列化到内部字典里。
 *
 * Buffer:
 * |quint16 header|quint16 size|quint8* json_data|quint16 checksum|quint16 tail|
 * 内部字典，不建议用户使用:
 * dict["Root"][0-N]=Value;
 * data段保存的是压缩的json结构数据，用户通过此类提供的操作符更改内容。
 *
 */
class QQTSHARED_EXPORT QQtDataSerialization : public QQtMessage
{
    Q_OBJECT

public:
    explicit QQtDataSerialization ( QObject* parent = 0 );
    virtual ~QQtDataSerialization() {}

    QQtDataSerialization ( const QQtDataSerialization& other ) {
        *this = other;
    }
    QQtDataSerialization& operator= ( const QQtDataSerialization& other ) {
        this->buffer() = other.buffer();
        this->dictionary() = other.dictionary();
        return *this;
    }

    //设置value
    template <typename T>
    void addValue ( const T& value ) {
        mDict["Root"][mIndex++].setValue<T> ( value );
    }
    /*自己本身没有孩子，是个叶子，添加值*/
    void addValue ( const QVariant& value ) {
        mDict["Root"][mIndex++].setValue ( value );
    }

    template <typename T>
    QQtDataSerialization& operator = ( const T& value ) {
        mDict["Root"][mIndex++].setValue<T> ( value );
        return *this;
    }
    QQtDataSerialization& operator = ( const QVariant& value ) {
        mDict["Root"][mIndex++].setValue ( value );
        return *this;
    }
    bool operator == ( const QQtDataSerialization& other ) {
        if ( mDict == other.dictionary() && mBytes == other.buffer() )
            return true;
        return false;
    }

    /**
     * <<
     **/
    QQtDataSerialization& operator<< ( std::nullptr_t ) { return *this; }

    QQtDataSerialization& operator<< ( const bool& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }
    QQtDataSerialization& operator<< ( const float& f ) {
        mDict["Root"][mIndex++] = f;
        return *this;
    }
    QQtDataSerialization& operator<< ( const double& f ) {
        mDict["Root"][mIndex++] = f;
        return *this;
    }


    QQtDataSerialization& operator<< ( const quint8& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }
    QQtDataSerialization& operator<< ( const quint16& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }
    QQtDataSerialization& operator<< ( const quint32& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }
    QQtDataSerialization& operator<< ( const quint64& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }

    QQtDataSerialization& operator<< ( const qint8& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }
    QQtDataSerialization& operator<< ( const qint16& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }
    QQtDataSerialization& operator<< ( const qint32& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }
    QQtDataSerialization& operator<< ( const qint64& i ) {
        mDict["Root"][mIndex++] = i;
        return *this;
    }

    QQtDataSerialization& operator<< ( const char* b ) {
        QByteArray bytes;
        bytes.resize ( qstrlen ( b ) );
        memcpy ( bytes.data(), b, qstrlen ( b ) );
        mDict["Root"][mIndex++] = bytes;
        return *this;
    }
    QQtDataSerialization& operator<< ( const QByteArray& b ) {
        mDict["Root"][mIndex++] = b;
        return *this;
    }
    QQtDataSerialization& operator<< ( const QString& b ) {
        mDict["Root"][mIndex++] = b;
        return *this;
    }
    QQtDataSerialization& operator<< ( const QImage& f ) {
        QByteArray bytes;
        bytes.resize ( f.byteCount() );
        memcpy ( bytes.data(), f.bits(), f.byteCount() );
        mDict["Root"][mIndex++] = bytes;
        return *this;
    }

    template <typename T>
    QQtDataSerialization& operator<< ( const T& b ) {
        mDict["Root"][mIndex++] = b;
        return *this;
    }
    QQtDataSerialization& operator<< ( const QVariant& b ) {
        mDict["Root"][mIndex++] = b;
        return *this;
    }

    /**
     * >>
     **/
    QQtDataSerialization& operator>> ( std::nullptr_t& ptr ) { ptr = nullptr; return *this; }

    QQtDataSerialization& operator>> ( bool& i ) {
        i = mDict["Root"][mIndex++].getValue().toBool();
        return *this;
    }
    QQtDataSerialization& operator>> ( float& f ) {
        f = mDict["Root"][mIndex++].getValue().toFloat();
        return *this;
    }
    QQtDataSerialization& operator>> ( double& f ) {
        f = mDict["Root"][mIndex++].getValue().toDouble();
        return *this;
    }

    QQtDataSerialization& operator>> ( qint8& i ) {
        i = mDict["Root"][mIndex++].getValue().toInt();
        return *this;
    }
    QQtDataSerialization& operator>> ( qint16& i ) {
        i = mDict["Root"][mIndex++].getValue().toInt();
        return *this;
    }
    QQtDataSerialization& operator>> ( qint32& i ) {
        i = mDict["Root"][mIndex++].getValue().toInt();
        return *this;
    }
    QQtDataSerialization& operator>> ( qint64& i ) {
        i = mDict["Root"][mIndex++].getValue().toLongLong();
        return *this;
    }

    QQtDataSerialization& operator>> ( quint8& i ) {
        i = mDict["Root"][mIndex++].getValue().toUInt();
        return *this;
    }
    QQtDataSerialization& operator>> ( quint16& i ) {
        i = mDict["Root"][mIndex++].getValue().toUInt();
        return *this;
    }
    QQtDataSerialization& operator>> ( quint32& i ) {
        i = mDict["Root"][mIndex++].getValue().toUInt();
        return *this;
    }
    QQtDataSerialization& operator>> ( quint64& i ) {
        i = mDict["Root"][mIndex++].getValue().toULongLong();
        return *this;
    }

    QQtDataSerialization& operator>> ( QByteArray& b ) {
        b = mDict["Root"][mIndex++].getValue().toByteArray();
        return *this;
    }
    QQtDataSerialization& operator>> ( QString& b ) {
        b = mDict["Root"][mIndex++].getValue().toString();
        return *this;
    }
    QQtDataSerialization& operator>> ( QImage& f ) {
        QByteArray bytes;
        bytes = mDict["Root"][mIndex++].getValue().toByteArray();
        f.loadFromData ( bytes );
        return *this;
    }

    template <typename T>
    QQtDataSerialization& operator>> ( T& b ) {
        b = mDict["Root"][mIndex++].getValue().value<T>();
        return *this;
    }
    QQtDataSerialization& operator>> ( QVariant& b ) {
        b = mDict["Root"][mIndex++].getValue();
        return *this;
    }

    /**
     * operator [] 直接操作构成json_data的数据字典
     */
    QQtDictionary& operator[] ( int index ) { return mDict["Root"][index]; }
    const QQtDictionary& operator[] ( int index ) const { return mDict["Root"][index]; }

    //输入、输出
    QByteArray& buffer() { return mBytes; }
    const QByteArray& buffer() const { return mBytes; }

    //直接操作 ["Root"][0-N][...] = value
    QQtDictionary& dictionary() { return mDict; }
    const QQtDictionary& dictionary() const { return mDict; }

    //手动packer()/parser()
    void serialize() {
        packer ( mBytes );
    }
    void unserialize() {
        parser ( mBytes );
    }

    void clear();
    void seek ( int index );
    int pos();
    int length();
    void dump();
    void dump_dictionary();

public:
    virtual quint16 minlength() const override {
        return 0x04;
    }
    virtual quint16 maxlength() const override {
        return 0x77FF;
    }
    virtual void packer ( QByteArray& l ) const override;
    virtual void parser ( const QByteArray& _l ) override;

protected:

private:
    QQtDictionary mDict;
    quint32 mIndex;

    QByteArray mBytes;
};

#endif // QQTDATASERIALIZATION_H

