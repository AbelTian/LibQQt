#ifndef QQTCLICKSOUNDHELPER_H
#define QQTCLICKSOUNDHELPER_H

#include <qqt-local.h>
#include <qqtcore.h>
#include <qqtclickhelper.h>

/**
 * QQtClickSoundHelper
 *
 * 为Widget提供按键声音支持.
 *
 * ClickSoundHelper和Widget共用ClickHelper,实现Widget按键同时能播放声音的能力
 * 依赖QQtClickHelper实现
 */
class QQTSHARED_EXPORT QQtClickSoundHelper : public QObject
{
    Q_OBJECT

public:
    explicit QQtClickSoundHelper ( QObject* parent = 0 );
    virtual ~QQtClickSoundHelper();

    void setClickSound();
    void setLongClickSound();

public:
    //一般,调用widget的clickHelper,设置到这里.
    inline void setClickHelper ( QQtClickHelper* helper ) {
        uninstallClickHelper();
        mClickHelper = helper;
        installClickHelper();
    }
    inline const QQtClickHelper* clickHelper() const {
        return mClickHelper;
    }

protected:
    //允许重写
    virtual void installClickHelper() {

    }
    virtual void uninstallClickHelper() {

    }
    QQtClickHelper* mClickHelper;

    /**
     * 内部
     */
public slots:
    void slotClick() {}
    void slotLongClick() {}
};

#endif // QQTCLICKSOUNDHELPER_H
