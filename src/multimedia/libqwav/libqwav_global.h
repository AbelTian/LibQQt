#ifndef LIBQWAV_GLOBAL_H
#define LIBQWAV_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef Q_OS_WIN
#if defined(LIBQWAV_LIBRARY)
#  define LIBQWAVSHARED_EXPORT Q_DECL_EXPORT
#elif defined(LIBQWAV_STATIC_LIBRARY)
#  define LIBQWAVSHARED_EXPORT
#else
#  define LIBQWAVSHARED_EXPORT Q_DECL_IMPORT
#endif
#else
#  define LIBQWAVSHARED_EXPORT
#endif

#endif // LIBQWAV_GLOBAL_H
