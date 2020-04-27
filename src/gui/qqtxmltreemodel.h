#ifndef QQTXMLTREEMODEL_H
#define QQTXMLTREEMODEL_H

#include <qqttreemodel.h>
#include <QDomDocument>
#include <qqt-local.h>

/**
 * @brief The QQtXmlTreeModel class
 * 将XML格式的内容解析到Tree里。
 * 废弃，使用QQtDictTreeModel代替。
 */
class QQTSHARED_EXPORT QQtXmlTreeModel : public QQtTreeModel
{
    Q_OBJECT
public:
    explicit QQtXmlTreeModel ( QObject* parent = 0 );


signals:

public slots:

    // QQtTreeModel interface
public:
    bool query ( QString condition ) override;
    void setFilePath ( QString xmlfile ) override;

protected:
    /**
    * @brief parseChildElement
    * @param element
    */
    void parseChildElement ( const QDomElement& element, QStandardItem* itemParent = 0 );

private:
    QDomDocument doc;
};

#endif // QQTXMLTREEMODEL_H
