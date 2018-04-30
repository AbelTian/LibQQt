#include "qqtobjectmanager.h"

bool operator< ( QByteArray& l, QByteArray& r )
{
    int cc = qstrcmp ( l, r );
    if ( cc == 0 || cc > 0 )
        return false;
    return true;
}

bool operator== ( QByteArray& l, QByteArray& r )
{
    int cc = qstrcmp ( l, r );
    if ( cc == 0 )
        return true;
    return false;
}
