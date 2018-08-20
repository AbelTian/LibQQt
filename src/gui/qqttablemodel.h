#ifndef QQTTABLEMODEL_H
#define QQTTABLEMODEL_H

#include <QSqlRelationalTableModel>
#include <qqt-local.h>

/**
 * @brief The QQtTableModel class
 * QQTSqlRelationalTableModel 方便起见，仅仅使用这个model
 */
class QQTSHARED_EXPORT QQtTableModel :  public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit QQtTableModel ( QObject* parent = 0, QSqlDatabase db = QSqlDatabase() );

    void query ( QString filter = "" );

public:
    QVariant data ( const QModelIndex& item, int role = Qt::DisplayRole ) const;
    bool setData ( const QModelIndex& item, const QVariant& value, int role = Qt::EditRole );
    Qt::ItemFlags flags ( const QModelIndex& index ) const;
signals:

public slots:

private:
    QMap<QModelIndex, QString> idata;
    QMap<QModelIndex, Qt::ItemFlag> iflag;
    QMap<QModelIndex, Qt::AlignmentFlag> ialign;
    QMap<QModelIndex, Qt::CheckState> icheck;
};
#endif // QQTTABLEMODEL_H
