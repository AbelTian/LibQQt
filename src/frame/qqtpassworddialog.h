#ifndef QQTPASSWORDDIALOG_H
#define QQTPASSWORDDIALOG_H

#include "qqtdialog.h"
#include "qqt-local.h"

namespace Ui {
class QQtPasswordDialog;
}

class QQTSHARED_EXPORT QQtPasswordDialog : public QQtDialog
{
    Q_OBJECT

public:
    explicit QQtPasswordDialog ( QWidget* parent = 0 );
    virtual ~QQtPasswordDialog();

    void setWifiName ( QString name );
    QString wifiPwd();

signals:
    void connectClicked ( QString password );
private slots:
    void connectClicked();
    void btnEnabled ( QString );

private:
    Ui::QQtPasswordDialog* ui;
};

#endif // QQTPASSWORDDIALOG_H
