#ifndef QQTDIALOG_H
#define QQTDIALOG_H

#include <QDialog>
#include <qqt.h>

namespace Ui {
class QQTDialog;
}

/**
 * @brief QSS
 */
class QQTSHARED_EXPORT QQTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QQTDialog(QWidget *parent = 0);
    ~QQTDialog();

private:
    Ui::QQTDialog *ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QQTDIALOG_H
