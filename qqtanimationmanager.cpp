#include "qqtanimationmanager.h"

QQTAnimationManager* QQTAnimationManager::_instance = NULL;

QQTAnimationManager *QQTAnimationManager::Instance(QObject *parent)
{
    if(_instance)
        return _instance;
    _instance = new QQTAnimationManager(parent);
    return _instance;
}

QQTAnimationManager::QQTAnimationManager(QObject *parent) : QObject(parent)
{
}
