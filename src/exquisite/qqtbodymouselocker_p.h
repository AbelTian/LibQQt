#ifndef QQTBODYMOUSELOCKER_P_H
#define QQTBODYMOUSELOCKER_P_H

#if defined (__DESKTOP_WIN__)
#include <qqtbodymouselocker_win.h>
#elif defined (__DESKTOP_LINUX__)
#include <qqtbodymouselocker_x11.h>
#else
#include <qqtbodymouselocker_unix.h>
#endif

#endif //QQTBODYMOUSELOCKER_P_H
