#include "qqtcheckbox.h"
#include "ui_qqtcheckbox.h"
#include <QStylePainter>
#include "qqtwidgets.h"

QQTCheckBox::QQTCheckBox(QWidget *parent) :
    QCheckBox(parent),
    ui(new Ui::QQTCheckBox)
{
    ui->setupUi(this);
}

QQTCheckBox::~QQTCheckBox()
{
    delete ui;
}

void QQTCheckBox::pixMap(QImage &icon, QImage &iconSel)
{
    icon = QImage(this->m_icon[BTN_NORMAL]);
    iconSel = QImage(this->m_icon[BTN_PRESS]);
}

void QQTCheckBox::setPixmap(const QString &icon, const QString &iconSel)
{
    this->m_icon[BTN_NORMAL] = icon;
    this->m_icon[BTN_PRESS] = iconSel;
}


void QQTCheckBox::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);

    QString icon = isChecked() ? m_icon[BTN_PRESS] : m_icon[BTN_NORMAL];

    if(icon.isEmpty())
        return;

    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(icon).pixmap(rect().size(), QIcon::Normal, QIcon::On));
    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawItemText(rect(), Qt::AlignCenter, opt.palette, true, text());
}

bool QQTCheckBox::hitButton(const QPoint &pos) const
{
    return true;
}
