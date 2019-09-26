#ifndef QQTMAINGLFORM_H
#define QQTMAINGLFORM_H

#include <qqtopenglwindow.h>

namespace Ui {
class QQtMainGLForm;
}

class QQtMainGLForm : public QQtOpenGLWindow
{
    Q_OBJECT

public:
    explicit QQtMainGLForm ( QWidget* parent = 0 );
    ~QQtMainGLForm();

private:
    Ui::QQtMainGLForm* ui;
};

#endif // QQTMAINGLFORM_H
