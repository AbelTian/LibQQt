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

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <gumbo.h>
#include <string>
#include "GumboQuerySelection.h"
#include "GumboQueryLocal.h"

class QT_GUMBO_EXPORT GumboQueryDocument: public GumboQueryObject
{
public:

    GumboQueryDocument();

    void parse ( const std::string& aInput );

    virtual ~GumboQueryDocument();

    GumboQuerySelection find ( std::string aSelector );

private:

    void reset();

protected:

    GumboOutput* mpOutput;
};

#endif /* DOCUMENT_H_ */

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
