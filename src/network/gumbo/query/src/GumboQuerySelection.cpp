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

#include "GumboQuerySelection.h"
#include "GumboQueryParser.h"
#include "GumboQueryUtil.h"
#include "GumboQueryNode.h"

GumboQuerySelection::GumboQuerySelection ( GumboNode* apNode )
{
    mNodes.push_back ( apNode );
}

GumboQuerySelection::GumboQuerySelection ( std::vector<GumboNode*> aNodes )
{
    mNodes = aNodes;
}

GumboQuerySelection::~GumboQuerySelection()
{
}

GumboQuerySelection GumboQuerySelection::find ( std::string aSelector )
{
    GumboQuerySelector* sel = GumboQueryParser::create ( aSelector );
    std::vector<GumboNode*> ret;

    for ( std::vector<GumboNode*>::iterator it = mNodes.begin(); it != mNodes.end(); it++ )
    {
        GumboNode* pNode = *it;
        std::vector<GumboNode*> matched = sel->matchAll ( pNode );
        ret = GumboQueryUtil::unionNodes ( ret, matched );
    }

    sel->release();
    return GumboQuerySelection ( ret );
}

GumboQueryNode GumboQuerySelection::nodeAt ( size_t i )
{
    if ( i >= mNodes.size() )
    {
        return GumboQueryNode();
    }

    return GumboQueryNode ( mNodes[i] );
}

size_t GumboQuerySelection::nodeNum()
{
    return mNodes.size();
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */

