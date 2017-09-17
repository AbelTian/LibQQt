#ifndef QQTRADIOBUTTON_H
#define QQTRADIOBUTTON_H

#include <QRadioButton>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqt-local.h"

namespace Ui {
class QQTRadioButton;
}

class QQTSHARED_EXPORT QQTRadioButton : public QRadioButton
{
    Q_OBJECT

public:
    explicit QQTRadioButton(QWidget *parent = 0);
    ~QQTRadioButton();

    void pixMap(QImage& m_icon, QImage& m_iconSel);
    void setPixmap(const QString& m_icon = QString(), const QString &m_iconSel = QString());
private:
    Ui::QQTRadioButton *ui;
    TBtnIconTable m_icon;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QAbstractButton interface
protected:
    bool hitButton(const QPoint &pos) const;
};

#endif // QQTRADIOBUTTON_H
