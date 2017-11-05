#ifndef QPROGRESSWINDOW_H
#define QPROGRESSWINDOW_H

#include "qqt-local.h"
#include "qqtdialog.h"
#include "qqtprogressbar.h"

namespace Ui
{
class QQtProgressDialog;
}

class QQTSHARED_EXPORT QQtProgressDialog : public QQtDialog
{
    Q_OBJECT

public:
    explicit QQtProgressDialog(QWidget* parent = 0);
    ~QQtProgressDialog();

    void initAll();
    void setRange(int min, int max);
    void setContent(QString content);

public slots:
    void setValue(int value);

private:
    Ui::QQtProgressDialog* ui;
    QQTProgressBar* bar;
};

#endif // QPROGRESSWINDOW_H
