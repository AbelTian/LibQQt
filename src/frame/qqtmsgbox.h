#ifndef QQTMSGBOX_H
#define QQTMSGBOX_H

#include "qqtdialog.h"

namespace Ui {
class QQTMsgBox;
}

/**
 * @brief The QQTMsgBox class
 *
 */
class QQTMsgBox : public QQTDialog
{
    Q_OBJECT

public:
    explicit QQTMsgBox(QWidget *parent = 0);
    ~QQTMsgBox();

    void warning(QString content);
    void question(QString content);
    void information(QString content);

    /*
     * 警告，不可选择
     */
    static int warning(QWidget* parent = 0, QString content = "");
    /*
     * 提醒，供用户选择
     */
    static int question(QWidget* parent = 0, QString content = "");

protected:
    int _warning(QString content);
    int _question(QString content);

private:
    Ui::QQTMsgBox *ui;
    quint32 m_time;
    int delayShow;

    void showYes();
    void showYesAndNo();
    void showNull();

    int widgetW;
    int widgetH;
    int btnW;
    int btnH;
    int botoomH;
    int xSpaceYes;
    int xSpaceYesNo;
    int ySpace;


    // QObject interface
protected:
    void timerEvent(QTimerEvent *);
};

#endif // QQTMSGBOX_H
