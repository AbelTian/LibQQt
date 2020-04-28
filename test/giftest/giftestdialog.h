#ifndef GIFTESTDIALOG_H
#define GIFTESTDIALOG_H

#include <QDialog>

namespace Ui {
class GifTestDialog;
}

class GifTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GifTestDialog ( QWidget* parent = 0 );
    ~GifTestDialog();

protected slots:
    virtual void updateProgress();

private:
    Ui::GifTestDialog* ui;
};

#endif // GIFTESTDIALOG_H
