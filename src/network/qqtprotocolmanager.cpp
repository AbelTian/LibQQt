#include <qqtprotocolmanager.h>


QQtProtocolManager::QQtProtocolManager ( QObject* parent ) : QObject ( parent )
{
}

QQtProtocolManager::~QQtProtocolManager()
{

}

QQtProtocol* QQtProtocolManager::createProtocol()
{
    if ( m_protocol_list.isEmpty() )
        return NULL;

    //无论如何，使用对象工厂也一样，都不能正确生成。对象工厂崩溃退出。
    //QQtProtocol* p0 = ( QQtProtocol* ) mProtocol->metaObject()->newInstance ( Q_ARG(QQtProtocolManager*, this) );
    QQtProtocol* p0 = findDetachedInstance();
    if ( p0 == 0 )
        return NULL;
    pmeta ( p0 ) << p0;

    //帮助Protocol给用户发数据。
    connect ( p0, SIGNAL ( notifyToProtocolManager ( const QQtProtocol*, const QQtMessage* ) ),
              this, SIGNAL ( notifyToBusinessLevel ( const QQtProtocol*, const QQtMessage* ) ) );
    return p0;
}

QQtProtocol* QQtProtocolManager::findDetachedInstance()
{
    QListIterator<QQtProtocol*> itor ( m_protocol_list );
    while ( itor.hasNext() )
    {
        QQtProtocol* p = itor.next();
        if ( p->detached() )
            return p;
    }
    return NULL;
}
