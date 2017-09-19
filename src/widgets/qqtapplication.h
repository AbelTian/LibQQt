#ifndef QQTAPPLICATION_H
#define QQTAPPLICATION_H

#include <QApplication>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtApplication : public QApplication
{
    Q_OBJECT
public:
public:
    explicit QQtApplication(int &argc, char **argv
#ifndef Q_QDOC
    , int = ApplicationFlags
#endif
        );

    void setLanguage(QString qmfile = "./lang/zh_CN.qm");
    //palette
    void setTextFont(QString fontfile = "/usr/lib/fonts/heiti.ttf", int fontsize = 11);
    void setQSSStyle(QString qssfile = "./skin/default.qss");
    void setUPanAutorun(bool run = false);

    virtual int initInstance() {}
    virtual int unInitInstance() {}

signals:

public slots:
    void slotUPanAutoRun(int status);
private:
    bool bUPanAutoRun;

private:
    QTranslator* language;
};

#endif // QQTAPPLICATION_H
