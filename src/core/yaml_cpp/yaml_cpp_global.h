#ifndef YAML_CPP_GLOBAL_H
#define YAML_CPP_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef Q_OS_WIN
#if defined(YAML_CPP_LIBRARY)
#  define YAML_CPPSHARED_EXPORT Q_DECL_EXPORT
#elif defined(YAML_CPP_STATIC_LIBRARY)
#  define YAML_CPPSHARED_EXPORT
#else
#  define YAML_CPPSHARED_EXPORT Q_DECL_IMPORT
#endif
#else
#  define YAML_CPPSHARED_EXPORT
#endif

#endif // YAML_CPP_GLOBAL_H
