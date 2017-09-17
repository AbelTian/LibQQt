#ifndef QQTOBJECTFACTORY_H
#define QQTOBJECTFACTORY_H

#include <QObject>
#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QList>
#include <QListIterator>
#include <qqt-local.h>

/**
 * @brief The QQTObjectFactory class
 * QQT 对象管理器 工厂模式
 */
class QQTSHARED_EXPORT QQTObjectFactory
{
public:
    /**
     * @brief createObject 根据对象类型（类名）生成类对象实例
     * @param className
     * @param parent
     * @return
     */
    static QObject* createObject( const QByteArray& className, QObject* parent = NULL )
    {
        /*
         * 搜索生成此类对象的函数
         */
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        /*
         * 生成对象,调用constructorHelper<className>(parent)
         */
        return (*constructor)( parent );
    }
    /**
     * @brief registerObject 将对象注册进工厂
     * @param w
     */
    static void registerObject(const QObject * const& w)
    {
        containers().push_back(w);
    }
    /**
     * @brief unregisterObject 取消对象在工厂中注册
     * @param w
     */
    static void unregisterObject(const QObject*& w)
    {
        QListIterator<const QObject*> itor(containers());
        while(itor.hasNext())
        {
            const QObject* ww = itor.next();
            if(ww == w)
            {
                containers().removeOne(w);
                break;
            }
        }
    }
    /**
     * @brief registedObject 根据对象名（ObjectName）查找注册的对象。
     * @param objName
     * @return
     */
    static const QObject* registedObject(const QString objName)
    {
        QListIterator<const QObject*> itor(containers());
        while(itor.hasNext())
        {
            const QObject* ww = itor.next();
            if(ww->objectName() == objName)
            {
                return ww;
            }
        }
    }

private:
    typedef QObject* (*Constructor)( QObject* parent );

    template<typename T>
    static QObject* constructorHelper( QObject* parent )
    {
        return new T( parent );
    }

    static QHash<QByteArray, Constructor>& constructors()
    {
        /*
         * 保存生成类对象的具体（非模板）函数
         */
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }

    template<typename T>
    static void registerClass()
    {
        /*
         * 将生成此类对象的具体（非模板）函数注册进Hash
         */
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }

private:
    static QList<const QObject*>& containers()
    {
        static QList<const QObject*> instance;
        return instance;
    }
};

#endif // QQTOBJECTFACTORY_H
