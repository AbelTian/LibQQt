#ifndef QQTPUB_H
#define QQTPUB_H


#include <QtCore/qglobal.h>

#if defined(QQT_LIBRARY)
#  define QQTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QQTSHARED_EXPORT Q_DECL_IMPORT
#endif

#include "qqtgui.h"
#include "qqt-qt.h"
#if defined(__WIN__) || defined(__WIN64__)
#include "qqtwin.h"
#elif defined(__LINUX__) || defined(__LINUX64__)
#include "qqtlinux.h"
#else
#include "qqtdarwin.h"
#endif
#include "qqtcore.h"
#include "qqtsql.h"
#include "qqtnetwork.h"
#include "qqtwidgets.h"
#include "qqtframe.h"

#endif // QQTPUB_H
