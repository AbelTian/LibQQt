#ifndef QQTDOUBLECLICKSOUNDHELPER_H
#define QQTDOUBLECLICKSOUNDHELPER_H

#include <qqt-local.h>
#include <qqtcore.h>
#include <qqtdoubleclickhelper.h>
#include <QSound>

/**
 * QQtDoubleClickSoundHelper
 * 为Widget提供按键声音支持.
 *
 * 支持
 * click、longclick、doubleclick
 *
 */
class QQTSHARED_EXPORT QQtDoubleClickSoundHelper : public QQtDoubleClickHelper
{
    Q_OBJECT

public:
    explicit QQtDoubleClickSoundHelper ( QObject* parent = 0 ) : QQtDoubleClickHelper ( parent ) {
        connect ( this, SIGNAL ( click() ), this, SLOT ( slotClick() ) );
        connect ( this, SIGNAL ( longClick() ), this, SLOT ( slotLongClick() ) );
        connect ( this, SIGNAL ( doubleClick() ), this, SLOT ( slotDoubleClick() ) );
    }
    virtual ~QQtDoubleClickSoundHelper() {}

    void setClickSound ( const QString clickSoundFile ) {
        this->clickSoundFile = clickSoundFile;
    }
    void setLongClickSound ( const QString clickSoundFile ) {
        this->longClickSoundFile = clickSoundFile;
    }
    void setDoubleClickSound ( const QString clickSoundFile ) {
        this->doubleClickSoundFile = clickSoundFile;
    }

    /**
     * 内部
     */
public slots:
    void slotClick() {
        if ( clickSoundFile.isEmpty() )
            return;

        QSound::play ( clickSoundFile );
    }
    void slotLongClick() {
        if ( longClickSoundFile.isEmpty() )
            return;

        QSound::play ( longClickSoundFile );
    }
    void slotDoubleClick() {
        if ( doubleClickSoundFile.isEmpty() )
            return;

        QSound::play ( doubleClickSoundFile );
    }

private:
    QString clickSoundFile;
    QString longClickSoundFile;
    QString doubleClickSoundFile;
};

#endif // QQTDOUBLECLICKSOUNDHELPER_H
