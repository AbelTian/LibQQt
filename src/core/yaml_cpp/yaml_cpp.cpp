#include "yaml_cpp.h"


#include "yaml-cpp/parser.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/yaml.h"

#include <iostream>
using namespace std;


QByteArray toYAML ( const QQtDictionary& dict )
{

    YAML::Node node;
    packDictionaryToYamlNode ( dict, node );
    //std::cout << "================(A)=============" << std::endl;
    //std::cout << node << std::endl;


    std::string buffer;
    buffer = YAML::Dump ( node );

    QByteArray bytes;
    bytes = QByteArray::fromStdString ( buffer );

    //std::cout << "================(B)=============" << std::endl;
    //qDebug() << qPrintable ( bytes );

    return bytes;
}

void fromYAML ( const QByteArray& yaml, QQtDictionary& dict )
{

    //这个东西非常容易崩溃。
    YAML::Node config;

#if 1
    try
    {
        config = YAML::Load ( yaml );
        //std::cout << config << std::endl;
    }
    catch ( const YAML::Exception& e )
    {
        //-—
        //? [ bad conversion but exited crashed
        std::cerr << e.what() << std::endl;
        return;
    }
#elif 0
    //YAML::Parser parser();
#else
    config = YAML::Load ( yaml );
#endif


    parseYamlNodeToDictionary ( config, dict );
    //qDebug() << "=================";
    //qDebug() << dict;
    //qDebug() << qPrintable ( QString ( dict.toJson ( QJsonDocument::Indented ) ) );
}



void parseYamlNodeToDictionary ( const YAML::Node& node, QQtDictionary& object )
{
    if ( node.IsNull() )
    {
        //qDebug() << "empty value"; //null
        object = QString();
    }
    else if ( node.IsScalar() )
    {
        //auto it = node.begin();
        //qDebug() << QString::fromStdString ( node.Scalar() );
        object = QString::fromStdString ( node.Scalar() );
    }
    else if ( node.IsSequence() )
    {
        int id = 0;
        for ( YAML::Node::const_iterator it = node.begin(); it != node.end(); ++it )
        {
            const YAML::Node& obj = *it;
            parseYamlNodeToDictionary ( obj,  object[id++] );
        }
    }
    else if ( node.IsMap() )
    {
        for ( YAML::Node::const_iterator it = node.begin(); it != node.end(); ++it )
        {
            //qDebug() << QString::fromStdString ( it->first.as<string>() ) << ":" << it->second.Type();
            QString key = QString::fromStdString ( it->first.as<string>() ) ;
            parseYamlNodeToDictionary ( it->second, object[key] );

        }
    }
}

void packDictionaryToYamlNode ( const QQtDictionary& node, YAML::Node& object )
{
    switch ( node.getType() )
    {
        case QQtDictionary:: DictValue:
        {
            //null, bool, double, string
            std::string value = node.getValue().toString().toStdString();
            object = value;
            break;
        }
        case  QQtDictionary:: DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
                QList<QQtDictionary>& l = node.getList();
                YAML::Node value;
                packDictionaryToYamlNode ( l[i], value );
                object.push_back ( value );
            }
            break;
        }
        case QQtDictionary::  DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin(); itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& qkey = itor.key();
                std::string key = qkey.toStdString();
                const QQtDictionary& srcvalue = itor.value();
                YAML::Node value;
                packDictionaryToYamlNode ( srcvalue, value );
                object[key] = value;
            }
            break;
        }
        case  QQtDictionary:: DictMax:
        default:
            break;
    }

}
