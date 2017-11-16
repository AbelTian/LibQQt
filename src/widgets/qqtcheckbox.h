#ifndef QQTCHECKBOX_H
#define QQTCHECKBOX_H

#include <QCheckBox>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqt-local.h"

/**
 * @brief The QQtCheckBox class
 * 为了图片占据全部全部控件而编写。
 */
class QQTSHARED_EXPORT QQtCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    explicit QQtCheckBox(QWidget* parent = 0);
    virtual ~QQtCheckBox();
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

#endif // QQTCHECKBOX_H
