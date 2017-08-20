#ifndef QQTTREEWIDGET_H
#define QQTTREEWIDGET_H

#include "qqttreeview.h"
#include "qqtsqltreemodel.h"
#include "qqtxmltreemodel.h"
#include "qqtfilesystemtreemodel.h"
#include "qqtcloudtreemodel.h"

namespace Ui {
class QQTTreeWidget;
}

class QQTTreeWidget : public QQTTreeView
{
    Q_OBJECT

public:
    explicit QQTTreeWidget(QWidget *parent = 0);
    ~QQTTreeWidget();

    enum {
        XMLTREE,
        SQLTREE,
        LOCALTREE,
        CLOUDTREE,
        TREEMAX
    };
    /**
     * @brief setModelType
     * @param type
     * 现在支持的模型来源类型
     */
    void setModel(int type = SQLTREE);

public slots:

private:
    Ui::QQTTreeWidget *ui;
    QQTTreeModel* mModel;
};

#endif // QQTTREEWIDGET_H
