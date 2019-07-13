#ifndef QQTOBJECTMANAGER_H
#define QQTOBJECTMANAGER_H

#include <QObject>
#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QList>
#include <QListIterator>
#include <QWidget>
#include "qqt-local.h"
#include "qqtcore.h"


/**
 * @brief The QQtObjectFactory class
 * QQt 对象生产器 工厂模式
 * 这是个模板函数，可以typedef出非常多基于基础类别的对象工厂。
 * 这里提供
 * QQtObjectFactory,
 * QQtWidgetFactory,
 */

QQTSHARED_EXPORT bool operator< (  QByteArray& l,  QByteArray& r );
QQTSHARED_EXPORT bool operator== (  QByteArray& l,  QByteArray& r );

template <class ObjectType>
class QQTSHARED_EXPORT __QQtObjectFactory__
{
public:

    /**
     * 方便函数
     * 用于指针类型之间的随意互转，以void*为中转。
     * 用于模板函数和模板函数实例之间进行转换，绝佳。
     */
    template<typename dst_type, typename src_type>
    static dst_type pointer_cast ( src_type src ) {
        return *static_cast<dst_type*> ( static_cast<void*> ( &src ) );
    }

    template<typename T>
    static void registerObject() {
        /*
         * 将生成此类对象的具体（非模板）函数注册进Hash
         */
        void* a = pointer_cast<void*> ( &__QQtObjectFactory__::constructorHelper<T> );
        //pline() << a;
        Constructor* constructor = ( Constructor* ) a;
        //pline() << constructor;
        constructors().insert ( T::staticMetaObject.className(), constructor );
    }
    /**
     * @brief createObject 根据对象类型（类名）生成类对象实例
     * @param className
     * @param parent
     * @return
     */
    static ObjectType* createObject ( const QByteArray& className, ObjectType* parent = NULL ) {
        /*
         * 搜索生成此类对象的函数
         */
        //pline() << constructors();
        Constructor* constructor = 0;//constructors().value( ( className, 0 );
        QMapIterator<QByteArray, Constructor*> itor ( constructors() );

        //pline() << constructors().isDetached();
        while ( itor.hasNext() ) {
            itor.next();
            //pline() << itor.key() << itor.value();

#if 0
            /**
             * @brief 这里发现一个bug，记录
             * 这里的QByteArray = == 运算全崩溃了。
             * 经过调查，发现，在跨线程的时候，这个操作无法进行。
             */
            QByteArray cc;
            QByteArray dd;
            cc = itor.key();//?
            dd = className;
            pline() << cc << dd;

            if ( cc == dd ) //??? 不能比较吗？能，但是必须加bool转换。
                constructor = itor.value();
#endif

            pline() << className << itor.key() << itor.value();
            //pline() << ( bool ) ( className == itor.key() );
            if ( ( bool ) ( className == itor.key() ) ) {
                constructor = itor.value();
                break;
            }
        }
        //pline() << constructor;

        if ( constructor == NULL )
            return NULL;

        //pline() << *constructor;
        //pline() << **constructor;
        //pline() << &*constructor;
        //pline() << &constructor;
        //pline() << *& constructor;

        /*
         * 生成对象,调用的是constructorHelper<className>(parent)
         */
        Constructor* a = pointer_cast<Constructor*> ( &constructor );
        //pline() << a << *a;
        return ( *a ) ( parent );
    }

private:
    typedef ObjectType* ( *Constructor ) ( ObjectType* parent );

    template<typename T>
    static ObjectType* constructorHelper ( ObjectType* parent = 0 ) {
        //pline() << "created ";
        return new T ( parent );
    }

    static QMap<QByteArray, Constructor*>& constructors() {
        /*
         * 保存生成类对象的具体（非模板）函数
         * 这个变量是全局的。
         * 无论是否使用静态函数包裹，这个变量用于是全局的，一直存在，不受类的实例存在与否控制。
         */
        static QMap<QByteArray, Constructor*> instance;
        return instance;
    }
};

typedef __QQtObjectFactory__<QObject> QQtObjectFactory;
typedef __QQtObjectFactory__<QWidget> QQtWidgetFactory;

/**
 * @brief The QQtObjectManager class
 * QQt 对象管理器
 * 用于管理Qt对象实例。
 * 曾用名 QQtObjectParcel
 */
class QQTSHARED_EXPORT QQtObjectManager
{
public:
    /**
     * @brief registerObject 将对象注册进工厂
     * @param w
     */
    static void registerObject ( const QObject* const& w ) {
        if ( containers().contains ( w ) )
            return;
        containers().push_back ( w );
    }
    /**
     * @brief unregisterObject 取消对象在工厂中注册
     * @param w
     */
    static void unregisterObject ( const QObject* const& w ) {
        QListIterator<const QObject*> itor ( containers() );

        while ( itor.hasNext() ) {
            const QObject* ww = itor.next();

            if ( ww == w ) {
                containers().removeOne ( w );
                break;
            }
        }
    }
    /**
     * @brief registeredObject 根据对象名（ObjectName）查找注册的对象。
     * @param objName
     * @return
     */
    static const QObject* registeredObject ( const QByteArray& objName ) {
        QListIterator<const QObject*> itor ( containers() );

        while ( itor.hasNext() ) {
            const QObject* ww = itor.next();

            if ( ww->objectName() == objName ) {
                return ww;
            }
        }

        return nullptr;
    }

private:
    //包裹一下，有利于省却全局声明。
    //强调：这个static不论是否被静态成员函数包裹，永远存在。
    //类不决定生存周期。
    //类决定作用域。
    static QList<const QObject*>& containers() {
        static QList<const QObject*> instance;
        return instance;
    }
};

#endif // QQTOBJECTMANAGER_H
