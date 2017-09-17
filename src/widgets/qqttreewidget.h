#ifndef QQTTREEWIDGET_H
#define QQTTREEWIDGET_H

#include "qqttreeview.h"
#include "qqttreemodel.h"
#include "qqt.h"

namespace Ui {
class QQTTreeWidget;
}

class QQTSHARED_EXPORT QQTTreeWidget : public QQTTreeView
{
    Q_OBJECT

public:
    explicit QQTTreeWidget(QWidget *parent = 0);
    ~QQTTreeWidget();


public slots:

private:
    Ui::QQTTreeWidget *ui;
    QQTTreeModel* mModel;
};

#endif // QQTTREEWIDGET_H
