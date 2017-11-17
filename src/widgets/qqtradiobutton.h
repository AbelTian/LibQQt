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

    inline TBtnIconTable& iconTable() { return m_icon; }
    void pixMap(QImage& icon, QImage& iconSel);
    void pixMap(QString& icon, QString& iconSel);
    void setPixmap(const QString& icon = QString(),
                   const QString& iconSel = QString());
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
