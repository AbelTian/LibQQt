#ifndef QQTOSDWIDGET_H
#define QQTOSDWIDGET_H

#include <qqtwidget.h>

#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtOSDWidget : public QQtWidget
{
    Q_OBJECT
public:
    explicit QQtOSDWidget ( QWidget* parent = nullptr );
    ~QQtOSDWidget() {}

signals:

public slots:
};

#endif // QQTOSDWIDGET_H
