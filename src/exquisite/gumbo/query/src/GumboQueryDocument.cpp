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

#include "GumboQueryDocument.h"

GumboQueryDocument::GumboQueryDocument()
{
    mpOutput = NULL;
}

void GumboQueryDocument::parse ( const std::string& aInput )
{
    reset();
    mpOutput = gumbo_parse ( aInput.c_str() );
}

GumboQueryDocument::~GumboQueryDocument()
{
    reset();
}

GumboQuerySelection GumboQueryDocument::find ( std::string aSelector )
{
    if ( mpOutput == NULL )
    {
        throw "document not initialized";
    }

    GumboQuerySelection sel ( mpOutput->root );
    return sel.find ( aSelector );
}

void GumboQueryDocument::reset()
{
    if ( mpOutput != NULL )
    {
        gumbo_destroy_output ( &kGumboDefaultOptions, mpOutput );
        mpOutput = NULL;
    }
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */

