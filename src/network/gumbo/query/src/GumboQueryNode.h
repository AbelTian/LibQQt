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

#ifndef NODE_H_
#define NODE_H_

#include <gumbo.h>
#include <string>
#include "GumboQueryLocal.h"

class GumboQuerySelection;

class QT_GUMBO_EXPORT GumboQueryNode
{
public:

    GumboQueryNode ( GumboNode* apNode = NULL );

    virtual ~GumboQueryNode();

public:

    bool valid();

    GumboQueryNode parent();

    GumboQueryNode nextSibling();

    GumboQueryNode prevSibling();

    unsigned int childNum();

    GumboQueryNode childAt ( size_t i );

    std::string attribute ( std::string key );

    std::string text();

    std::string ownText();

    size_t startPos();

    size_t endPos();

    size_t startPosOuter();

    size_t endPosOuter();

    std::string tag();

    GumboQuerySelection find ( std::string aSelector );

private:

    GumboNode* mpNode;
};

#endif /* NODE_H_ */

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
