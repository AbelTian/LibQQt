#ifndef QQTPROGRESSBAR_H
#define QQTPROGRESSBAR_H

#include <qqtwidget.h>
#include "qqt-local.h"
#include "qqtwidgets.h"
#include "qqtframe.h"

namespace Ui {
class QQtProgressBar;
}

/**
 * @brief The QQtProgressBar class
 * 原装QtProgressBar，在板子上Dialog里paint的时候发生异常，所以重写。
 * 行为约束：图片的大小和Bar的宽度必须相等，不容易失真
 */
class QQTSHARED_EXPORT QQtProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit QQtProgressBar ( QWidget* parent = 0 );
    virtual ~QQtProgressBar();

    void setPixMap ( QString back, QString trunk );
public slots:
    void setValue ( int value );
    void setRange ( int min, int max );

private:
    Ui::QQtProgressBar* ui;

private:
    QString m_back, m_trunk;
    int m_min, m_max, m_value;
};

#endif // QQTPROGRESSBAR_H
