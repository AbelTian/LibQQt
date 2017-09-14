#ifndef QQTPUB_H
#define QQTPUB_H

#include "qqtgui.h"
#include "qqtgui-qt.h"
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


#endif // QQTPUB_H
