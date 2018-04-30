#include "mainwindow.h"
#include <QQtApplication>
#include "qqtobjectmanager.h"
#include "qqtprotocol.h"
#include "qqtserver2protocolmanager.h"

typedef QObject* ( *Constructor ) ( QObject* parent );
template<typename T>
static QObject* constructorHelper ( QObject* parent = 0 )
{
    pline() << "created ";
    return new T ( parent );
}
template<typename dst_type, typename src_type>
static dst_type pointer_cast ( src_type src )
{
    return *static_cast<dst_type*> ( static_cast<void*> ( &src ) );
}

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    QQtObjectFactory::registerObject<QObject>();
//    QObject* o = QQtObjectFactory::createObject ( "QObject" );
//    pline() << o;

//    QQtObjectFactory::registerObject<QQtProtocol>();
//    QObject* obj = QQtObjectFactory::createObject ( "QQtProtocol" );
//    QQtProtocol* protocol = dynamic_cast<QQtProtocol*> ( obj );
//    pline() << protocol;
//    //protocol->translator ( QByteArray() );

//    QObject* obj = metaObj->newInstance ( Q_ARG ( QString, QStringLiteral ( "Rex" ) ), Q_ARG ( QObject*, nullptr ) );
//    pline() << obj;
//    QQtProtocol* an = qobject_cast<QQtProtocol*> ( obj );
//    pline() << an;

    QMap<QByteArray, Constructor*> instance;
    void* b = pointer_cast<void*> ( &constructorHelper<QQtServer2Protocol> );
    pline() << b;
    Constructor* constructor = ( Constructor* ) b;
    pline() << constructor;
    instance.insert ( "aaa", constructor );
    pline() << "ffff";
    Constructor* func = instance.value ( "aaa" );
    pline() << func;
    Constructor* c = pointer_cast<Constructor*> ( &func );

    QQtServer2Protocol* p = ( QQtServer2Protocol* ) ( *c ) ( 0 );
    pline() << p;
    p->sendCommand();
    //p->translator ( QByteArray() );


    MainWindow w;
    w.show();

    QObject* o = QQtObjectFactory::createObject ( "QObject" );
    pline() << o;

    return a.exec();
}
