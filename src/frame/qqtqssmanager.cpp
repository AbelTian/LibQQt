#include "qqtqssmanager.h"

QQtQSSManager::QQtQSSManager ( QObject* parent )
{

}

QQtQSSManager::~QQtQSSManager()
{

}

QList<QString> QQtQSSManager::styleList()
{
    while ( mStyleList.count() > 0 )
        mStyleList.removeAt ( 0 );
    QDir d ( SKIN_PATH );
    foreach ( QFileInfo mfi, d.entryInfoList() )
    {
        if ( mfi.isFile() )
        {
            if ( mfi.suffix() != "qss" )
                continue;
            //不包括default.qss
            if ( mfi.baseName() == "default" )
                continue;
            QString styleName = mfi.completeBaseName();
            mStyleList.push_back ( styleName );
        }
    }
    return mStyleList;
}

void QQtQSSManager::setCurrentStyle ( QString styleName )
{
    if ( !QDir ( skin ( "default.qss" ) ).exists() )
        return;
    if ( !QDir ( skin ( QString ( "%1.qss" ).arg ( styleName ) ) ).exists() )
        return;

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

    qqtApp->setQSSStyle ( skin ( "current.qss" ) );
}
