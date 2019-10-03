#ifndef QQTSHAREDMEMORY_H
#define QQTSHAREDMEMORY_H

#include <QSharedMemory>
#include <qqt-local.h>
#include <qqtcore.h>
#include <qqtmessage.h>

/**
 * @brief The QQtSharedMemory class
 * 共享内存读写实现类。
 * 允许可变长度的局部变量。
 *
 * 原理：
 * 在每个个局部变量和共享内存块之间进行数据交换。
 * 业务层从局部变量取值和设值。
 *
 * 使用方法：
 * 1.继承这个类，定义成员变量，允许使用QByteArray。
 * 2.实现packer和parser函数，从共享内存块里顺序读和顺序写数据。
 * 3.create创建内存块，固定大小的内存块，共享内存有这样的约束。
 * 4.attach使内存块在当前线程里生效。
 * 5.不使用了以后，detach。
 *
 * 注意：detach以后需要频繁create和attach，以确保内存没有被释放。
 * 注意：key是确认共享内存的唯一值，可以取作为变量名。
 * 注意：数据结构是保持不变的，改变的是数据结构里面的Value。
 *
 * 1.initializer() 初始化 create attach。特点：内存空间地址是动态会变化的，但是value却保持的。所以频繁create、attach就好了，防止没有create或者attach导致的空间地址为null。
 * 2.共享块数据结构保持，实现packer parser。
 * 3.XXXSharedMemory variable("key"); 特点：第一个，必须保持，static，必须有个保持的，什么都不干，就用来保持就行。
 * 4.variable.initializer(); 特点：每个变量都必须调用！
 * 5.variable.parser(); XXXSharedMemory内部定义的成员变量就可以使用了。
 * 6.variable.packer(); XXXSharedMemory内部定义的成员变量就写到共享存储块里面了。
 * 7.只要保证写入的总长度小于等于共享存储块的大小就不会出错。读取的时候总长度随便。
 *
 * 约束：共享内存块总长定长，不能变化。内部组成不定长。
 */
class QQTSHARED_EXPORT QQtSharedMemory : public QSharedMemory
{
    Q_OBJECT
public:
    explicit QQtSharedMemory ( const QString& key, QObject* parent = Q_NULLPTR ) : QSharedMemory ( key, parent ) {

    }
    virtual ~QQtSharedMemory() {}

    //需要重写，改变共享内存块大小。
    virtual void initializer() {
        //user set payload size.
        //这个只需要调用一次，但是调用多次也正常使用。我在这个教程父类里面给的是1024.子类可变可改。这个是最大约束，万万不能超过。
        create ( 1024 );
        //这个每个变量都必须调用！是这个函数保证data()指针有数的。
        attach();
    }

    //需要重写，实现把局部变量打包到共享内存块。（注释部分。）
    //这个函数保证写入共享内存。
    virtual void packer() {
        lock();

        //user data struct
        QByteArray bytes;
        //bytes << a;

        //这个是无论如何不应该发生的，用户在申请空间的时候应当申请足够的以供变动的空间。
        if ( bytes.size() > size() ) {
            pline() << "bytes size out payload..., create more...";
            unlock();
            return;
        }
        memcpy ( data(), bytes.constData(), bytes.size() );
        unlock();
    }

    //需要重写，实现把共享内存块解压到局部变量。（注释部分。）
    //这个函数保证从共享内存读取。
    virtual void parser() {
        lock();
        QByteArray bytes;
        bytes.resize ( size() );
        memcpy ( bytes.data(), data(), size() );

        //user data struct
        //bytes >> a;

        unlock();
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


#endif //QQTSHAREDMEMORY_H
