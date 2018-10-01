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

#include "GumboQueryUtil.h"

std::string GumboQueryUtil::tolower ( std::string s )
{
    for ( unsigned int i = 0; i < s.size(); i++ )
    {
        char c = s[i];

        if ( c >= 'A' && c <= 'Z' )
        {
            c = 'a' + c - 'A';
            s[i] = c;
        }
    }

    return s;
}

std::vector<GumboNode*> GumboQueryUtil::unionNodes ( std::vector<GumboNode*> aNodes1,
                                                     std::vector<GumboNode*> aNodes2 )
{
    for ( std::vector<GumboNode*>::iterator it = aNodes2.begin(); it != aNodes2.end(); it++ )
    {
        GumboNode* pNode = *it;

        if ( nodeExists ( aNodes1, pNode ) )
        {
            continue;
        }

        aNodes1.push_back ( pNode );
    }

    return aNodes1;
}

bool GumboQueryUtil::nodeExists ( std::vector<GumboNode*> aNodes, GumboNode* apNode )
{
    for ( std::vector<GumboNode*>::iterator it = aNodes.begin(); it != aNodes.end(); it++ )
    {
        GumboNode* pNode = *it;

        if ( pNode == apNode )
        {
            return true;
        }
    }

    return false;
}

std::string GumboQueryUtil::nodeText ( GumboNode* apNode )
{
    std::string text;
    writeNodeText ( apNode, text );
    return text;
}

std::vector<std::string> GumboQueryUtil::nodeTextList ( GumboNode* apNode )
{
    std::vector<std::string> textList;
    writeNodeTextList ( apNode, textList );
    return textList;
}

std::string GumboQueryUtil::nodeOwnText ( GumboNode* apNode )
{
    std::string text;

    if ( apNode->type != GUMBO_NODE_ELEMENT )
    {
        return text;
    }

    GumboVector children = apNode->v.element.children;

    for ( unsigned int i = 0; i < children.length; i++ )
    {
        GumboNode* child = ( GumboNode* ) children.data[i];

        if ( child->type == GUMBO_NODE_TEXT )
        {
            text.append ( child->v.text.text );
        }
    }

    return text;
}

void GumboQueryUtil::writeNodeText ( GumboNode* apNode, std::string& aText )
{
    switch ( apNode->type )
    {
        case GUMBO_NODE_TEXT:
            aText.append ( apNode->v.text.text );
            break;

        case GUMBO_NODE_ELEMENT:
        {
            GumboVector children = apNode->v.element.children;

            for ( unsigned int i = 0; i < children.length; i++ )
            {
                GumboNode* child = ( GumboNode* ) children.data[i];
                writeNodeText ( child, aText );
            }

            break;
        }

        default:
            break;
    }
}

void GumboQueryUtil::writeNodeTextList ( GumboNode* apNode, std::vector<std::string>& aTextList )
{
    switch ( apNode->type )
    {
        case GUMBO_NODE_TEXT:
            aTextList.push_back ( apNode->v.text.text );
            break;

        case GUMBO_NODE_ELEMENT:
        {
            GumboVector children = apNode->v.element.children;

            for ( unsigned int i = 0; i < children.length; i++ )
            {
                GumboNode* child = ( GumboNode* ) children.data[i];
                writeNodeTextList ( child, aTextList );
            }

            break;
        }

        default:
            break;
    }
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
