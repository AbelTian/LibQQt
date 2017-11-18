#ifndef QQTSVGPROGRESSBAR_H
#define QQTSVGPROGRESSBAR_H

#include <qqtsvgwidget.h>
#include <QSvgRenderer>
#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtSvgProgressBar : public QQtSvgWidget
{
    Q_OBJECT
public:
    explicit QQtSvgProgressBar ( QWidget* parent = nullptr );

    void setSvgFile ( QString back, QString trunk );
public slots:
    void setValue ( int value );
    void setRange ( int min, int max );

private:
    //svg trunk can't know background width
    //so trunk display a complete svg picture but out of shape
    //don't rewrite
private:
    QQtSvgWidget* widgetBack, *widgetTrunk;
    int m_min, m_max, m_value;
};

#endif // QQTSVGPROGRESSBAR_H
