#include "qqtsvgpushbutton.h"

QQtSvgPushButton::QQtSvgPushButton(QWidget* parent) : QQtPushButton(parent)
{

}

void QQtSvgPushButton::renderToVariable()
{
    TBtnIconTable& pic = iconTable();

    for (int i = 0; i < BTN_MAX; i++)
        r[i].load(pic[i]);
}



void QQtSvgPushButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QStylePainter p(this);
    EBtnStatus bs = btnStatus();
    if (r[bs].isValid())
        r[bs].render(&p);

    bool enabled = isEnabled();
    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawItemText(rect(), Qt::AlignCenter, opt.palette, enabled, text());
}
