#ifndef QQTDIALOG_H
#define QQTDIALOG_H

#include <QDialog>
#include <qqt-local.h>

/**
 * @brief QSS
 */
class QQTSHARED_EXPORT QQtDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QQtDialog(QWidget* parent = 0);
    virtual ~QQtDialog();

private:
};

#endif // QQTDIALOG_H
