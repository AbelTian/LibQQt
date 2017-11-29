#ifndef QQTCHECKBOX_H
#define QQTCHECKBOX_H

#include <QCheckBox>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqt-local.h"
#include <qqtwidgets.h>

/**
 * @brief The QQtCheckBox class
 * 为了图片占据全部全部控件而编写。
 */
class QQTSHARED_EXPORT QQtCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    explicit QQtCheckBox ( QWidget* parent = 0 );
    virtual ~QQtCheckBox();

    inline TBtnIconTable& iconTable() { return m_icon; }
    void pixMap ( QImage& icon, QImage& iconSel ) const;
    void pixMap ( QString& icon, QString& iconSel ) const;
    void setPixmap ( const QString& icon = QString(),
                     const QString& iconSel = QString() );

private:
    TBtnIconTable m_icon;

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* ) override;

    // QAbstractButton interface
protected:
    bool hitButton ( const QPoint& pos ) const;
};

#endif // QQTCHECKBOX_H
