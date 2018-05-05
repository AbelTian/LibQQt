#ifndef QQTMULTIPAGETABLEWIDGET_H
#define QQTMULTIPAGETABLEWIDGET_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QHeaderView>
#include <QTableView>
#include "qqttablewidget.h"
#include "qqt-local.h"

namespace Ui {
class QQtMultiPageTableWidget;
}

/**
 * @brief The QQtMultiPageTableWidget class
 * 关于视图规格的改变改变到上层
 * 这里的控件使用默认视图
 * 这里的控件只是Table-DB关系，没有Tree/List模型
 *
 * 第一次查询，为数据准备页面，速度较慢。
 * 后来，变动时，只有导致页数变动时才会慢一点点的感觉。
 * 平时查看，都是极速。
 */
class QQTSHARED_EXPORT QQtMultiPageTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQtMultiPageTableWidget ( QWidget* parent = 0 );
    ~QQtMultiPageTableWidget();

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
    Ui::QQtMultiPageTableWidget* ui;
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

#endif // QQTMULTIPAGETABLEWIDGET_H
