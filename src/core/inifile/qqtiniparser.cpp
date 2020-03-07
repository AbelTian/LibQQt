#include "qqtiniparser.h"

#include <QDebug>

#include "inifile.h"
#include "qqtdictionary.h"

QByteArray toIni ( const QQtDictionary& dict )
{
    const QQtDictionary& node = dict;

    inifile::IniFile p0;
    switch ( dict.getType() )
    {
        case QQtDictionary::DictValue:
        {
            break;
        }
        case QQtDictionary::DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
#if 0
                QList<QQtDictionary>& l = node.getList();
                if ( l[i].getType() == QQtDictionary::DictValue )
                {
                    QString qkey = QString::number ( i );
                    string key = qkey.toStdString();
                    string value = l[i].getValue().toString().toStdString();
                    string comment = node["__comments__"][""][qkey]["#comment"].getValue().toString().toStdString();
                    string right_comment = node["__comments__"][""][qkey]["#right_comment"].getValue().toString().toStdString();
                    p0.SetStringValue ( "", key, value );
                    p0.SetComment ( "", key, comment );
                    p0.SetRightComment ( "", key, right_comment );
                }
#else
                const QString& sec = QString::number ( i );
                string stdsec = sec.toStdString();

                QList<QQtDictionary>& l = node.getList();
                const QQtDictionary& srcvalue = l[i];

                p0.AddSection ( stdsec );

                string comment = node["__comments__"][sec]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][sec]["#right_comment"].getValue().toString().toStdString();
                p0.SetComment ( stdsec, "", comment );
                p0.SetRightComment ( stdsec, "", right_comment );

                if ( srcvalue.getType() == QQtDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QQtDictionary::DictValue )
                        {
                            QString qkey = QString::number ( i );
                            string key = qkey.toStdString();
                            string value = l[i].getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, key, value );
                            p0.SetComment ( stdsec, key, comment );
                            p0.SetRightComment ( stdsec, key, right_comment );
                        }
                    }
                }

                if ( srcvalue.getType() == QQtDictionary::DictMap )
                {
                    for ( QMap<QString, QQtDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QMap<QString, QQtDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QQtDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QQtDictionary::DictValue )
                        {
                            string value = srcvalue2.getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey2]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey2]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, stdkey2, value );
                            p0.SetComment ( stdsec, stdkey2, comment );
                            p0.SetRightComment ( stdsec, stdkey2, right_comment );
                        }
                    }
                }

#endif
            }
            break;
        }
        case QQtDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& sec = itor.key();
                string stdsec = sec.toStdString();
                const QQtDictionary& srcvalue = itor.value();

                if ( sec == "__comments__" )
                    continue;

                p0.AddSection ( stdsec );

                string comment = node["__comments__"][sec]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][sec]["#right_comment"].getValue().toString().toStdString();
                //qDebug() << QString::fromStdString ( comment );
                //qDebug() << QString::fromStdString ( right_comment );
                int ret;
                ret = p0.SetComment ( stdsec, "", comment );
                //qDebug() << ret;
                ret = p0.SetRightComment ( stdsec, "", right_comment );
                //qDebug() << ret;

                if ( srcvalue.getType() == QQtDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QQtDictionary::DictValue )
                        {
                            QString qkey = QString::number ( i );
                            string key = qkey.toStdString();
                            string value = l[i].getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, key, value );
                            p0.SetComment ( stdsec, key, comment );
                            p0.SetRightComment ( stdsec, key, right_comment );
                        }
                    }
                }

                if ( srcvalue.getType() == QQtDictionary::DictMap )
                {
                    for ( QMap<QString, QQtDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QMap<QString, QQtDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QQtDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QQtDictionary::DictValue )
                        {
                            string value = srcvalue2.getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey2]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey2]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, stdkey2, value );
                            p0.SetComment ( stdsec, stdkey2, comment );
                            p0.SetRightComment ( stdsec, stdkey2, right_comment );
                        }
                    }
                }
            }
            break;
        }
        case QQtDictionary::DictMax:
        default:
            break;
    }

    int ret;

    std::string buffer;
    ret = p0.SaveToContent ( buffer );
    //qDebug() << ret;

    QByteArray bytes = QByteArray::fromStdString ( buffer );
    //qDebug() << qPrintable ( bytes );

    //不返回会崩溃
    return bytes;
}

void fromIni ( const QByteArray& bytes, QQtDictionary& dict )
{
    inifile::IniFile p0;
    int ret;
    ret = p0.LoadFromContent ( bytes.toStdString() );

    //qDebug() << ret;
    vector<string> secs;
    ret = p0.GetSections ( &secs );
    for ( vector<string>::iterator itor = secs.begin();
          itor != secs.end(); itor++ )
    {
        string& secName = *itor;
        inifile::IniSection* sec = p0.getSection ( secName );
        //sec name
        string name = sec->name; QString qname = QString::fromStdString ( name );
        //sec comment
        string comment = sec->comment; QString qcomment = QString::fromStdString ( comment );
        //sec right_comment
        string right_comment = sec->rightComment; QString qright_comment = QString::fromStdString ( right_comment );

        dict["__comments__"][qname]["#comment"] = qcomment;
        dict["__comments__"][qname]["#right_comment"] = qright_comment;

        //sec child
        for ( inifile::IniSection::IniItem_it it = sec->begin();
              it != sec->end(); it++ )
        {
            inifile::IniItem& item = *it;

            //#comment
            string comment = item.comment; QString qcomment = QString::fromStdString ( comment );
            //#right_comment
            string right_comment = item.rightComment; QString qright_comment = QString::fromStdString ( right_comment );
            //key
            string key = item.key; QString qkey = QString::fromStdString ( key );
            //value
            string value = item.value; QString qvalue = QString::fromStdString ( value );

            dict["__comments__"][qname][qkey]["#comment"] = qcomment;
            dict["__comments__"][qname][qkey]["#right_comment"] = qright_comment;
            dict[qname][qkey] = qvalue;
        }
    }

    //qDebug() << qPrintable ( dict.toJson ( QJsonDocument::Indented ) );
}

QByteArray toProperties ( const QQtDictionary& dict )
{
    const QQtDictionary& node = dict;

    inifile::IniFile p0;
    switch ( dict.getType() )
    {
        case QQtDictionary::DictValue:
        {
            break;
        }
        case QQtDictionary::DictList:
        {
            //"name":[a, b, ...]
            for ( int i = 0; i < node.getList().size(); i++ )
            {
#if 0
                QList<QQtDictionary>& l = node.getList();
                if ( l[i].getType() == QQtDictionary::DictValue )
                {
                    QString qkey = QString::number ( i );
                    string key = qkey.toStdString();
                    string value = l[i].getValue().toString().toStdString();
                    string comment = node["__comments__"][""][qkey]["#comment"].getValue().toString().toStdString();
                    string right_comment = node["__comments__"][""][qkey]["#right_comment"].getValue().toString().toStdString();
                    p0.SetStringValue ( "", key, value );
                    p0.SetComment ( "", key, comment );
                    p0.SetRightComment ( "", key, right_comment );
                }
#elif 0
                const QString& sec = QString::number ( i );
                string stdsec = sec.toStdString();

                QList<QQtDictionary>& l = node.getList();
                const QQtDictionary& srcvalue = l[i];

                p0.AddSection ( stdsec );

                string comment = node["__comments__"][sec]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][sec]["#right_comment"].getValue().toString().toStdString();
                p0.SetComment ( stdsec, "", comment );
                p0.SetRightComment ( stdsec, "", right_comment );

                if ( srcvalue.getType() == QQtDictionary::DictList )
                {
                    for ( int i = 0; i < srcvalue.getList().size(); i++ )
                    {
                        QList<QQtDictionary>& l = srcvalue.getList();
                        if ( l[i].getType() == QQtDictionary::DictValue )
                        {
                            QString qkey = QString::number ( i );
                            string key = qkey.toStdString();
                            string value = l[i].getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, key, value );
                            p0.SetComment ( stdsec, key, comment );
                            p0.SetRightComment ( stdsec, key, right_comment );
                        }
                    }
                }

                if ( srcvalue.getType() == QQtDictionary::DictMap )
                {
                    for ( QMap<QString, QQtDictionary>::Iterator itor2 = srcvalue.getMap().begin();
                          itor2 != srcvalue.getMap().end(); itor2++ )
                    {
                        //QMap<QString, QQtDictionary>& m = node.getMap();
                        const QString& qkey2 = itor2.key();
                        string stdkey2 = qkey2.toStdString();
                        const QQtDictionary& srcvalue2 = itor2.value();
                        if ( srcvalue2.getType() == QQtDictionary::DictValue )
                        {
                            string value = srcvalue2.getValue().toString().toStdString();
                            string comment = node["__comments__"][sec][qkey2]["#comment"].getValue().toString().toStdString();
                            string right_comment = node["__comments__"][sec][qkey2]["#right_comment"].getValue().toString().toStdString();
                            p0.SetStringValue ( stdsec, stdkey2, value );
                            p0.SetComment ( stdsec, stdkey2, comment );
                            p0.SetRightComment ( stdsec, stdkey2, right_comment );
                        }
                    }
                }
#else
                const QString& key = QString::number ( i );
                string stdkey = key.toStdString();
                QList<QQtDictionary>& l = node.getList();
                const QQtDictionary& srcvalue = l[i];

                if ( key == "__comments__" )
                    continue;

                if ( srcvalue.getType() != QQtDictionary::DictValue )
                    continue;

                p0.AddSection ( "" );

                string value = srcvalue.getValue().toString().toStdString();
                string comment = node["__comments__"][key]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][key]["#right_comment"].getValue().toString().toStdString();
                p0.SetStringValue ( "", stdkey, value );
                p0.SetComment ( "", stdkey, comment );
                p0.SetRightComment ( "", stdkey, right_comment );
#endif
            }
            break;
        }
        case QQtDictionary::DictMap:
        {
            //"name": {"a":"b", "a2":"b2", "a3":["b31", "b32"], "a4":{"a41":"b41", "a42":"b42"}, ...}
            for ( QMap<QString, QQtDictionary>::Iterator itor = node.getMap().begin();
                  itor != node.getMap().end(); itor++ )
            {
                //QMap<QString, QQtDictionary>& m = node.getMap();
                const QString& key = itor.key();
                string stdkey = key.toStdString();
                const QQtDictionary& srcvalue = itor.value();

                if ( key == "__comments__" )
                    continue;

                if ( srcvalue.getType() != QQtDictionary::DictValue )
                    continue;

                p0.AddSection ( "" );

                string value = srcvalue.getValue().toString().toStdString();
                string comment = node["__comments__"][key]["#comment"].getValue().toString().toStdString();
                string right_comment = node["__comments__"][key]["#right_comment"].getValue().toString().toStdString();
                p0.SetStringValue ( "", stdkey, value );
                p0.SetComment ( "", stdkey, comment );
                p0.SetRightComment ( "", stdkey, right_comment );
            }
            break;
        }
        case QQtDictionary::DictMax:
        default:
            break;
    }

    int ret;

    std::string buffer;
    ret = p0.SaveToContent ( buffer );
    //qDebug() << ret;

    QByteArray bytes = QByteArray::fromStdString ( buffer );
    //qDebug() << qPrintable ( bytes );

    //不返回会崩溃
    return bytes;
}

void fromProperties ( const QByteArray& bytes, QQtDictionary& dict )
{
    inifile::IniFile p0;
    int ret;
    ret = p0.LoadFromContent ( bytes.toStdString() );

    //qDebug() << ret;
    vector<string> secs;
    ret = p0.GetSections ( &secs );
    for ( vector<string>::iterator itor = secs.begin();
          itor != secs.end(); itor++ )
    {
        string& secName = *itor;
        if ( secName != "" )
            continue;

        inifile::IniSection* sec = p0.getSection ( secName );
        //sec child
        for ( inifile::IniSection::IniItem_it it = sec->begin();
              it != sec->end(); it++ )
        {
            inifile::IniItem& item = *it;

            //#comment
            string comment = item.comment; QString qcomment = QString::fromStdString ( comment );
            //#right_comment
            string right_comment = item.rightComment; QString qright_comment = QString::fromStdString ( right_comment );
            //key
            string key = item.key; QString qkey = QString::fromStdString ( key );
            //value
            string value = item.value; QString qvalue = QString::fromStdString ( value );

            dict["__comments__"][qkey]["#comment"] = qcomment;
            dict["__comments__"][qkey]["#right_comment"] = qright_comment;
            dict[qkey] = qvalue;
        }
    }

    //qDebug() << qPrintable ( dict.toJson ( QJsonDocument::Indented ) );
}
