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

#include "GumboQueryNode.h"
#include "GumboQuerySelection.h"
#include "GumboQueryUtil.h"

GumboQueryNode::GumboQueryNode ( GumboNode* apNode )
{
    mpNode = apNode;
}

GumboQueryNode::~GumboQueryNode()
{
}

GumboQueryNode GumboQueryNode::parent()
{
    return GumboQueryNode ( mpNode->parent );
}

GumboQueryNode GumboQueryNode::nextSibling()
{
    return parent().childAt ( mpNode->index_within_parent + 1 );
}

GumboQueryNode GumboQueryNode::prevSibling()
{
    return parent().childAt ( mpNode->index_within_parent - 1 );
}

unsigned int GumboQueryNode::childNum()
{
    if ( mpNode->type != GUMBO_NODE_ELEMENT )
    {
        return 0;
    }

    return mpNode->v.element.children.length;

}

bool GumboQueryNode::valid()
{
    return mpNode != NULL;
}

GumboQueryNode GumboQueryNode::childAt ( size_t i )
{
    if ( mpNode->type != GUMBO_NODE_ELEMENT || i >= mpNode->v.element.children.length )
    {
        return GumboQueryNode();
    }

    return GumboQueryNode ( ( GumboNode* ) mpNode->v.element.children.data[i] );
}

std::string GumboQueryNode::attribute ( std::string key )
{
    if ( mpNode->type != GUMBO_NODE_ELEMENT )
    {
        return "";
    }

    GumboVector attributes = mpNode->v.element.attributes;

    for ( unsigned int i = 0; i < attributes.length; i++ )
    {
        GumboAttribute* attr = ( GumboAttribute* ) attributes.data[i];

        if ( key == attr->name )
        {
            return attr->value;
        }
    }

    return "";
}

std::string GumboQueryNode::text()
{
    return GumboQueryUtil::nodeText ( mpNode );
}

std::string GumboQueryNode::ownText()
{
    return GumboQueryUtil::nodeOwnText ( mpNode );
}

size_t GumboQueryNode::startPos()
{
    switch ( mpNode->type )
    {
    case GUMBO_NODE_ELEMENT:
        return mpNode->v.element.start_pos.offset + mpNode->v.element.original_tag.length;

    case GUMBO_NODE_TEXT:
        return mpNode->v.text.start_pos.offset;

    default:
        return 0;
    }
}

size_t GumboQueryNode::endPos()
{
    switch ( mpNode->type )
    {
    case GUMBO_NODE_ELEMENT:
        return mpNode->v.element.end_pos.offset;

    case GUMBO_NODE_TEXT:
        return mpNode->v.text.original_text.length + startPos();

    default:
        return 0;
    }
}

size_t GumboQueryNode::startPosOuter()
{
    switch ( mpNode->type )
    {
    case GUMBO_NODE_ELEMENT:
        return mpNode->v.element.start_pos.offset;

    case GUMBO_NODE_TEXT:
        return mpNode->v.text.start_pos.offset;

    default:
        return 0;
    }
}

size_t GumboQueryNode::endPosOuter()
{
    switch ( mpNode->type )
    {
    case GUMBO_NODE_ELEMENT:
        return mpNode->v.element.end_pos.offset + mpNode->v.element.original_end_tag.length;

    case GUMBO_NODE_TEXT:
        return mpNode->v.text.original_text.length + startPos();

    default:
        return 0;
    }
}

std::string GumboQueryNode::tag()
{
    if ( mpNode->type != GUMBO_NODE_ELEMENT )
    {
        return "";
    }

    return gumbo_normalized_tagname ( mpNode->v.element.tag );
}

GumboQuerySelection GumboQueryNode::find ( std::string aSelector )
{
    GumboQuerySelection c ( mpNode );
    return c.find ( aSelector );
}
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
