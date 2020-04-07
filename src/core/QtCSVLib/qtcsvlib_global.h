#ifndef QTCSVLIB_GLOBAL_H
#define QTCSVLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef Q_OS_WIN
#if defined(QTCSVLIB_LIBRARY)
#  define QTCSVLIBSHARED_EXPORT Q_DECL_EXPORT
#elif defined(QTCSVLIB_STATIC_LIBRARY)
#  define QTCSVLIBSHARED_EXPORT
#else
#  define QTCSVLIBSHARED_EXPORT Q_DECL_IMPORT
#endif
#else
#  define QTCSVLIBSHARED_EXPORT
#endif

#endif // QTCSVLIB_GLOBAL_H
