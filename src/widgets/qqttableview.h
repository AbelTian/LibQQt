#ifndef QQTTABLEVIEW_H
#define QQTTABLEVIEW_H

#include <QTableView>
#include "qqtheaderview.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtTableView : public QTableView
{
    Q_OBJECT

public:
    explicit QQtTableView(QWidget* parent = 0);
    virtual ~QQtTableView();

    QQTHeaderView* QQTHHeader() { return m_header; }
    QQTHeaderView* QQTVHeader() { return m_vheader; }
    void setQQTHeader();
    void setQQTVHeader();
    void setObjectName(const QString& name);
private:

    QQTHeaderView* m_vheader;
    QQTHeaderView* m_header;
};

#endif // QQTTABLEVIEW_H
