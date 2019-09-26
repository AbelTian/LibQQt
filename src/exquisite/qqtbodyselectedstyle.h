#ifndef QQTBODYSELECTEDSTYLE_H
#define QQTBODYSELECTEDSTYLE_H

#include <QObject>

#include <qqt-local.h>

/**
 * @brief The QQtBodySelectedStyle class
 * 窗体选中效果
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
