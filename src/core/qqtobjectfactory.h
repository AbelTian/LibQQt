#ifndef QQTOBJECTFACTORY_H
#define QQTOBJECTFACTORY_H

#include <QObject>
#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QList>
#include <QListIterator>
#include <QWidget>
#include "qqt-local.h"
#include "qqtcore.h"

#if 0
class QQTSHARED_EXPORT QQtConstructer : public QObject

{
    Q_OBJECT
public:
    explicit QQtConstructer ( QObject* parent = 0 ) :
        QObject ( parent ) {}
    virtual ~QQtConstructer() {}

protected:
    virtual QString constructorName()  = 0;
};

/**
 * @brief The QQtObjectConstructer class
 * QQt 对象生产器
 */
class QQTSHARED_EXPORT QQtObjectConstructer : public QQtConstructer

{
    Q_OBJECT
public:
    explicit QQtObjectConstructer ( QObject* parent = 0 ) :
        QQtConstructer ( parent ) {}
    virtual ~QQtObjectConstructer() {}

    virtual QString constructorName() { return "QObject"; }

private:
    typedef QObject* ( *Constructor ) ( QObject* parent );

    template<typename T>
    static QObject* constructorHelper ( QObject* parent = 0 ) {
        return new T ( parent );
    }

    static QHash<QByteArray, Constructor>& constructors() {
        /*
         * 保存生成类对象的具体（非模板）函数
         */
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};

/**
 * @brief The QQtWidgetConstructer class
 * QQt 对象生产器
 */
class QQTSHARED_EXPORT QQtWidgetConstructer : public QQtConstructer

{
    Q_OBJECT
public:
    explicit QQtWidgetConstructer ( QObject* parent = 0 ) :
        QQtConstructer ( parent ) {}
    virtual ~QQtWidgetConstructer() {}

    virtual QString constructorName() { return "QWidget"; }

private:
    typedef QWidget* ( *Constructor ) ( QWidget* parent );

    template<typename T>
    static QWidget* constructorHelper ( QWidget* parent = 0 ) {
        return new T ( parent );
    }

    static QHash<QByteArray, Constructor>& constructors() {
        /*
         * 保存生成类对象的具体（非模板）函数
         */
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};

/**
 * @brief The QQtObjectFactory class
 * QQt 对象生产器 工厂模式
 */
class QQTSHARED_EXPORT QQtObjectFactory2
{
public:

private:
    template<typename T>
    static QQtConstructer* objectContructor() {
        static QList<QQtConstructer*>* objcList = NULL;

        if ( !objcList ) {
            objcList = new QList<QQtConstructer*>();
            //add custom contructor
            objcList->push_back ( new QQtObjectConstructer() );
            objcList->push_back ( new QQtWidgetConstructer() );
        }

        T obj;
        QQtConstructer* objcc = NULL;
        /*
        QListIterator itor ( objcList );

        while ( itor.hasNext() ) {
            QQtConstructer* objc = *itor.next();

            if ( obj.inherits ( objc->constructorName() ) ) {
                objcc = objc;
                break;
            }
        }
        */

        return objcc;
    }
};
#endif

/**
 * @brief The QQtObjectFactory class
 * QQt 对象生产器 工厂模式
 */
class QQTSHARED_EXPORT QQtObjectFactory
{
public:
    template<typename T>
    static void registerObject() {
        /*
         * 将生成此类对象的具体（非模板）函数注册进Hash
         */
        constructors().insert ( T::staticMetaObject.className(), &constructorHelper<T> );
    }
    /**
     * @brief createObject 根据对象类型（类名）生成类对象实例
     * @param className
     * @param parent
     * @return
     */
    static QObject* createObject ( const QByteArray& className, QObject* parent = NULL ) {
        /*
         * 搜索生成此类对象的函数
         */
        Constructor constructor = constructors().value ( className );

        if ( constructor == NULL )
            return NULL;

        /*
         * 生成对象,调用的是constructorHelper<className>(parent)
         */
        return ( *constructor ) ( parent );
    }

private:
    typedef QObject* ( *Constructor ) ( QObject* parent );

    template<typename T>
    static QObject* constructorHelper ( QObject* parent = 0 ) {
        return new T ( parent );
    }

    static QHash<QByteArray, Constructor>& constructors() {
        /*
         * 保存生成类对象的具体（非模板）函数
         */
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};

/**
 * @brief The QQtWidgetFactory class
 * QQt Widget生产器 工厂模式
 */
class QQTSHARED_EXPORT QQtWidgetFactory
{
public:
    /**
     * call this function, you must add ()
     * registerObject<T> &registerObject<T> is only a function address, but print true...
     */
    template<typename T>
    static void registerObject() {
        /*
         * 将生成此类对象的具体（非模板）函数注册进Hash
         */
        constructors().insert ( T::staticMetaObject.className(), &constructorHelper<T> );
    }
    /**
     * @brief createObject 根据对象类型（类名）生成类对象实例
     * @param className
     * @param parent
     * @return
     */
    static QWidget* createObject ( const QByteArray& className, QWidget* parent = NULL ) {
        /*
         * 搜索生成此类对象的函数
         */
        Constructor constructor = constructors().value ( className );

        if ( constructor == NULL ) {
            return NULL;
        }

        /*
         * 生成对象,调用的是constructorHelper<className>(parent)
         */
        return ( *constructor ) ( parent );
    }

private:
    typedef QWidget* ( *Constructor ) ( QWidget* parent );

    template<typename T>
    static QWidget* constructorHelper ( QWidget* parent = 0 ) {
        return new T ( parent );
    }

    static QHash<QByteArray, Constructor>& constructors() {
        /*
         * 保存生成类对象的具体（非模板）函数
         */
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};

/**
 * @brief The QQtObjectParcel class
 * QQt 对象管理器 工厂模式
 */
class QQTSHARED_EXPORT QQtObjectParcel
{
public:
    /**
     * @brief registerObject 将对象注册进工厂
     * @param w
     */
    static void registerObject ( const QObject* const& w ) {
        containers().push_back ( w );
    }
    /**
     * @brief unregisterObject 取消对象在工厂中注册
     * @param w
     */
    static void unregisterObject ( const QObject*& w ) {
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
    static const QObject* registeredObject ( const QString objName ) {
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
    static QList<const QObject*>& containers() {
        static QList<const QObject*> instance;
        return instance;
    }
};

#endif // QQTOBJECTFACTORY_H
