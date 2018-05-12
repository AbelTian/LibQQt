#ifndef QZXING_GLOBAL_H
#define QZXING_GLOBAL_H

#include <QtCore>
#include <qglobal.h>

#if defined(QZXING_LIBRARY)
#  define QZXINGSHARED_EXPORT Q_DECL_EXPORT
#elif defined(QZXING_STATIC_LIBRARY)
#  define QZXINGSHARED_EXPORT
#else
#  define QZXINGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif  //QZXING_GLOBAL_H
