#ifndef QQTSVGLABEL_H
#define QQTSVGLABEL_H

#include <qqtlabel.h>
#include <QSvgRenderer>
#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtSvgLabel : public QQtLabel
{
    Q_OBJECT
public:
    explicit QQtSvgLabel ( QWidget* parent = nullptr );

    void setSvgFile ( QString& filename );
    void setSvgContent ( QByteArray& bytes );

signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;

private:
    QSvgRenderer mSvgRender;
};

#endif // QQTSVGLABEL_H
