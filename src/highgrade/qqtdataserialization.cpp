#include <qqtdataserialization.h>

#include <QDebug>
#include <qqtcore.h>

QQtDataSerialization::QQtDataSerialization ( QObject* parent )
    : QQtMessage ( parent )
{
    mIndex = 0;
}

void QQtDataSerialization::clear() { mDict.clear(); }

void QQtDataSerialization::seek ( int index ) { mIndex = index; }

int QQtDataSerialization::pos()
{
    return mIndex;
}

int QQtDataSerialization::length() { return 2 + 2 + mDict.toJson ( QJsonDocument::Compact ).size() + 2 + 2; }

void QQtDataSerialization::dump()
{
    quint16 header = 0x77EE;
    quint16 size = 0;
    QByteArray json_data;
    quint16 checksum = 0;
    quint16 tail = 0x77FF;

    QByteArray bytes = mBytes;
    bytes >> header >> size;
    int json_size = size - ( 2 + 2 + 2 + 2 );
    json_data.resize ( json_size );
    bytes >> json_data;
    bytes >> checksum >> tail;

    QQtDictionary dict;
    dict.fromJson ( json_data );
    QByteArray data = dict.toJson ( QJsonDocument::Indented );

    qDebug() << "{" << hex << header << ", "
             << oct << size  << ", "
             << oct << json_data.size() << ", "
             << hex << checksum << ", "
             << hex << tail
             << "}";
    qDebug() << qPrintable ( data );
}

void QQtDataSerialization::dump_dictionary()
{
    QQtDictionary& dict = mDict;
    qDebug() << dict["Root"];;
}

void QQtDataSerialization::packer ( QByteArray& l ) const
{
    quint16 header = 0x77EE;
    quint16 size = 0;
    QByteArray json_data;
    quint16 checksum = 0;
    quint16 tail = 0x77FF;

    json_data = mDict.toJson ( QJsonDocument::Compact );
    size = 2 + 2 + json_data.size() + 2 + 2;
    for ( int i = 0; i < json_data.size(); i++ )
    {
        char check = json_data.data() [i];
        if ( checksum + check >= 0x77FF )
            checksum = 0;
        checksum = checksum + ( quint16 ) check;
    }
    QByteArray& bytes = l;
    bytes << header << size << json_data << checksum << tail;
}

void QQtDataSerialization::parser ( const QByteArray& _l )
{
    quint16 header = 0x77EE;
    quint16 size = 0;
    QByteArray json_data;
    quint16 checksum = 0;
    quint16 tail = 0x77FF;

    QByteArray bytes = _l;
    bytes >> header >> size;
    int json_size = size - ( 2 + 2 + 2 + 2 );
    json_data.resize ( json_size );
    bytes >> json_data;
    bytes >> checksum >> tail;

    QQtDictionary& dict = mDict;
    dict.fromJson ( json_data );
}
