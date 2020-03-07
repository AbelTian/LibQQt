#ifndef YAML_CPP_H
#define YAML_CPP_H

#include <qqtdictionary.h>

#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/eventhandler.h"
#include "yaml-cpp/parser.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/yaml.h"

#include "yaml_cpp_global.h"

class YAML_CPPSHARED_EXPORT NullEventHandler : public YAML::EventHandler
{
public:
    typedef YAML::Mark Mark;
    typedef YAML::anchor_t anchor_t;

    NullEventHandler() {}

    virtual void OnDocumentStart ( const Mark& ) {}
    virtual void OnDocumentEnd() {}
    virtual void OnNull ( const Mark&, anchor_t ) {}
    virtual void OnAlias ( const Mark&, anchor_t ) {}
    virtual void OnScalar ( const Mark&, const std::string&, anchor_t,
                            const std::string& ) {}
    virtual void OnSequenceStart ( const Mark&, const std::string&, anchor_t,
                                   YAML::EmitterStyle::value style ) {}
    virtual void OnSequenceEnd() {}
    virtual void OnMapStart ( const Mark&, const std::string&, anchor_t,
                              YAML::EmitterStyle::value style ) {}
    virtual void OnMapEnd() {}
};

YAML_CPPSHARED_EXPORT QByteArray toYAML ( const QQtDictionary& dict );
YAML_CPPSHARED_EXPORT void fromYAML ( const QByteArray& yaml, QQtDictionary& dict );

YAML_CPPSHARED_EXPORT void parseYamlNodeToDictionary ( const YAML::Node& node, QQtDictionary& object );
YAML_CPPSHARED_EXPORT void packDictionaryToYamlNode ( const QQtDictionary& node, YAML::Node& object );

#endif // YAML_CPP_H
