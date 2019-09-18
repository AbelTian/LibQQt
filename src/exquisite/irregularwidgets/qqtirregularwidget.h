#ifndef QQTIRREGULARWIDGET_H
#define QQTIRREGULARWIDGET_H

#include <qqtwidget.h>
#include <qqt-local.h>

/**
 * @brief The QQtIrregularWidget class
 * 不规则控件
 * 不规则窗体，可以用这个，建议用QQtOSDFrame，那个比这个简单。
 *
 * 原理：
 * 设置一张带有alpha通道的图片即可。即能够点击的部分不透明，其他部分透明的矩形图片。
 * 内部将图片本身设置为背景，将它的mask设置为mask，实现不规则功能效果。
 *
 * 内部自动管理设置mask resizeEvent
 * 自动管理mask伴随图片的大小变化 resizeEvent
 */
class QQTSHARED_EXPORT QQtIrregularWidget : public QQtWidget
{
    Q_OBJECT
public:
    QQtIrregularWidget ( QWidget* parent = 0 );
    virtual ~QQtIrregularWidget();

    // QWidget interface
protected:
    virtual void resizeEvent ( QResizeEvent* event ) override;
};

#endif //QQTIRREGULARWIDGET_H
