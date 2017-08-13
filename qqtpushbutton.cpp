#include "qqtpushbutton.h"
#include "ui_qqtpushbutton.h"
#include <QStylePainter>
#include <QMouseEvent>
#include "qqtdefine.h"

QQTPushButton::QQTPushButton(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::QQTPushButton)
{
    ui->setupUi(this);
    state = BTN_NORMAL;
}

QQTPushButton::~QQTPushButton()
{
    delete ui;
}

void QQTPushButton::paintEvent(QPaintEvent *e)
{
    QStylePainter p(this);

    bool enabled = isEnabled();

    //pline() << this->objectName() << e->type() << state << m_pixmap[state];

#if 0
    /*
     * 不会报告ｌｉｂｐｎｇｗａｒｎｉｎｇ
     */
    QIcon::Mode iconFlag = QIcon::Normal;
    if(BTN_PRESS == state)
        iconFlag = QIcon::Selected;
    if(!enabled)
        iconFlag = QIcon::Disabled;
    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(m_pixmap[state]).pixmap(rect().size(), iconFlag, QIcon::On));
#else
    /*
     * 以下方法会导致图片失真 可以控制大小 可以控制图片状态 ｓｃａｌｅｄ函数打印ｌｉｂｐｎｇｗａｒｎｉｎｇ
     */
    QImage image(m_pixmap[state]);
    p.drawItemPixmap(rect(), Qt::AlignCenter, QPixmap::fromImage(image.scaled(rect().size(), Qt::IgnoreAspectRatio)));
#endif

    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawItemText(rect(), Qt::AlignCenter, opt.palette, enabled, text());
}

void QQTPushButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        state = BTN_PRESS;
        QApplication::beep();
        //pline() << state;
    }
    QPushButton::mousePressEvent(e);
}

void QQTPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
#ifdef __MIPS_LINUX__
        state = BTN_NORMAL;
        //pline() << state;
        update();
#else
        if(rect().contains(e->pos()))
            state = BTN_HOVER;
        else
            state = BTN_NORMAL;
#endif
    }
    QPushButton::mouseReleaseEvent(e);
}

void QQTPushButton::enterEvent(QEvent *e)
{
    state = BTN_HOVER;
    QPushButton::enterEvent(e);
}

void QQTPushButton::leaveEvent(QEvent *e)
{
    state = BTN_NORMAL;
    QPushButton::leaveEvent(e);
}

void QQTPushButton::changeEvent(QEvent *e)
{
    QPushButton::changeEvent(e);
}

void QQTPushButton::enabledChange(bool enabled)
{
    state = isEnabled() ? BTN_NORMAL : BTN_DISABLE;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QPushButton::enabledChange(enabled);
#else
    //TODO:
#endif
}
