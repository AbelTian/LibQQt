#ifndef HTTPDOWNLOADDIALOG_H
#define HTTPDOWNLOADDIALOG_H

#include <QDialog>

namespace Ui {
class HttpDownloadDialog;
}

class HttpDownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HttpDownloadDialog(QWidget *parent = 0);
    ~HttpDownloadDialog();

private:
    Ui::HttpDownloadDialog *ui;
};

#endif // HTTPDOWNLOADDIALOG_H
