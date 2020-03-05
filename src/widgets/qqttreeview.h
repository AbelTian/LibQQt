#ifndef QQTTREEVIEW_H
#define QQTTREEVIEW_H

#include <QTreeView>
#include <qqt-local.h>

/**
 * @brief The QQtTreeView class
 */
class QQTSHARED_EXPORT QQtTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit QQtTreeView ( QWidget* parent = 0 );
    virtual ~QQtTreeView();

private:
};

#endif // QQTTREEVIEW_H
