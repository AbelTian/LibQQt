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

#ifndef SELECTION_H_
#define SELECTION_H_

#include "GumboQueryObject.h"
#include <vector>
#include <string>
#include <gumbo.h>

class GumboQueryNode;

class GumboQuerySelection: public GumboQueryObject
{

public:

    GumboQuerySelection ( GumboNode* apNode );

    GumboQuerySelection ( std::vector<GumboNode*> aNodes );

    virtual ~GumboQuerySelection();

public:

    GumboQuerySelection find ( std::string aSelector );

    GumboQueryNode nodeAt ( size_t i );

    size_t nodeNum();

private:

    std::vector<GumboNode*> mNodes;
};

#endif /* SELECTION_H_ */

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
