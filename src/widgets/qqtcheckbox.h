#ifndef QQTCHECKBOX_H
#define QQTCHECKBOX_H

#include <QCheckBox>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqt-local.h"

namespace Ui {
class QQTCheckBox;
}
/**
 * @brief The QQTCheckBox class
 * 为了图片占据全部全部控件而编写。
 */
class QQTSHARED_EXPORT QQTCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    explicit QQTCheckBox(QWidget *parent = 0);
    ~QQTCheckBox();
    void pixMap(QImage& m_icon, QImage& m_iconSel);
    void setPixmap(const QString& m_icon = QString(), const QString &m_iconSel = QString());

private:
    Ui::QQTCheckBox *ui;
    TBtnIconTable m_icon;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QAbstractButton interface
protected:
    bool hitButton(const QPoint &pos) const;
};

#endif // QQTCHECKBOX_H
