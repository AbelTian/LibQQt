#ifndef QQTLOCAL_H
#define QQTLOCAL_H


#include <QtCore/qglobal.h>

#if defined(QQT_LIBRARY)
#  define QQTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QQTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QQTLOCAL_H
