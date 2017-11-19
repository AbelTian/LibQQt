#ifndef QQTSVGPUSHBUTTON_H
#define QQTSVGPUSHBUTTON_H

#include <qqtpushbutton.h>
#include <QSvgRenderer>
#include <qqtwidgets.h>
#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtSvgPushButton : public QQtPushButton
{
    Q_OBJECT
public:
    explicit QQtSvgPushButton ( QWidget* parent = nullptr );
    virtual ~QQtSvgPushButton() {}

    /**
     * @brief renderToVariable
     * call this function after iconTable() set.
     */
    void renderToVariable();

signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;

private:
    QSvgRenderer r[BTN_MAX];

};

#endif // QQTSVGPUSHBUTTON_H
