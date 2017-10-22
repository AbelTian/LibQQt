#include "qqtmarqueeeffectlabel.h"

QQtMarqueeEffectLabel::QQtMarqueeEffectLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    marqueeMargin = 0;
}

QQtMarqueeEffectLabel::QQtMarqueeEffectLabel(const QString& text, QWidget* parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{
    marqueeMargin = 0;
}

QQtMarqueeEffectLabel::~QQtMarqueeEffectLabel()
{
    if (timerId > 0)
    {
        killTimer(timerId);
        timerId = 0;
    }
}

int QQtMarqueeEffectLabel::interval() const
{
    return mInterval;
}

bool QQtMarqueeEffectLabel::isActive() const
{
    return active;
}

QQtMarqueeEffectLabel::Direction QQtMarqueeEffectLabel::direction() const
{
    return mDirection;
}

void QQtMarqueeEffectLabel::setAlignment(Qt::Alignment align)
{
    switch (mDirection)
    {
    case RightToLeft:
        QLabel::setAlignment(Qt::AlignLeft
                             | (align & Qt::AlignVertical_Mask));
        break;
    case BottomToTop:
    default:
        QLabel::setAlignment(Qt::AlignTop
                             | (align & Qt::AlignHorizontal_Mask));
    }
}

void QQtMarqueeEffectLabel::reset()
{
    if (timerId != 0)
    {
        killTimer(timerId);
        timerId = 0;
    }
    bool bActiveChanged = false;
    if (active)
    {
        active = false;
        bActiveChanged = true;
    }
    marqueeMargin = 0;
    setContentsMargins(0, 0, 0, 0);
    update();

    if (bActiveChanged)
    {
        Q_EMIT activeChanged(active);
    }
}

void QQtMarqueeEffectLabel::setActive(bool active)
{
    if (this->active == active)
    {
        return;
    }
    if (active)
    {
        start();
    }
    else
    {
        stop();
    }
}

void QQtMarqueeEffectLabel::setInterval(int msec)
{
    if (msec < 1)
    {
        return;
    }
    if (mInterval != msec)
    {
        mInterval = msec;
        if (timerId != 0)
        {
            killTimer(timerId);
            timerId = startTimer(mInterval);
        }
        Q_EMIT intervalChanged(mInterval);
    }
}

void QQtMarqueeEffectLabel::start()
{
    bool bActiveChanged = false;
    if (!active)
    {
        active = true;
        bActiveChanged = true;
    }
    if (!mouseIn)
    {
        if (timerId == 0)
        {
            timerId = startTimer(mInterval);
        }
        setContentsMargins(0, 0, 0, 0);
    }

    if (bActiveChanged)
    {
        Q_EMIT activeChanged(active);
    }
}

void QQtMarqueeEffectLabel::stop()
{
    bool bActiveChanged = false;
    if (active)
    {
        active = false;
        bActiveChanged = true;
    }
    if (!mouseIn)
    {
        if (timerId != 0)
        {
            killTimer(timerId);
            timerId = 0;
        }
        switch (mDirection)
        {
        case RightToLeft:
            setContentsMargins(marqueeMargin, 0, 0, 0);
            break;
        case BottomToTop:
        default:
            setContentsMargins(0, marqueeMargin, 0, 0);
        }
    }

    if (bActiveChanged)
    {
        Q_EMIT activeChanged(active);
    }
}

void QQtMarqueeEffectLabel::setDirection(QQtMarqueeEffectLabel::Direction param_direciton)
{
    if (param_direciton == mDirection)
    {
        return;
    }
    mDirection = param_direciton;
    switch (mDirection)
    {
    case RightToLeft:
        setAlignment(Qt::AlignLeft
                     | (alignment() & Qt::AlignVertical_Mask));
        break;
    case BottomToTop:
    default:
        setAlignment(Qt::AlignTop
                     | (alignment() & Qt::AlignHorizontal_Mask));
    }
    marqueeMargin = 0;
    setContentsMargins(0, 0, 0, 0);
    update();
    Q_EMIT directionChanged(mDirection);
}

void QQtMarqueeEffectLabel::enterEvent(QEvent* event)
{
    mouseIn = true;
    if (active)
    {
        if (timerId != 0)
        {
            killTimer(timerId);
            timerId = 0;
        }
        switch (mDirection)
        {
        case RightToLeft:
            setContentsMargins(marqueeMargin, 0, 0, 0);
            break;
        case BottomToTop:
        default:
            setContentsMargins(0, marqueeMargin, 0, 0);
        }
    }
    QLabel::enterEvent(event);
}

void QQtMarqueeEffectLabel::leaveEvent(QEvent* event)
{
    mouseIn = false;
    if (active)
    {
        if (timerId == 0)
        {
            timerId = startTimer(mInterval);
        }
        setContentsMargins(0, 0, 0, 0);
    }
    QLabel::leaveEvent(event);
}

void QQtMarqueeEffectLabel::resizeEvent(QResizeEvent* event)
{
    QLabel::resizeEvent(event);
    int w;
    switch (mDirection)
    {
    case RightToLeft:
        w = event->size().width();
        break;
    case BottomToTop:
    default:
        w = event->size().height();
    }
    if (marqueeMargin > w)
    {
        marqueeMargin = w;
        update();
    }
}

void QQtMarqueeEffectLabel::timerEvent(QTimerEvent* event)
{
    QLabel::timerEvent(event);
    if (timerId != 0 && event->timerId() == timerId)
    {
        marqueeMargin--;
        int w, w2;
        switch (mDirection)
        {
        case RightToLeft:
            w = sizeHint().width();
            w2 = width();
            break;
        case BottomToTop:
        default:
            w = sizeHint().height();
            w2 = height();
        }
        if (marqueeMargin < 0 && -marqueeMargin > w)
        {
            marqueeMargin = w2;
        }
        update();
    }
}

void QQtMarqueeEffectLabel::paintEvent(QPaintEvent* event)
{
    switch (mDirection)
    {
    case RightToLeft:
        setContentsMargins(marqueeMargin, 0, 0, 0);
        break;
    case BottomToTop:
    default:
        setContentsMargins(0, marqueeMargin, 0, 0);
    }
    QLabel::paintEvent(event);

    if (timerId != 0)
    {
        setContentsMargins(0, 0, 0, 0);
    }
}
