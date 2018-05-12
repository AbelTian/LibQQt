#include "qqtpassworddialog.h"
#include "ui_qqtpassworddialog.h"

QQtPasswordDialog::QQtPasswordDialog(QWidget* parent) :
    QQtDialog(parent),
    ui(new Ui::QQtPasswordDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, false);
    /*
     * 阻挡父亲窗口内其他控件，除非本dialog关闭 show的功能强大起来 可以使用输入法
     */
    setWindowModality(Qt::WindowModal);
    ui->lineEdit_ssid_password->setEchoMode(QLineEdit::Password);
    ui->pushButton_ssid_connect->setEnabled(false);
    connect(ui->pushButton_ssid_connect, SIGNAL(clicked()), this, SLOT(connectClicked()));
    connect(ui->lineEdit_ssid_password, SIGNAL(textChanged(QString)), SLOT(btnEnabled(QString)));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

QQtPasswordDialog::~QQtPasswordDialog()
{
    delete ui;
}

void QQtPasswordDialog::setWifiName(QString name)
{
    ui->label_ssid_name->setText(name);
}

QString QQtPasswordDialog::wifiPwd()
{
    return ui->lineEdit_ssid_password->text();
}

void QQtPasswordDialog::connectClicked()
{
    emit connectClicked(ui->lineEdit_ssid_password->text());
    accept();
}

void QQtPasswordDialog::btnEnabled(QString pas)
{
    bool enable = pas.length() < 8 ? false : true;
    ui->pushButton_ssid_connect->setEnabled(enable);
}
