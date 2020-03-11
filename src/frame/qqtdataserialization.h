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
 * 内部有QByteArray、字典，
 * 把数据序列化到字典里，通过serialize/unserialize操作，获取字典，获取QByteArray。
 */
class QQTSHARED_EXPORT QQtDataSerialization : public QObject
{
    Q_OBJECT

public:
    explicit QQtDataSerialization ( QObject* parent = 0 )
        : QObject ( parent ) {}
    virtual ~QQtDataSerialization() {}

    QQtDictionary& dictionary() { return mDict; }
    const QQtDictionary& dictionary() const { return mDict; }

    QByteArray& data() { return mBytes; }
    const QByteArray& data() const { return mBytes; }

    void serialize();
    void unserialize();


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

    QQtDataSerialization& operator>> ( QImage& f );
    QQtDataSerialization& operator[] ( QString index );

protected:

private:
    QQtDictionary mDict;
    QByteArray mBytes;
};

#endif // QQTDATASERIALIZATION_H

