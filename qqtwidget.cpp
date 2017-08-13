#include "qqtwidget.h"
#include "ui_qqtwidget.h"
#include <QStylePainter>
#include "qqtdefine.h"

QQTWidget::QQTWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQTWidget)
{
    ui->setupUi(this);
    m_type = QQTCENTER;
}

QQTWidget::~QQTWidget()
{
    delete ui;
}

void QQTWidget::setPixmap(QString pic)
{
    m_pic = pic;
}

void QQTWidget::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    if(m_pic.isEmpty())
        return;

    QImage image(m_pic);
    switch (m_type) {
    case QQTCENTER:
        p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(m_pic).pixmap(rect().size(), QIcon::Normal, QIcon::On));
        break;
    case QQTTILEDWIDTH:
        /*
         * 会产生label的效果，左右按照rect长，但是不缩放形状
         **/
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
}
