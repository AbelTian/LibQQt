#ifndef QQTLONGCLICKSOUNDHELPER_H
#define QQTLONGCLICKSOUNDHELPER_H

#include <qqt-local.h>
#include <qqtcore.h>
#include <qqtlongclickhelper.h>
#include <qqtsoundeffect.h>

/**
 * QQtLongClickSoundHelper
 *
 * 为Widget提供按键声音支持.
 *
 * 支持
 * click
 *
 */
class QQTSHARED_EXPORT QQtLongClickSoundHelper : public QQtLongClickHelper
{
    Q_OBJECT

public:
    explicit QQtLongClickSoundHelper ( QObject* parent = 0 ) : QQtLongClickHelper ( parent ) {
        connect ( this, SIGNAL ( click() ), this, SLOT ( slotClick() ) );
        connect ( this, SIGNAL ( longClick() ), this, SLOT ( slotLongClick() ) );
    }
    virtual ~QQtLongClickSoundHelper() {}

    inline void setClickSound ( const QString clickSoundFile ) {
        this->clickSoundFile = clickSoundFile;
    }
    inline void setLongClickSound ( const QString clickSoundFile ) {
        this->longClickSoundFile = clickSoundFile;
    }

    /**
     * 内部
     */
public slots:
    void slotClick() {
        if ( clickSoundFile.isEmpty() )
            return;

        QQtWavSound ( clickSoundFile );
    }
    void slotLongClick() {
        if ( longClickSoundFile.isEmpty() )
            return;

        QQtWavSound ( longClickSoundFile );
    }

private:
    QString clickSoundFile;
    QString longClickSoundFile;
};

#endif // QQTLONGCLICKSOUNDHELPER_H
