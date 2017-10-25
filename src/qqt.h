#ifndef QQT_H
#define QQT_H


#include <QtCore/qglobal.h>

#include "qqt-local.h"
#include "qqt-qt.h"

#if defined(__WIN__) || defined(__WIN64__)
#include "qqtwin.h"
#elif defined(__LINUX__) || defined(__LINUX64__)
#include "qqtlinux.h"
#elif defined (__ANDROID__) || defined (__ANDROIDX86__)
#include "qqtandroid.h"
#elif defined (__DARWIN__)  || defined(__IOS__)
#include "qqtdarwin.h"
#endif
#include "qqtcore.h"
#include "qqtgui.h"
#include "qqtsql.h"
#include "qqtnetwork.h"
#include "qqtwidgets.h"
#include "qqtframe.h"

#endif // QQT_H
