#ifndef QQTTABLEWIDGET_H
#define QQTTABLEWIDGET_H

#include "qqttableview.h"
#include "qqttablemodel.h"

namespace Ui {
class QQTTableWidget;
}

class QQTTableWidget : public QQTTableView
{
    Q_OBJECT

public:
    explicit QQTTableWidget(QWidget *parent = 0);
    ~QQTTableWidget();

    void setDB(QString db = "");
    void setTable(QString table);
    void query(QString excp = "");
    //在TableWidget中，删除的行肯定是选中的行，设定
    void removeRow(int row);
    void removeRows(int column, QList<QStringList> ids);

    void selectedRows(int column, QMap<int, QStringList>& ids);
private:
    Ui::QQTTableWidget *ui;
    QQTTableModel* m_model;
    QSqlDatabase m_db;
};

#endif // QQTTABLEWIDGET_H
