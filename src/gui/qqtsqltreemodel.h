#ifndef QQTSQLTREEMODEL_H
#define QQTSQLTREEMODEL_H

#include <qqttreemodel.h>
#include <qqttablemodel.h>
#include <QList>
#include <qqt-local.h>

/**
 * @brief The QQtSqlTreeModel class
 * 按照树的样式来显示数据库
 */
class QQTSHARED_EXPORT QQtSqlTreeModel : public QQtTreeModel
{
    Q_OBJECT
public:
    explicit QQtSqlTreeModel ( QObject* parent = 0 );

    QSqlDatabase& database() { return m_db; }
    void setAbsoluteFilePath ( QString dbname );

    // QQtSqlTreeModel interface
public:
    virtual bool query ( QString condition = "" ) override;
    virtual void setFilePath ( QString dbname ) override;
protected:
    virtual bool parseDatabase();
    virtual bool parseTable ( QString tableName );
private:
    QSqlDatabase m_db;
    QList<QQtTableModel*> tableModelList;
};

#endif // QQTSQLTREEMODEL_H
