#ifndef QQTGIFPROGRESSBAR_H
#define QQTGIFPROGRESSBAR_H

#include <qqtgifwidget.h>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtGifProgressBar : public QQtGifWidget
{
    Q_OBJECT
public:
    explicit QQtGifProgressBar ( QWidget* parent = nullptr );

    void setGifFile ( QString back, QString trunk );

public slots:
    void setValue ( int value );
    void setRange ( int min, int max );

private:

private:
    QQtGifWidget* widgetBack, *widgetTrunk;
    int m_min, m_max, m_value;

signals:

public slots:
};

#endif // QQTGIFPROGRESSBAR_H
