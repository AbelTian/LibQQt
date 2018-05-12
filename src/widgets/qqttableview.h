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

    QQtHeaderView* QQTHHeader() { return m_header; }
    QQtHeaderView* QQTVHeader() { return m_vheader; }
    void setQQTHeader();
    void setQQTVHeader();
    void setObjectName(const QString& name);
private:

    QQtHeaderView* m_vheader;
    QQtHeaderView* m_header;
};

#endif // QQTTABLEVIEW_H
