#ifndef QQTDIALOG_H
#define QQTDIALOG_H

#include <QDialog>

namespace Ui {
class QQTDialog;
}

/**
 * @brief QSS
 */
class QQTDialog : public QDialog
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
