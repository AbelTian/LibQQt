#include "qqtheaderview.h"
#include <QPainter>
#include "qqtwidgets.h"
#include <QStylePainter>
#include <QPaintEvent>
#include <QStandardItemModel>
#include <QStringListModel>

QQTHeaderView::QQTHeaderView(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent), ori(orientation)
{
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet("QHeaderView, QHeaderView::section{background:transparent;}");
}

void QQTHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->drawText(rect, Qt::AlignCenter, model()->headerData(logicalIndex, ori).toString());
}

QSize QQTHeaderView::sectionSizeFromContents(int logicalIndex) const
{
    /*
     * 文字宽度 不是section宽度
     */
    return QHeaderView::sectionSizeFromContents(logicalIndex);
}

void QQTHeaderView::paintEvent(QPaintEvent *e)
{
    QStylePainter p(this->viewport());
    if(Qt::Horizontal == ori)
    {
        for(int i = 0; i < model()->columnCount(); i++)
        {
            if(isSectionHidden(i))
                continue;
            QRect rect(sectionViewportPosition(i), 0, sectionSize(i), height());
            paintSection(&p, rect, i);
        }
    }
    else if(Qt::Vertical == ori)
    {
        for(int i = 0; i < model()->rowCount(); i++)
        {
            QRect rect(0, sectionViewportPosition(i), width(), sectionSize(i));
            paintSection(&p, rect, i);
        }
    }

    return;
}
