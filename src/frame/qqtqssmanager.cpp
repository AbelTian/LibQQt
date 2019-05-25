#include "qqtqssmanager.h"
#include "qqtcore.h"
#include <QFile>
#include <QDir>

QQtQSSManager::QQtQSSManager ( QObject* parent ) : QObject ( parent )
{

}

QQtQSSManager::~QQtQSSManager()
{

}

QList<QString> QQtQSSManager::styleList()
{
    while ( mStyleList.count() > 0 )
        mStyleList.removeAt ( 0 );
    QDir d ( skin ( "." ) );
    foreach ( QFileInfo mfi, d.entryInfoList() )
    {
        if ( mfi.isFile() )
        {
            if ( mfi.suffix() != "qss" )
                continue;
            //不包括default.qss
            if ( mfi.baseName() == "default" )
                continue;
            if ( mfi.baseName() == "current" )
                continue;
            QString styleName = mfi.completeBaseName();
            mStyleList.push_back ( styleName );
        }
    }
    //pline() << d.absolutePath();
    //pline() << mStyleList;
    return mStyleList;
}

void QQtQSSManager::setCurrentStyle ( QString styleName )
{
    //pline() << "set style";
    //pline() << skin ( "default.qss" );
    //pline() << QFile ( skin ( "default.qss" ) ).exists() << QDir ( skin ( "default.qss" ) ).exists();
    //pline() << skin ( QString ( "%1.qss" ).arg ( styleName ) );
    //pline() << QFile ( skin ( QString ( "%1.qss" ).arg ( styleName ) ) ).exists() << QDir ( skin ( QString ( "%1.qss" ).arg ( styleName ) ) ).exists();

    if ( !QFile ( skin ( "default.qss" ) ).exists() )
        return;
    if ( !QFile ( skin ( QString ( "%1.qss" ).arg ( styleName ) ) ).exists() )
        return;
    //pline() << "set style 2" << styleName;
#ifdef __EMBEDDED_LINUX__
    QString cmd = QString ( "touch %1" ).arg ( skin ( "current.qss" ) );
    system ( cmd.toLocal8Bit().constData() );
#endif

    QByteArray bytes;

    QFile f1 ( skin ( "default.qss" ) );
    f1.open ( QFile::ReadOnly );
    bytes = f1.readAll();
    f1.close();

    QFile f2 ( skin ( QString ( "%1.qss" ).arg ( styleName ) ) );
    f2.open ( QFile::ReadOnly );
    bytes += f2.readAll();
    f2.close();

    QFile file ( skin ( "current.qss" ) );
    file.open ( QFile::Truncate | QFile::WriteOnly );
    file.write ( bytes );
    file.close();

    //pline() << skin ( "current.qss" );
    qqtApp->setQSSStyle ( skin ( "current.qss" ) );
}
