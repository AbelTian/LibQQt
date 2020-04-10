#ifndef JSON_MOD_WRITER_H
#define JSON_MOD_WRITER_H

#include <json/config.h>
#include <json/writer.h>

namespace Json {

class JSON_API BaseWriter : public Writer
{
public:
    BaseWriter() {}
    virtual ~BaseWriter() {}

protected:
    static bool isControlCharacter ( char ch ) {
        return ch > 0 && ch <= 0x1F;
    }

    static bool containsControlCharacter ( const char* str ) {
        while ( *str ) {
            if ( isControlCharacter ( * ( str++ ) ) )
                return true;
        }
        return false;
    }

    static void uintToString ( unsigned int value,
                               char*& current ) {
        *--current = 0;
        do {
            *--current = ( value % 10 ) + '0';
            value /= 10;
        } while ( value != 0 );
    }

    std::string valueToString ( Int value ) {
        char buffer[32];
        char* current = buffer + sizeof ( buffer );
        bool isNegative = value < 0;
        if ( isNegative )
            value = -value;
        uintToString ( UInt ( value ), current );
        if ( isNegative )
            *--current = '-';
        //assert(current >= buffer);
        return current;
    }


    std::string valueToString ( UInt value ) {
        char buffer[32];
        char* current = buffer + sizeof ( buffer );
        uintToString ( value, current );
        //assert(current >= buffer);
        return current;
    }

    std::string valueToString ( double value ) {
        char buffer[32];
#if defined(_MSC_VER) && defined(__STDC_SECURE_LIB__) // Use secure version with visual studio 2005 to avoid warning.
        sprintf_s ( buffer, sizeof ( buffer ), "%#.16g", value );
#else
        sprintf ( buffer, "%#.16g", value );
#endif
        char* ch = buffer + strlen ( buffer ) - 1;
        if ( *ch != '0' )
            return buffer; // nothing to truncate, so save time
        while ( ch > buffer && *ch == '0' ) {
            --ch;
        }
        char* last_nonzero = ch;
        while ( ch >= buffer ) {
            switch ( *ch ) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    --ch;
                    continue;
                case '.':
                    // Truncate zeroes to save bytes in output, but keep one.
                    * ( last_nonzero + 2 ) = '\0';
                    return buffer;
                default:
                    return buffer;
            }
        }
        return buffer;
    }


    std::string valueToString ( bool value ) {
        return value ? "true" : "false";
    }

    std::string valueToQuotedString ( const char* value ) {
        // Not sure how to handle unicode...
        if ( strpbrk ( value, "\"\\\b\f\n\r\t" ) == NULL && !containsControlCharacter ( value ) )
            return std::string ( "\"" ) + value + "\"";
        // We have to walk value and escape any special characters.
        // Appending to std::string is not efficient, but this should be rare.
        // (Note: forward slashes are *not* rare, but I am not escaping them.)
        unsigned maxsize = strlen ( value ) * 2 + 3; // allescaped+quotes+NULL
        std::string result;
        result.reserve ( maxsize ); // to avoid lots of mallocs
        result += "\"";
        for ( const char* c = value; *c != 0; ++c ) {
            switch ( *c ) {
                case '\"':
                    result += "\\\"";
                    break;
                case '\\':
                    result += "\\\\";
                    break;
                case '\b':
                    result += "\\b";
                    break;
                case '\f':
                    result += "\\f";
                    break;
                case '\n':
                    result += "\\n";
                    break;
                case '\r':
                    result += "\\r";
                    break;
                case '\t':
                    result += "\\t";
                    break;
                //case '/':
                // Even though \/ is considered a legal escape in JSON, a bare
                // slash is also legal, so I see no reason to escape it.
                // (I hope I am not misunderstanding something.
                // blep notes: actually escaping \/ may be useful in javascript to avoid </
                // sequence.
                // Should add a flag to allow this compatibility mode and prevent this
                // sequence from occurring.
                default:
                    result += *c;
                    break;
            }
        }
        result += "\"";
        return result;
    }
};

class JSON_API StringWriter : public BaseWriter
{
public:
    StringWriter() {}
    virtual ~StringWriter() {}

public: // overridden from Writer
    /** \brief Serialize a Value in <a HREF="http://www.json.org">JSON</a> format.
    * \param root Value to serialize.
    * \return String containing the JSON document that represents the root value.
    */
    virtual std::string write ( const Value& root ) {
        document_ = "";
        addChildValues_ = false;
        indentString_ = "";
        writeCommentBeforeValue ( root );
        writeValue ( root );
        writeCommentAfterValueOnSameLine ( root );
        document_ += "\n";
        return document_;
    }

private:
    void writeValue ( const Value& value ) {
        switch ( value.type() ) {
            case nullValue:
                pushValue ( "null" );
                break;
            case intValue:
                pushValue ( valueToString ( value.asInt() ) );
                break;
            case uintValue:
                pushValue ( valueToString ( value.asUInt() ) );
                break;
            case realValue:
                pushValue ( valueToString ( value.asDouble() ) );
                break;
            case stringValue:
                pushValue ( valueToQuotedString ( value.asCString() ) );
                break;
            case booleanValue:
                pushValue ( valueToString ( value.asBool() ) );
                break;
            case arrayValue:
                writeArrayValue ( value );
                break;
            case objectValue: {
                Value::Members members ( value.getMemberNames() );
                if ( members.empty() )
                    pushValue ( "{}" );
                else {
                    writeWithIndent ( "{" );
                    indent();
                    Value::Members::iterator it = members.begin();
                    while ( true ) {
                        const std::string& name = *it;
                        const Value& childValue = value[name];
                        writeCommentBeforeValue ( childValue );
                        writeWithIndent ( valueToQuotedString ( name.c_str() ) );
                        document_ += " : ";
                        writeValue ( childValue );
                        if ( ++it == members.end() ) {
                            writeCommentAfterValueOnSameLine ( childValue );
                            break;
                        }
                        document_ += ",";
                        writeCommentAfterValueOnSameLine ( childValue );
                    }
                    unindent();
                    writeWithIndent ( "}" );
                }
            }
            break;
        }
    }
    void writeArrayValue ( const Value& value ) {
        unsigned size = value.size();
        if ( size == 0 )
            pushValue ( "[]" );
        else {
            bool isArrayMultiLine = isMultineArray ( value );
            if ( isArrayMultiLine ) {
                writeWithIndent ( "[" );
                indent();
                bool hasChildValue = !childValues_.empty();
                unsigned index = 0;
                while ( true ) {
                    const Value& childValue = value[index];
                    writeCommentBeforeValue ( childValue );
                    if ( hasChildValue )
                        writeWithIndent ( childValues_[index] );
                    else {
                        writeIndent();
                        writeValue ( childValue );
                    }
                    if ( ++index == size ) {
                        writeCommentAfterValueOnSameLine ( childValue );
                        break;
                    }
                    document_ += ",";
                    writeCommentAfterValueOnSameLine ( childValue );
                }
                unindent();
                writeWithIndent ( "]" );
            }
            else { // output on a single line
                //assert(childValues_.size() == size);
                document_ += "[ ";
                for ( unsigned index = 0; index < size; ++index ) {
                    if ( index > 0 )
                        document_ += ", ";
                    document_ += childValues_[index];
                }
                document_ += " ]";
            }
        }
    }
    bool isMultineArray ( const Value& value ) {
        int size = value.size();
        bool isMultiLine = size * 3 >= rightMargin_;
        childValues_.clear();
        for ( int index = 0; index < size && !isMultiLine; ++index ) {
            const Value& childValue = value[index];
            isMultiLine = isMultiLine ||
                          ( ( childValue.isArray() || childValue.isObject() ) &&
                            childValue.size() > 0 );
        }
        if ( !isMultiLine ) { // check if line length > max line length
            childValues_.reserve ( size );
            addChildValues_ = true;
            int lineLength = 4 + ( size - 1 ) * 2; // '[ ' + ', '*n + ' ]'
            for ( int index = 0; index < size && !isMultiLine; ++index ) {
                writeValue ( value[index] );
                lineLength += int ( childValues_[index].length() );
                isMultiLine = isMultiLine  &&  hasCommentForValue ( value[index] );
            }
            addChildValues_ = false;
            isMultiLine = isMultiLine || lineLength >= rightMargin_;
        }
        return isMultiLine;
    }
    void pushValue ( const std::string& value ) {
        if ( addChildValues_ )
            childValues_.push_back ( value );
        else
            document_ += value;
    }
    void writeIndent() {
        if ( !document_.empty() ) {
            char last = document_[document_.length() - 1];
            if ( last == ' ' )   // already indented
                return;
            if ( last != '\n' )  // Comments may add new-line
                document_ += '\n';
        }
        document_ += indentString_;
    }
    void writeWithIndent ( const std::string& value ) {
        writeIndent();
        document_ += value;
    }
    void indent() {
        indentString_ += std::string ( indentSize_, ' ' );
    }
    void unindent() {
        //assert(int(indentString_.size()) >= indentSize_);
        indentString_.resize ( indentString_.size() - indentSize_ );
    }
    void writeCommentBeforeValue ( const Value& root ) {
        if ( !root.hasComment ( commentBefore ) )
            return;
        document_ += normalizeEOL ( root.getComment ( commentBefore ) );
        document_ += "\n";
    }
    void writeCommentAfterValueOnSameLine ( const Value& root ) {
        if ( root.hasComment ( commentAfterOnSameLine ) )
            document_ += " " + normalizeEOL ( root.getComment ( commentAfterOnSameLine ) );

        if ( root.hasComment ( commentAfter ) ) {
            document_ += "\n";
            document_ += normalizeEOL ( root.getComment ( commentAfter ) );
            document_ += "\n";
        }
    }
    bool hasCommentForValue ( const Value& value ) {
        return value.hasComment ( commentBefore )
               || value.hasComment ( commentAfterOnSameLine )
               || value.hasComment ( commentAfter );
    }
    static std::string normalizeEOL ( const std::string& text ) {
        std::string normalized;
        normalized.reserve ( text.length() );
        const char* begin = text.c_str();
        const char* end = begin + text.length();
        const char* current = begin;
        while ( current != end ) {
            char c = *current++;
            if ( c == '\r' ) { // mac or dos EOL
                if ( *current == '\n' ) // convert dos EOL
                    ++current;
                normalized += '\n';
            }
            else // handle unix EOL & other char
                normalized += c;
        }
        return normalized;
    }

    typedef std::vector<std::string> ChildValues;

    ChildValues childValues_;
    std::string document_;
    std::string indentString_;
    int rightMargin_ = 74;
    int indentSize_ = 4;
    bool addChildValues_;
};

}

#endif // JSON_MOD_WRITER_H
