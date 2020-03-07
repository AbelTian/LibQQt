#ifndef QQTINIPARSER_H
#define QQTINIPARSER_H

#include "qqtdictionary.h"

#include <qqt-local.h>

QQTSHARED_EXPORT QByteArray toIni ( const QQtDictionary& dict );
QQTSHARED_EXPORT void fromIni ( const QByteArray& bytes, QQtDictionary& dict );


#endif // QQTINIPARSER_H
