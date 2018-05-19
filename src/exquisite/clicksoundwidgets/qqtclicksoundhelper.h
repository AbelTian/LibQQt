#ifndef QQTCLICKSOUNDHELPER_H
#define QQTCLICKSOUNDHELPER_H

#include <qqt-local.h>
#include <qqtcore.h>
#include <qqtclickhelper.h>
#include <qqtsoundeffect.h>

/**
 * QQtClickSoundHelper
 *
 * 为Widget提供按键声音支持.
 *
 * 支持
 * click
 *
 */
class QQTSHARED_EXPORT QQtClickSoundHelper : public QQtClickHelper
{
    Q_OBJECT

public:
    explicit QQtClickSoundHelper ( QObject* parent = 0 ) : QQtClickHelper ( parent ) {
        connect ( this, SIGNAL ( click() ), this, SLOT ( slotClick() ) );
    }
    virtual ~QQtClickSoundHelper() {}

    void setClickSound ( const QString clickSoundFile ) {
        this->clickSoundFile = clickSoundFile;
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

private:
    QString clickSoundFile;
};

#endif // QQTCLICKSOUNDHELPER_H
