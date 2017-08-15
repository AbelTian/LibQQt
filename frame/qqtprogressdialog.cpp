#include "qqtprogressdialog.h"
#include "ui_qqtprogressdialog.h"
#include "qqtdefine.h"
#include "qqtobjectfactory.h"

QQTProgressDialog::QQTProgressDialog(QWidget *parent) :
    QQTDialog(parent),
    ui(new Ui::QQTProgressDialog)
{
    ui->setupUi(this);
    bar = ui->widgetBar;
    bar->setRange(0, 100);
    bar->setValue(0);

    connect(ui->btnCancel, SIGNAL(clicked()),
            this, SLOT(reject()));

    //setFixedWidth(260);

#ifdef __QQTWIDGETS_K1160__
    setFixedSize(526, 283);
    bar->setFixedSize(481, 31);
    bar->move(20, 50);

    ui->btnCancel->setText("");
    ui->btnCancel->setFixedSize(104, 40);
    ui->btnCancel->iconTable().initNormal("./skin/default/bt_back_normal.png",
                                      "./skin/default/bt_back_press.png" );
    ui->btnCancel->iconTable().initOther("./skin/default/bt_back_hover.png",
                                     "./skin/default/bt_back_disable.png");

    ui->widgetBar->setPixMap("./skin/default/bk_progress_background.png",
                             "./skin/default/bk_progress_chunk.png");
#endif

    QQTObjectFactory::registerObject(this);
    QQTObjectFactory::registerObject(ui->btnCancel);
}

QQTProgressDialog::~QQTProgressDialog()
{
    delete ui;
}

void QQTProgressDialog::initAll()
{
    bar->setRange(0, 100);
    bar->setValue(0);
}

void QQTProgressDialog::setRange(int min, int max)
{
    bar->setRange(min, max);
}

void QQTProgressDialog::setContent(QString content)
{
    ui->label->setText(content);
}

void QQTProgressDialog::setValue(int value)
{
    bar->setValue(value);
}

