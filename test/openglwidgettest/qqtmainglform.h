#ifndef QQTMAINGLFORM_H
#define QQTMAINGLFORM_H

#include <qqtopenglwidget.h>

namespace Ui {
class QQtMainGLForm;
}

class QQtMainGLForm : public QQtOpenGLWidget
{
    Q_OBJECT

public:
    explicit QQtMainGLForm ( QWidget* parent = 0 );
    ~QQtMainGLForm();

private:
    Ui::QQtMainGLForm* ui;
};

#endif // QQTMAINGLFORM_H
