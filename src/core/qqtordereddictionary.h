#ifndef QQTORDEREDDICTIONARY_H
#define QQTORDEREDDICTIONARY_H

#include <QObject>
#include <qqt-local.h>
/**
 * @brief The QQtOrderedDictionary class
 * 使用不排序的map的字典类。
 *
 * 未实现
 */
class QQTSHARED_EXPORT QQtOrderedDictionary : public QObject
{
    Q_OBJECT

public:
    explicit QQtOrderedDictionary ( QObject* parent = 0 )
        : QObject ( parent ) {}
    virtual ~QQtOrderedDictionary() {}

protected:

private:

};

#endif // QQTORDEREDDICTIONARY_H

