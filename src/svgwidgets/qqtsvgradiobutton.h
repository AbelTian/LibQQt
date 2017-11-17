#ifndef QQTSVGRADIOBUTTON_H
#define QQTSVGRADIOBUTTON_H

#include <qqtradiobutton.h>
#include <QSvgRenderer>
#include <qqtwidgets.h>

class QQtSvgRadioButton : public QQtRadioButton
{
    Q_OBJECT
public:
    explicit QQtSvgRadioButton(QWidget* parent = nullptr);
    /**
     * @brief renderToVariable
     * call this function after iconTable() set.
     */
    void renderToVariable();
signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;
private:
    QSvgRenderer r[BTN_MAX];
};

#endif // QQTSVGRADIOBUTTON_H
