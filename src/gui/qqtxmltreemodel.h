#ifndef QQTXMLTREEMODEL_H
#define QQTXMLTREEMODEL_H

#include <qqttreemodel.h>
#include <QDomDocument>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQTXmlTreeModel : public QQTTreeModel
{
    Q_OBJECT
public:
    explicit QQTXmlTreeModel(QObject *parent = 0);


signals:

public slots:

    // QQTTreeModel interface
public:
    bool query(QString condition) Q_DECL_OVERRIDE;
    void setFilePath(QString xmlfile) Q_DECL_OVERRIDE;

protected:
       /**
     * @brief parseChildElement
     * @param element
     */
    void parseChildElement(const QDomElement &element, QStandardItem* itemParent = 0);

private:
    QDomDocument doc;
};

#endif // QQTXMLTREEMODEL_H
