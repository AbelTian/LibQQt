#ifndef QQTCHART_H
#define QQTCHART_H

#include <QWidget>
#include <qqtcore.h>
#include <qqt-local.h>

/*
 * Qt Charts has a problem, you can't mod tip label's style.
*/
class QQTSHARED_EXPORT QQtChart : public QWidget
{
    Q_OBJECT
public:
    explicit QQtChart ( QWidget* parent = nullptr );

signals:

public slots:
};

#endif // QQTCHART_H
