#include "qqtcheckbox.h"
#include <QStylePainter>
#include "qqtwidgets.h"

QQtCheckBox::QQtCheckBox(QWidget* parent) :
    QCheckBox(parent)
{
}

QQtCheckBox::~QQtCheckBox()
{
}

void QQtCheckBox::pixMap(QImage& icon, QImage& iconSel)
{
    icon = QImage(this->m_icon[BTN_NORMAL]);
    iconSel = QImage(this->m_icon[BTN_PRESS]);
}

void QQtCheckBox::setPixmap(const QString& icon, const QString& iconSel)
{
    this->m_icon[BTN_NORMAL] = icon;
    this->m_icon[BTN_PRESS] = iconSel;
}


void QQtCheckBox::paintEvent(QPaintEvent*)
{
    QStylePainter p(this);

    QString icon = isChecked() ? m_icon[BTN_PRESS] : m_icon[BTN_NORMAL];

    if (icon.isEmpty())
        return;

    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(icon).pixmap(rect().size(), QIcon::Normal, QIcon::On));
    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawItemText(rect(), Qt::AlignCenter, opt.palette, true, text());
}

bool QQtCheckBox::hitButton(const QPoint& pos) const
{
    Q_UNUSED(pos)
    //TODO:
    return true;
}
