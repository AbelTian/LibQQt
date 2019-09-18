#ifndef QQTIRREGULARLABEL_H
#define QQTIRREGULARLABEL_H

#include <qqtlabel.h>
#include <qqt-local.h>

/**
 * @brief The QQtIrregularLabel class
 *
 * setScaledContents
 */
class QQTSHARED_EXPORT QQtIrregularLabel : public QQtLabel
{
    Q_OBJECT
public:
    QQtIrregularLabel ( QWidget* parent = 0 );
    virtual ~QQtIrregularLabel();
};

#endif //QQTIRREGULARLABEL_H
