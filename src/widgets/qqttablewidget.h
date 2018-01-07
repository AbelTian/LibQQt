#ifndef QQTTABLEWIDGET_H
#define QQTTABLEWIDGET_H

#include "qqttableview.h"
#include "qqttablemodel.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtTableWidget : public QQtTableView
{
    Q_OBJECT

public:
    explicit QQtTableWidget(QWidget* parent = 0);
    virtual ~QQtTableWidget();

    void setDB(QString db = "");
    void setTable(QString table);
    void query(QString excp = "");
    /*
     * 在TableWidget中，删除的行肯定是选中的行，设定
     */
    void removeRow(int row);
    /**
     * @brief removeRows
     * @param column 根据这一列的值进行删除
     * @param ids 需要删除的列值列表
     */
    void removeRows(int column, QList<QStringList> ids);
    void selectedRows(int column, QMap<int, QStringList>& ids);

    /*
     * 用于将表列动态显示到其他控件上。
     */
private:
    QQtTableModel* m_model;
    QSqlDatabase m_db;
};

#endif // QQTTABLEWIDGET_H
