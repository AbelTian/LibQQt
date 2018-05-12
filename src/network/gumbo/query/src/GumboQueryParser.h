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

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <gumbo.h>
#include "GumboQuerySelector.h"
#include "GumboQueryLocal.h"

class QT_GUMBO_EXPORT GumboQueryParser
{
private:

    GumboQueryParser ( std::string aInput );

public:

    virtual ~GumboQueryParser();

public:

    static GumboQuerySelector* create ( std::string aInput );

private:

    GumboQuerySelector* parseSelectorGroup();

    GumboQuerySelector* parseSelector();

    GumboQuerySelector* parseSimpleSelectorSequence();

    void parseNth ( int& aA, int& aB );

    int parseInteger();

    GumboQuerySelector* parsePseudoclassSelector();

    GumboQuerySelector* parseAttributeSelector();

    GumboQuerySelector* parseClassSelector();

    GumboQuerySelector* parseIDSelector();

    GumboQuerySelector* parseTypeSelector();

    bool consumeClosingParenthesis();

    bool consumeParenthesis();

    bool skipWhitespace();

    std::string parseString();

    std::string parseName();

    std::string parseIdentifier();

    bool nameChar ( char c );

    bool nameStart ( char c );

    bool hexDigit ( char c );

    std::string parseEscape();

    std::string error ( std::string message );

private:

    std::string mInput;

    size_t mOffset;
};

#endif /* PARSER_H_ */

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
