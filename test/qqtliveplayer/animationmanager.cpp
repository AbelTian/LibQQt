#include "animationmanager.h"
#include "qqtobjectmanager.h"
#include "qqtanimation.h"
#include "qqt-qt.h"
#include "qqtwindow.h"

AnimationManager* AnimationManager::_instance = NULL;

AnimationManager *AnimationManager::Instance(QObject *parent)
{
    if(_instance)
        return _instance;
    _instance = new AnimationManager(parent);
    return _instance;
}

AnimationManager::AnimationManager(QObject *parent) : QObject(parent)
{
    //init app's all animation
#if 0
    /**
     * window appear and miss  and and  animation
     * animation start
     * step1 label ani0 go..
     * user can't decate qqtwindow
     */
    QQTWindow* qqtwindow = (QQTWindow*)
            QQtObjectManager::registeredObject("QQTWindow");
    QQtAnimation* ani = new QQtAnimation(this);
    QSequentialAnimationGroup* sani = new QSequentialAnimationGroup(ani);
    QParallelAnimationGroup* pani = new QParallelAnimationGroup(ani);
    QPropertyAnimation* ani1 = new QPropertyAnimation(qqtwindow, "geometry");
    ani1->setDuration(1000);
    QRect r1 = qqtwindow->geometry(); r1.setLeft(-800);
    ani1->setStartValue(r1);
    ani1->setEndValue(qqtwindow->geometry());
    sani->addAnimation(ani1);
    ani->start();
#endif
}
