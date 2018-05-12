#ifndef QQTTABBAR_H
#define QQTTABBAR_H

#include <QTabBar>
#include <QColor>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqt-local.h"

/**
 * @brief The QQtTabBar class
 * 用于解决QtTabWidget接口上的错误。
 */
class QQTSHARED_EXPORT QQtTabBar : public QTabBar
{
    Q_OBJECT

public:
    explicit QQtTabBar(QWidget* parent = 0);
    virtual ~QQtTabBar() {}
protected:
    //inline but no implement in headers cause link error.
    bool verticalTabs();
};

#endif // QQTTABBAR_H
