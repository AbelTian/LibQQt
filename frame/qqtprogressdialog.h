#ifndef QPROGRESSWINDOW_H
#define QPROGRESSWINDOW_H

#include "qqtdialog.h"
#include "qqtprogressbar.h"

namespace Ui {
class QQTProgressDialog;
}

class QQTProgressDialog : public QQTDialog
{
    Q_OBJECT

public:
    explicit QQTProgressDialog(QWidget *parent = 0);
    ~QQTProgressDialog();

    void initAll();
    void setRange(int min, int max);
    void setContent(QString content);

public slots:
    void setValue(int value);

private:
    Ui::QQTProgressDialog *ui;
    QQTProgressBar* bar;
};

#endif // QPROGRESSWINDOW_H
