#ifndef QQTIRREGULARLABEL_H
#define QQTIRREGULARLABEL_H

#include <qqtlabel.h>
#include <qqt-local.h>

/**
 * @brief The QQtIrregularLabel class
 * 不规则label
 *
 */
class QQTSHARED_EXPORT QQtIrregularLabel : public QQtLabel
{
    Q_OBJECT
public:
    QQtIrregularLabel ( QWidget* parent = 0 );
    virtual ~QQtIrregularLabel();

    void setAlignment ( Qt::Alignment );

protected:
    virtual void makeMaskWidget ( void );

    // QWidget interface
protected:
    virtual void resizeEvent ( QResizeEvent* event ) override;
};

#endif //QQTIRREGULARLABEL_H
