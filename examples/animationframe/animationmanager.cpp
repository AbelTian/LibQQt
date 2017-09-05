#include "animationmanager.h"
#include "qqtobjectfactory.h"
#include "qqtanimation.h"
#include "qqtgui-qt.h"

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
    QPushButton* pushButton = (QPushButton*)QQTObjectFactory::registedObject("pushButton");
    QPushButton* pushButton_2 = (QPushButton*)QQTObjectFactory::registedObject("pushButton_2");
    QPushButton* pushButton_3 = (QPushButton*)QQTObjectFactory::registedObject("pushButton_3");
    QPushButton* pushButton_4 = (QPushButton*)QQTObjectFactory::registedObject("pushButton_4");
    QPushButton* pushButton_5 = (QPushButton*)QQTObjectFactory::registedObject("pushButton_5");
    QPushButton* pushButton_6 = (QPushButton*)QQTObjectFactory::registedObject("pushButton_6");

    QQTAnimation* ani = new QQTAnimation(this);
    QSequentialAnimationGroup* sa = new QSequentialAnimationGroup(ani);
    QParallelAnimationGroup* pa = new QParallelAnimationGroup(ani);

    QPropertyAnimation* ani0 = new QPropertyAnimation(pushButton, "geometry");
    ani0->setDuration(1000);
    ani0->setStartValue(QRect(300, 150, 100, 30));
    ani0->setEndValue(QRect(500, 150, 100, 30));
    ani0->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation* ani1 = new QPropertyAnimation(pushButton, "geometry");
    ani1->setDuration(1000);
    ani1->setStartValue(QRect(500, 150, 100, 30));
    ani1->setEndValue(QRect(300, 150, 100, 30));
    ani1->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation* ani2 = new QPropertyAnimation(pushButton_2, "geometry");
    ani2->setDuration(500);
    ani2->setStartValue(QRect(300, 200, 100, 30));
    ani2->setEndValue(QRect(500, 200, 100, 30));
    //ani2->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation* ani3 = new QPropertyAnimation(pushButton_2, "geometry");
    ani3->setDuration(200);
    ani3->setStartValue(QRect(500, 200, 100, 30));
    ani3->setEndValue(QRect(300, 200, 100, 30));
    //ani3->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation* ani4 = new QPropertyAnimation(pushButton_3, "geometry");
    ani4->setDuration(1000);
    ani4->setStartValue(QRect(300, 250, 100, 30));
    ani4->setEndValue(QRect(500, 250, 100, 30));
    ani4->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation* ani5 = new QPropertyAnimation(pushButton_3, "geometry");
    ani5->setDuration(1000);
    ani5->setStartValue(QRect(500, 250, 100, 30));
    ani5->setEndValue(QRect(300, 250, 100, 30));
    ani5->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation* ani6 = new QPropertyAnimation(pushButton_4, "geometry");
    ani6->setDuration(1000);
    ani6->setStartValue(QRect(300, 300, 100, 30));
    ani6->setEndValue(QRect(500, 300, 100, 30));
    ani6->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation* ani7 = new QPropertyAnimation(pushButton_4, "geometry");
    ani7->setDuration(1000);
    ani7->setStartValue(QRect(500, 300, 100, 30));
    ani7->setEndValue(QRect(300, 300, 100, 30));
    ani7->setEasingCurve(QEasingCurve::OutBounce);

    sa->addAnimation(ani0);
    sa->addAnimation(ani2);
    pa->addAnimation(ani4);
    pa->addAnimation(ani6);

    //pa->addAnimation(ani1);
    //pa->addAnimation(ani3);
    //pa->addAnimation(ani5);
    //pa->addAnimation(ani7);

    connect(pushButton_5, SIGNAL(clicked(bool)),
            ani, SLOT(start()));
    connect(pushButton_6, SIGNAL(clicked(bool)),
            pa, SLOT(start()));
}
