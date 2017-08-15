#ifndef QQTANIMATIONMANAGER_H
#define QQTANIMATIONMANAGER_H

#include <QObject>
#include "qqtobjectfactory.h"
#include "qqtanimation.h"
#include "qqtgui-qt.h"

/**
 * @brief The QQTAnimationManager class
 * @brief 这是指示型代码，不可使用，否则将会出现无法调用子类构造函数的问题
 * @brief AppAnimationManager模仿此类编写
 * @brief 在构造函数中处理所有的动画修饰动作
 */
class QQTAnimationManager : public QObject
{
    Q_OBJECT
public:
    static QQTAnimationManager *Instance(QObject* parent = 0);

signals:

public slots:
protected:
    explicit QQTAnimationManager(QObject *parent = nullptr);
private:
    static QQTAnimationManager* _instance;
};

#endif // QQTANIMATIONMANAGER_H
