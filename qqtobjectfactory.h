#ifndef QQTOBJECTFACTORY_H
#define QQTOBJECTFACTORY_H

#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QList>
#include <QListIterator>

/**
 * @brief The QQTObjectFactory class
 * QQT 对象管理器 工厂模式
 */
class QQTObjectFactory
{
public:
    template<typename T>
    static void registerClass()
    {
        //将生成此类对象的具体（非模板）函数注册进Hash
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }

    static QObject* createObject( const QByteArray& className, QObject* parent = NULL )
    {
        //搜索生成此类对象的函数
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        //生成对象,调用constructorHelper<className>(parent)
        return (*constructor)( parent );
    }

    static void registerObject(const QObject * const& w)
    {
        containers().push_back(w);
    }

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
        //保存生成类对象的具体（非模板）函数
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }

private:
    static QList<const QObject*>& containers()
    {
        static QList<const QObject*> instance;
        return instance;
    }
};

#endif // QQTOBJECTFACTORY_H
