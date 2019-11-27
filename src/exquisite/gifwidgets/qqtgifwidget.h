#ifndef QQTGIFWIDGET_H
#define QQTGIFWIDGET_H

#include <qqtwidget.h>
#include <qqt-local.h>
#include <qqtcore.h>

#include <QMovie>
#include <QTimer>

class QQTSHARED_EXPORT QQtGifWidget : public QQtWidget
{
    Q_OBJECT
public:
    explicit QQtGifWidget ( QWidget* parent = nullptr );
    virtual ~QQtGifWidget() {}

    void setGifFile ( QString gifFile );

    inline QMovie* movieHandler() const { return m_movie; }
    inline QTimer* timerHandler() const { return m_frameTimer; }
signals:

public slots:

private:
    QMovie* m_movie;
    QTimer* m_frameTimer;

protected slots:
    virtual void slotFramePlayback();
};

#endif // QQTGIFWIDGET_H
