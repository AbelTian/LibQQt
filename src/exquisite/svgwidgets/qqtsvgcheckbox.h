#ifndef QQTSVGCHECKBOX_H
#define QQTSVGCHECKBOX_H

#include <qqtcheckbox.h>
#include <QSvgRenderer>
#include <qqtwidgets.h>
#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtSvgCheckBox : public QQtCheckBox
{
    Q_OBJECT
public:
    explicit QQtSvgCheckBox ( QWidget* parent = nullptr );

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

#endif // QQTSVGCHECKBOX_H
