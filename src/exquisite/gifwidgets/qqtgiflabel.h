#ifndef QQTGIFLABEL_H
#define QQTGIFLABEL_H

#include <qqtlabel.h>
#include <qqt-local.h>
#include <qqtcore.h>
#include <QMovie>

class QQTSHARED_EXPORT QQtGifLabel : public QQtLabel
{
    Q_OBJECT
public:
    explicit QQtGifLabel ( QWidget* parent = nullptr );
    virtual ~QQtGifLabel() {}

    void setGifFile ( QString gifFile );

signals:

public slots:
private:
    QMovie* m_movie;
};

#endif // QQTGIFLABEL_H
