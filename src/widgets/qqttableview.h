#ifndef QQTTABLEVIEW_H
#define QQTTABLEVIEW_H

#include <QTableView>
#include "qqtheaderview.h"
#include "qqt-local.h"

namespace Ui {
class QQTTableView;
}

class QQTSHARED_EXPORT QQTTableView : public QTableView
{
    Q_OBJECT

public:
    explicit QQTTableView(QWidget *parent = 0);
    ~QQTTableView();

    QQTHeaderView* QQTHHeader() { return m_header; }
    QQTHeaderView* QQTVHeader() { return m_vheader; }
    void setQQTHeader();
    void setQQTVHeader();
    void setObjectName(const QString &name);
private:
    Ui::QQTTableView *ui;

    QQTHeaderView* m_vheader;
    QQTHeaderView* m_header;
};

#endif // QQTTABLEVIEW_H
