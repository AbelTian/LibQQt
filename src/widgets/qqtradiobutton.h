#ifndef QQTRADIOBUTTON_H
#define QQTRADIOBUTTON_H

#include <QRadioButton>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtRadioButton : public QRadioButton
{
    Q_OBJECT

public:
    explicit QQtRadioButton(QWidget* parent = 0);
    virtual ~QQtRadioButton();

    void pixMap(QImage& m_icon, QImage& m_iconSel);
    void setPixmap(const QString& m_icon = QString(), const QString& m_iconSel = QString());
private:
    TBtnIconTable m_icon;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);

    // QAbstractButton interface
protected:
    bool hitButton(const QPoint& pos) const;
};

#endif // QQTRADIOBUTTON_H
