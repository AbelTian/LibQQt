#ifndef QQTMPTABLEWIDGET_H
#define QQTMPTABLEWIDGET_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QHeaderView>
#include <QTableView>
#include "qqttablewidget.h"
#include "qqt-local.h"

namespace Ui {
class QQtMPTableWidget;
}

/**
 * @brief The QQtMPTableWidget class
 * 关于视图规格的改变改变到上层
 * 这里的控件使用默认视图
 * 这里的控件只是Table-DB关系，没有Tree/List模型
 */
class QQTSHARED_EXPORT QQtMPTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQtMPTableWidget ( QWidget* parent = 0 );
    ~QQtMPTableWidget();

    void setDB ( QString db );
    void setTable ( QString table );
    void setRelation ( int column, const QSqlRelation& relation );
    void setRecordNumPerPage ( int num );
    void setColumnHidden ( int key, bool value = true );
    void setSelectionMode ( QAbstractItemView::SelectionMode mode = QAbstractItemView::MultiSelection );
    void setResizeMode ( QHeaderView::ResizeMode mode = QHeaderView::ResizeToContents );
    void setResizeMode ( int column, QHeaderView::ResizeMode mode = QHeaderView::ResizeToContents );
    void setAlternatingRowColors ( bool alt = true );
    void setHeaderData ( Qt::Orientation, QStringList dataList );
    void setHeaderData ( int i, Qt::Orientation, QString data );
    void setColumnWidth ( int column, int width );
    void query ( QString filter = "1=1" );
    void selectedRows ( int column, QVector<QStringList>& strl );
    QQtTableWidget* selectedRows ( int column = 0 );
    int pageNum();
    int currentPage();
    //1-pagenum
    void setCurrentPage ( int page );

public slots:
    void removeSelectedRows ( int column = 0 );

private slots:
    void on_btnLeft_clicked();

    void on_btnRight_clicked();

    void on_btnJump_clicked();

    void on_btnLeftHead_clicked();

    void on_btnRightHead_clicked();

private:
    Ui::QQtMPTableWidget* ui;
    QSqlDatabase m_db;
    QString m_name;
    QString m_table;
    int m_numPerPage ;
    int m_pageNum;
    QHash<int, QSqlRelation> m_columnRelation;
    QHash<int, bool> m_columnHidden;
    QHash<int, QString> m_headerData;
    QHash<int, int> m_columnWidth;
    QHeaderView::ResizeMode resizeMode;
    QHash<int, QHeaderView::ResizeMode> m_resizeMode;
    QAbstractItemView::SelectionMode selectionMode;
    bool altColor;
};

#endif // QQTMPTABLEWIDGET_H
