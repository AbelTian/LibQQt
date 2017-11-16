#ifndef QQTTREEWIDGET_H
#define QQTTREEWIDGET_H

#include "qqttreeview.h"
#include "qqttreemodel.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtTreeWidget : public QQtTreeView
{
    Q_OBJECT

public:
    explicit QQtTreeWidget(QWidget* parent = 0);
    virtual ~QQtTreeWidget();


public slots:

private:
    QQTTreeModel* mModel;
};

#endif // QQTTREEWIDGET_H
