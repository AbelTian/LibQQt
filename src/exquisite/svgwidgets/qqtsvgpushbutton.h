#ifndef QQTSVGPUSHBUTTON_H
#define QQTSVGPUSHBUTTON_H

#include <qqtpushbutton.h>
#include <QSvgRenderer>
#include <qqtwidgets.h>
#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtSvgPushButton : public QQtPushButton
{
    Q_OBJECT
public:
    explicit QQtSvgPushButton ( QWidget* parent = nullptr );
    virtual ~QQtSvgPushButton() {}

    QString stateImage ( int index );
    void setStateImage ( int index, const QString& image );

    //normal, press; uncheck, check; [0,1];
    void setNormalImage ( const QString& normal, const QString& press );
    //hover; [2];
    void setHoverImage ( const QString& hover );
    //disable; [4];
    void setDisableImage ( const QString& disable );

    //svg控件使用iconTable，必须render。
    const TBtnIconTable& iconTable() const;
    TBtnIconTable& iconTable();
    /**
     * @brief renderToVariable
     * call this function after iconTable() set.
     */
    void renderToVariable();
protected:
    virtual void translateImage();


signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;

private:
    QSvgRenderer r[BTN_MAX];

    TBtnIconTable mIconTable;
};

#endif // QQTSVGPUSHBUTTON_H
