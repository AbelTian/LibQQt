#include "qqtmsgbox.h"
#include "ui_qqtmsgbox.h"
#include "qqtcore.h"

QQtMsgBox::QQtMsgBox(QWidget* parent) :
    QQtDialog(parent),
    ui(new Ui::QQtMsgBox)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose, true);

    connect(ui->btnYes, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->btnNo, SIGNAL(clicked()), this, SLOT(reject()));

    delayShow = 100;

    pline() << qApp->desktop()->size();

    if (qApp->desktop()->size() == QSize(1024, 768))
    {

        widgetW = 401;
        widgetH = 235;
        btnW = 104;
        btnH = 40;
        botoomH = widgetH / 7 * 3;
        xSpaceYes = (widgetW - btnW - 12) / 2;
        xSpaceYesNo = (widgetW - btnW * 2 - 12) / 3;
        ySpace = (botoomH - btnH) / 2;

        pline() << widgetW << widgetH;
        pline() << btnW << btnH;
        pline() << botoomH;
        pline() << xSpaceYes << xSpaceYesNo << ySpace;

        setFixedSize(widgetW, widgetH);

        //size
        ui->btnNo->setFixedSize(btnW, btnH);
        ui->btnYes->setFixedSize(btnW, btnH);
        ui->widgetBottom->setFixedHeight(botoomH);

        //text
        ui->btnNo->setText("");
        ui->btnYes->setText("");

        //pic
        ui->btnNo->iconTable().initNormal("./skin/default/bt_back_normal.png",
                                          "./skin/default/bt_back_press.png");
        ui->btnNo->iconTable().initOther("./skin/default/bt_back_hover.png",
                                         "./skin/default/bt_back_disable.png");

        ui->btnYes->iconTable().initNormal("./skin/default/bt_login_normal.png",
                                           "./skin/default/bt_login_press.png");
        ui->btnYes->iconTable().initOther("./skin/default/bt_login_hover.png",
                                          "./skin/default/bt_login_disable.png");

    }
    else if (qApp->desktop()->size() == QSize(800, 480))
    {
        widgetW = 300;
        widgetH = 160;
        btnW = 80;
        btnH = 30;
        botoomH = widgetH / 7 * 3;
        xSpaceYes = (widgetW - btnW - 12) / 2;
        xSpaceYesNo = (widgetW - btnW * 2 - 12) / 3;
        ySpace = (botoomH - btnH) / 2;

        pline() << widgetW << widgetH;
        pline() << btnW << btnH;
        pline() << botoomH;
        pline() << xSpaceYes << xSpaceYesNo << ySpace;

        setFixedSize(widgetW, widgetH);

        //size
        ui->btnNo->setFixedSize(btnW, btnH);
        ui->btnYes->setFixedSize(btnW, btnH);
        ui->widgetBottom->setFixedHeight(botoomH);
    }

}

QQtMsgBox::~QQtMsgBox()
{
    delete ui;
}



int QQtMsgBox::warning(QWidget* parent, QString content)
{
    QQtMsgBox* msgBox = new QQtMsgBox(parent);

    return msgBox->_warning(content);
}

int QQtMsgBox::question(QWidget* parent, QString content)
{
    QQtMsgBox* msgBox = new QQtMsgBox(parent);
    return msgBox->_question(content);
}

int QQtMsgBox::_warning(QString content)
{
    ui->lbContent->setText(content);
    showYes();;
    return exec();
}

int QQtMsgBox::_question(QString content)
{
    ui->lbContent->setText(content);
    showYesAndNo();
    return exec();
}

void QQtMsgBox::showYes()
{
    ui->btnYes->setHidden(false);
    ui->btnNo->setHidden(true);
    int x0 = xSpaceYes;
    int y0 = ySpace;
    ui->btnYes->setGeometry(x0, y0, btnW, btnH);
}

void QQtMsgBox::showYesAndNo()
{
    ui->btnYes->setHidden(false);
    ui->btnNo->setHidden(false);
    int x0 = xSpaceYesNo;
    int y0 = ySpace;
    ui->btnYes->setGeometry(x0, y0, btnW, btnH);
    ui->btnNo->setGeometry(x0 + btnW + x0, y0, btnW, btnH);
}

void QQtMsgBox::showNull()
{
    ui->btnYes->setHidden(true);
    ui->btnNo->setHidden(true);
}






void QQtMsgBox::warning(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lbContent->setText(content);
    showYes();
    m_time = 0;
    //startTimer(1000);
    show();
    QQtSleep(delayShow);
}

void QQtMsgBox::question(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lbContent->setText(content);
    showYesAndNo();
    m_time = 0;
    //startTimer(1000);
    show();
    QQtSleep(delayShow);
}

void QQtMsgBox::information(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lbContent->setText(content);
    showNull();
    m_time = 0;
    //startTimer(1000);
    show();
    QQtSleep(delayShow);
}

void QQtMsgBox::timerEvent(QTimerEvent* e)
{
    return;

    if (m_time > 5)
    {
        killTimer(e->timerId());
        reject();
        return;
    }

    m_time ++ ;
}
