#ifndef QQTOSDWIDGET_H
#define QQTOSDWIDGET_H

#include <qqtwidget.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * QQtOSDWidget
 * 透明背景的Widget，可以应用于作为透明控件。
 */
class QQTSHARED_EXPORT QQtOSDWidget : public QQtWidget
{
    Q_OBJECT
public:
    explicit QQtOSDWidget ( QWidget* parent = nullptr );
    virtual ~QQtOSDWidget() {}

signals:

public slots:
};

#endif // QQTOSDWIDGET_H
