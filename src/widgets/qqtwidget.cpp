#include "qqtwidget.h"
#include <QStylePainter>
#include "qqtcore.h"

QQtWidget::QQtWidget(QWidget* parent) :
    QWidget(parent)
{
    m_style = QQTCENTER;
}

QQtWidget::~QQtWidget()
{
}

void QQtWidget::setPixmap(QString pic)
{
    m_pic = pic;
}

void QQtWidget::paintEvent(QPaintEvent* event)
{
    QStylePainter p(this);
    if (m_pic.isEmpty())
        return;

    QImage image(m_pic);
    switch (m_style)
    {
    case QQTCENTER:
        p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(m_pic).pixmap(rect().size(), QIcon::Normal, QIcon::On));
        break;
    case QQTTILEDWIDTH:
        p.drawItemPixmap(rect(), Qt::AlignLeft | Qt::AlignTop,
                         QPixmap::fromImage(image.copy(rect())
                                            .scaledToWidth(rect().width())
                                           ));
        break;
    case QQTZOOMWIDTH:
        p.drawItemPixmap(rect(), Qt::AlignLeft | Qt::AlignTop,
                         QPixmap::fromImage(image
                                            .scaled(rect().width(), image.height(), Qt::IgnoreAspectRatio)
                                           ));
        break;
    default:
        break;
    }

    return QWidget::paintEvent(event);
}


void QQtWidget::mouseReleaseEvent(QMouseEvent* event)
{
    emit click();
    return QWidget::mouseReleaseEvent(event);
}

void QQtWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit doubleClick();
    return QWidget::mouseDoubleClickEvent(event);
}
