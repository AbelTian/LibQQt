#ifndef QQTSVGWIDGET_H
#define QQTSVGWIDGET_H

#include <QSvgWidget>

class QQtSvgWidget : public QSvgWidget
{
    Q_OBJECT
public:
    explicit QQtSvgWidget(QWidget* parent = nullptr);

    void setSvgFile(QString& filename);
    void setSvgContent(QByteArray& bytes);
signals:

public slots:
};

#endif // QQTSVGWIDGET_H
