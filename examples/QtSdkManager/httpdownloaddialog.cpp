#include "httpdownloaddialog.h"
#include "ui_httpdownloaddialog.h"

HttpDownloadDialog::HttpDownloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HttpDownloadDialog)
{
    ui->setupUi(this);
}

HttpDownloadDialog::~HttpDownloadDialog()
{
    delete ui;
}
