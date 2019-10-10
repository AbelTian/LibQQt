#ifndef QQTBODYSELECTEDSTYLE_H
#define QQTBODYSELECTEDSTYLE_H

#include <QObject>

#include <qqt-local.h>

/**
 * @brief The QQtBodySelectedStyle class
 * 窗体选中效果。
 *
 * 存在的问题：
 * 选中效果的绘制无论如何都会绘制在QQtWidget里面图片的下方
 *
 * 在QQtExquisite里面提供了QQtMultiEventFilterWidget，可以把效果画在图的上边，建议使用。
 * 针对某些特别需求，在QQtExquisite里面提供了QQtMultiPageWidget和配套的QQtSelectedStyle类，针对QQtMultiPageWidget设置选中效果。要求较多，需要重写很多的效果器。
 */
class QQTSHARED_EXPORT QQtBodySelectedStyle : public QObject
{
    Q_OBJECT

public:
    enum SelectedStyle
    {
        //default
        SelectedStyle_QtDesigner,
        SelectedStyle_QRCodeScaner,
        SelectedStyle_DottedLine,
        SelectedStyle_FourCheck,

        SelectedStyle_Max
    } ;

public:
    QQtBodySelectedStyle ( QObject* parent = 0 );
    virtual ~QQtBodySelectedStyle();

    void setSelectedStyle ( SelectedStyle style );
    SelectedStyle selectedStyle();

    void setSelected ( bool bSelected );
    bool selectedStatus();

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;

private:
    bool hasSelected;
    SelectedStyle hasStyle;
};

#endif
