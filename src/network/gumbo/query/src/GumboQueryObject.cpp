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

#include "GumboQueryObject.h"

GumboQueryObject::GumboQueryObject()
{
    mReferences = 1;
}

GumboQueryObject::~GumboQueryObject()
{
    if ( mReferences != 1 )
    {
        throw "something wrong, reference count not zero";
    }
}

void GumboQueryObject::retain()
{
    mReferences++;
}

void GumboQueryObject::release()
{
    if ( mReferences < 0 )
    {
        throw "something wrong, reference count is negative";
    }

    if ( mReferences == 1 )
    {
        delete this;
    }
    else
    {
        mReferences--;
    }
}

unsigned int GumboQueryObject::references()
{
    return mReferences;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */

