#ifndef QQTDICTHELPER_H
#define QQTDICTHELPER_H

#include <qqt-local.h>

#include <qqtdictionary.h>
#include <qqtordereddictionary.h>

//别名，Q开头的Dictionary。
typedef QQtDictionary QDictionary;
typedef QQtOrderedDictionary QOrderedDictionary;

typedef QQtDictionaryMap QDictionaryMap;
typedef QQtDictionaryMapIterator QDictionaryMapIterator;
typedef QQtDictionaryMutableMapIterator QDictionaryMutableMapIterator;

typedef QQtDictionaryList QDictionaryList;
typedef QQtDictionaryListIterator QDictionaryListIterator;
typedef QQtDictionaryMutableListIterator QDictionaryMutableListIterator;

typedef QQtOrderedDictionaryMap QOrderedDictionaryMap;
typedef QQtOrderedDictionaryMapIterator QOrderedDictionaryMapIterator;
typedef QQtOrderedDictionaryMutableMapIterator QOrderedDictionaryMutableMapIterator;

typedef QQtOrderedDictionaryList QOrderedDictionaryList;
typedef QQtOrderedDictionaryListIterator QOrderedDictionaryListIterator;
typedef QQtOrderedDictionaryMutableListIterator QOrderedDictionaryMutableListIterator;

//C++ []操作符重载超过两层就不能赋值给引用变量了，所以这里对于获取深层引用进行封装。
QQtDictionary& QQtGetDictNode ( QQtDictionary& rootDict,
                                QList<QString>& keyList1, bool numberAsString = false );
QQtOrderedDictionary& QQtGetDictNode ( QQtOrderedDictionary& rootDict,
                                       QList<QString>& keyList1, bool numberAsString = false );

#endif // QQTDICTHELPER_H
