#ifndef QQTPUB_H
#define QQTPUB_H


#include <QtCore/qglobal.h>
#include "qqt-local.h"


#include "qqt-qt.h"
#include "qqtgui.h"
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
