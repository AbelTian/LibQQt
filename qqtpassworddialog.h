#ifndef QQTPASSWORDDIALOG_H
#define QQTPASSWORDDIALOG_H

#include "qqtdialog.h"

namespace Ui {
class QQTPasswordDialog;
}

class QQTPasswordDialog : public QQTDialog
{
    Q_OBJECT

public:
    explicit QQTPasswordDialog(QWidget *parent = 0);
    ~QQTPasswordDialog();

    void setWifiName(QString name);
    QString wifiPwd();

signals:
    void connectClicked(QString password);
private slots:
    void connectClicked();
    void btnEnabled(QString);

private:
    Ui::QQTPasswordDialog *ui;
};

#endif // QQTPASSWORDDIALOG_H
