#include "qqtslideeffecttabbar.h"
#include <QMouseEvent>
#include <QPalette>
#include <qqtcore.h>

QQtSlideEffectTabBar::QQtSlideEffectTabBar(QWidget* parent) : QQtTabBar(parent)
{
    slideSpeed = 10;
    cornerRadius = 6;
    timer = new QTimer(this);
    timer->setInterval(100);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTabBarRect()));
}

void QQtSlideEffectTabBar::setSlideSpeed(int slideSpeed)
{
    if (this->slideSpeed != slideSpeed)
    {
        this->slideSpeed = slideSpeed;
    }
}

void QQtSlideEffectTabBar::setCornerRadius(int cornerRadius)
{
    if (this->cornerRadius != cornerRadius)
    {
        this->cornerRadius = cornerRadius;
        update();
    }
}


void QQtSlideEffectTabBar::paintEvent(QPaintEvent* event)
{
    int width = this->width();
    int height = this->height();

    /*绘制准备工作,启用反锯齿,等比例缩放*/
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    /*更改刻度 设置的是放大的倍数 */
    /*有利于在绘制的时候，统一绘制数据*/
    /*矢量放大，不失真*/
    /*
     * 不更改刻度，使用实际值
     */
    //painter.scale(width / 200.0, height / 200.0);

    drawBackground(&painter);
    drawTabBar(&painter);
    drawTabBarIcon(&painter);
    drawTabBarText(&painter);
}

void QQtSlideEffectTabBar::drawBackground(QPainter* painter)
{
    painter->save();
    QPalette pale = palette();
    painter->setBrush(pale.background());
    painter->drawRoundRect(rect(), cornerRadius, cornerRadius);
    painter->restore();
}

void QQtSlideEffectTabBar::drawTabBar(QPainter* painter)
{
    painter->save();
    QPalette pale = palette();
    painter->setBrush(pale.button());
    painter->drawRoundedRect(m_barRect, cornerRadius, cornerRadius);
    painter->restore();
}

void QQtSlideEffectTabBar::drawTabBarIcon(QPainter* painter)
{

}

void QQtSlideEffectTabBar::drawTabBarText(QPainter* painter)
{
    painter->save();

    for (int i = 0; i < count(); i++)
    {
        QPalette pale = palette();

        if (i == currentIndex())
            painter->setBrush(pale.buttonText());
        else
            painter->setBrush(pale.windowText());

        QRect textRect = tabRect(i);
        painter->drawText(textRect, Qt::AlignCenter, tabText(i));
    }

    painter->restore();
}

void QQtSlideEffectTabBar::updateTabBarRect()
{
    if (m_targetRect.top() == m_barRect.top())
    {
        // right direction
        if (m_barRect.left() < m_targetRect.left())
        {
            if (m_barRect.left() + slideSpeed < m_targetRect.left())
            {
                m_barRect.setRect(m_barRect.left() + slideSpeed, m_barRect.top(),
                                  m_targetRect.width(), m_targetRect.height());
                timer->start();
            }
            else
            {
                m_barRect = m_targetRect;
            }
        }
        // left direction
        else if (m_barRect.left() > m_targetRect.left())
        {
            if (m_barRect.left() - slideSpeed > m_targetRect.left())
            {
                m_barRect.setRect(m_barRect.left() - slideSpeed, m_barRect.top(),
                                  m_targetRect.width(), m_targetRect.height());
                timer->start();
            }
            else
            {
                m_barRect = m_targetRect;
            }
        }
    }
    else
    {
        // down direction
        if (m_barRect.top() < m_targetRect.top())
        {
            if (m_barRect.top() + slideSpeed < m_targetRect.top())
            {
                m_barRect.setRect(m_barRect.left(), m_barRect.top() + slideSpeed,
                                  m_targetRect.width(), m_targetRect.height());
                timer->start();
            }
            else
            {
                m_barRect = m_targetRect;
            }
        }
        // up direction
        else if (m_barRect.top() > m_targetRect.top())
        {
            if (m_barRect.top() - slideSpeed > m_targetRect.top())
            {
                m_barRect.setRect(m_barRect.left(), m_barRect.top() - slideSpeed,
                                  m_targetRect.width(), m_targetRect.height());
                timer->start();
            }
            else
            {
                m_barRect = m_targetRect;
            }
        }
    }

    update();
}


void QQtSlideEffectTabBar::mousePressEvent(QMouseEvent* event)
{
    m_barRect = tabRect(currentIndex());

    for (int i = 0 ; i < count(); i++)
    {
        if (tabRect(i).contains(event->pos()) && i != currentIndex())
        {
            m_targetRect = tabRect(i);
            timer->start();
            break;
        }
    }

    return QTabBar::mousePressEvent(event);
}

void QQtSlideEffectTabBar::mouseReleaseEvent(QMouseEvent* event)
{
    return QTabBar::mouseReleaseEvent(event);
}
