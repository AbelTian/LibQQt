/***************************************************************************
 *
 * $Id$
 *
 **************************************************************************/

/**
 * @file $HeadURL$
 * @author $Author$(hoping@baimashi.com)
 * @date $Date$
 * @version $Revision$
 * @brief
 *
 **/

#ifndef QUERYLOCAL_H_
#define QUERYLOCAL_H_

#include <QtCore/qglobal.h>

#if defined(Q_OS_WIN)
//dynamic and static are different
#if   defined(QT_GUMBO_LIBRARY)
#     define QT_GUMBO_EXPORT Q_DECL_EXPORT
#elif defined(QT_GUMBO_STATIC_LIBRARY)
#     define QT_GUMBO_EXPORT
#else
#     define QT_GUMBO_EXPORT Q_DECL_IMPORT
#endif
#else
//dynamic and static are equal to each other
#     define QT_GUMBO_EXPORT
#endif


#endif /* QUERYLOCAL_H_ */
