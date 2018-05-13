#ifndef QQTLISTVIEW_H
#define QQTLISTVIEW_H

#include <QListView>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtListView : public QListView
{
    Q_OBJECT

public:
    explicit QQtListView ( QWidget* parent = 0 );
    virtual ~QQtListView ();

private:
};

#endif // QQTLISTVIEW_H
