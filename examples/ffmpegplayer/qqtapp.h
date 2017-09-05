#ifndef QQTAPP_H
#define QQTAPP_H

#include <QApplication>

class QQTApp : public QApplication
{
    Q_OBJECT
public:
    explicit QQTApp(int &argc, char **argv);
    virtual ~QQTApp();

    void setTheme();

    void setLanguage();

signals:

public slots:
    void slotUPanAutoRun(int status);

private:
    QTranslator* language;
};

#endif // QQTAPP_H
