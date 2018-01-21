#ifndef QQTGIFWIDGET_H
#define QQTGIFWIDGET_H

#include <QWidget>
#include <QMovie>
#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtGifWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QQtGifWidget ( QWidget* parent = nullptr );
    virtual ~QQtGifWidget() {}

signals:

public slots:

private:
};

#endif // QQTGIFWIDGET_H
