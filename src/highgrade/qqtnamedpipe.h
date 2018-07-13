#ifndef QQTNAMEDPIPE_H
#define QQTNAMEDPIPE_H

#include <qqt-local.h>
#include <qqtcore.h>
#include <qqtmessage.h>
#include <qqtlocalclient.h>
#include <qqtlocalserver.h>

/**
 * @brief The QQtNamedPipe class
 * 类似于QSharedMemory使用方式。只不过底层使用Pipe(QLocalSocket)实现。
 */
class QQTSHARED_EXPORT QQtNamedPipe : public QQtLocalClient
{
    Q_OBJECT
public:
    explicit QQtNamedPipe ( const QString& key, QObject* parent = Q_NULLPTR ) : QQtLocalClient ( parent ) {

    }
    ~QQtNamedPipe() {}

    //需要重写，改变共享内存块大小。
    virtual void initializer() {
        //user set payload size.
        //这个只需要调用一次，但是调用多次也正常使用。我在这个教程父类里面给的是1024.子类可变可改。这个是最大约束，万万不能超过。
        //create ( 1024 );
        //这个每个变量都必须调用！是这个函数保证data()指针有数的。
        //attach();
    }

    //需要重写，实现把局部变量打包到共享内存块。（注释部分。）
    //这个函数保证写入共享内存。
    virtual void packer() {
        //lock();

        //user data struct
        QByteArray bytes;
        //bytes << a;

        //这个是无论如何不应该发生的，用户在申请空间的时候应当申请足够的以供变动的空间。
        if ( bytes.size() > size() ) {
            pline() << "bytes size out payload..., create more...";
            //unlock();
            return;
        }
        //memcpy ( data(), bytes.constData(), bytes.size() );
        //unlock();
    }

    //需要重写，实现把共享内存块解压到局部变量。（注释部分。）
    //这个函数保证从共享内存读取。
    virtual void parser() {
        //lock();
        QByteArray bytes;
        bytes.resize ( size() );
        //memcpy ( bytes.data(), data(), size() );

        //user data struct
        //bytes >> a;

        //unlock();
    }

    /*以下函数提供操作方便。*/

    QByteArray readShortString ( QByteArray& bytes ) {
        quint16 s0;
        QByteArray str;
        bytes >> s0;
        str.resize ( s0 );
        bytes >> str;
        return str;
    }

    void writeShortString ( QByteArray& bytes, QByteArray& shortString ) {
        quint16 s0 = shortString.size();
        bytes << s0;
        bytes << shortString;
    }

    QByteArray readString ( QByteArray& bytes ) {
        quint32 s0;
        QByteArray str;
        bytes >> s0;
        str.resize ( s0 );
        bytes >> str;
        return str;
    }

    void writeString ( QByteArray& bytes, QByteArray& shortString ) {
        quint32 s0 = shortString.size();
        bytes << s0;
        bytes << shortString;
    }

signals:

public slots:

private:
    /**
     * example
     * quint32 a;
     * QByteArray b;
     * quint8 c;
     */
};

#endif // QQTNAMEDPIPE_H
