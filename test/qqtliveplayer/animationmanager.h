#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <QObject>
#include "qqt.h"

class AnimationManager : public QObject
{
public:
    static AnimationManager* Instance ( QObject* parent = 0 );

signals:

public slots:
protected:
    explicit AnimationManager ( QObject* parent = nullptr );
private:
    static AnimationManager* _instance;
};

#endif // ANIMATIONMANAGER_H
