#ifndef QQTJSONTREEMODEL_H
#define QQTJSONTREEMODEL_H

#include <qqttreemodel.h>
#include <QDomDocument>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtJsonTreeModel : public QQtTreeModel
{
    Q_OBJECT
public:
    explicit QQtJsonTreeModel ( QObject* parent = 0 );


signals:

public slots:

    // QQtJsonTreeModel interface
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

#endif // QQTJSONTREEMODEL_H
