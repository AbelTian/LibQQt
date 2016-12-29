#ifndef QQTLISTVIEW_H
#define QQTLISTVIEW_H

#include <QListView>

namespace Ui {
class QQTListView;
}

class QQTListView : public QListView
{
    Q_OBJECT

public:
    explicit QQTListView(QWidget *parent = 0);
    ~QQTListView();

private:
    Ui::QQTListView *ui;
};

#endif // QQTLISTVIEW_H
