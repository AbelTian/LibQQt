#ifndef QQTLOCAL_H
#define QQTLOCAL_H


#include <QtCore/qglobal.h>

//only this logic is correct !

#if defined(Q_OS_WIN)
//dynamic and static are different
//build dynamic library
#if   defined(QQT_LIBRARY)
#     define QQTSHARED_EXPORT Q_DECL_EXPORT
//build static library
//you must use this macro to link static library, otherwise linker will think you have use dynamic library
#elif defined(QQT_STATIC_LIBRARY)
#     define QQTSHARED_EXPORT
//link  dynamic library
#else
#     define QQTSHARED_EXPORT Q_DECL_IMPORT
#endif
#else
//dynamic and static are equal to each other
#     define QQTSHARED_EXPORT
#endif


#endif // QQTLOCAL_H
