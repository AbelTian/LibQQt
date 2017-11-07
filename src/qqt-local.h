#ifndef QQTLOCAL_H
#define QQTLOCAL_H


#include <QtCore/qglobal.h>

#if defined(Q_OS_WIN)
//dynamic and static are different
#if   defined(QQT_LIBRARY)
#     define QQTSHARED_EXPORT Q_DECL_EXPORT
#elif defined(QQT_STATIC_LIBRARY)
#     define QQTSHARED_EXPORT
#else
#     define QQTSHARED_EXPORT Q_DECL_IMPORT
#endif
#else
//dynamic and static are equal to each other
#     define QQTSHARED_EXPORT
#endif


#endif // QQTLOCAL_H
