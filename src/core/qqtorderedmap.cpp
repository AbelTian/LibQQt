#include <qqtorderedmap.h>

#include <stdlib.h>

#ifdef QT_QMAP_DEBUG
# include <qstring.h>
# include <qvector.h>
#endif

QT_BEGIN_NAMESPACE

/*!
    \class QOrderedMap
    \inmodule QtCore
    \brief The QOrderedMap class is a template class that provides a red-black-tree-based dictionary.

    \ingroup tools
    \ingroup shared

    \reentrant

    QOrderedMap\<Key, T\> is one of Qt's generic \l{container classes}. It
    stores (key, value) pairs and provides fast lookup of the
    value associated with a key.

    QOrderedMap and QHash provide very similar functionality. The
    differences are:

    \list
    \li QHash provides average faster lookups than QOrderedMap. (See \l{Algorithmic
       Complexity} for details.)
    \li When iterating over a QHash, the items are arbitrarily ordered.
       With QOrderedMap, the items are always sorted by key.
    \li The key type of a QHash must provide operator==() and a global
       qHash(Key) function. The key type of a QOrderedMap must provide
       operator<() specifying a total order. Since Qt 5.8.1 it is also safe
       to use a pointer type as key, even if the underlying operator<()
       does not provide a total order.
    \endlist

    Here's an example QOrderedMap with QString keys and \c int values:
    \snippet code/src_corelib_tools_qmap.cpp 0

    To insert a (key, value) pair into the map, you can use operator[]():

    \snippet code/src_corelib_tools_qmap.cpp 1

    This inserts the following three (key, value) pairs into the
    QOrderedMap: ("one", 1), ("three", 3), and ("seven", 7). Another way to
    insert items into the map is to use insert():

    \snippet code/src_corelib_tools_qmap.cpp 2

    To look up a value, use operator[]() or value():

    \snippet code/src_corelib_tools_qmap.cpp 3

    If there is no item with the specified key in the map, these
    functions return a \l{default-constructed value}.

    If you want to check whether the map contains a certain key, use
    contains():

    \snippet code/src_corelib_tools_qmap.cpp 4

    There is also a value() overload that uses its second argument as
    a default value if there is no item with the specified key:

    \snippet code/src_corelib_tools_qmap.cpp 5

    In general, we recommend that you use contains() and value()
    rather than operator[]() for looking up a key in a map. The
    reason is that operator[]() silently inserts an item into the
    map if no item exists with the same key (unless the map is
    const). For example, the following code snippet will create 1000
    items in memory:

    \snippet code/src_corelib_tools_qmap.cpp 6

    To avoid this problem, replace \c map[i] with \c map.value(i)
    in the code above.

    If you want to navigate through all the (key, value) pairs stored
    in a QOrderedMap, you can use an iterator. QOrderedMap provides both
    \l{Java-style iterators} (QOrderedMapIterator and QMutableMapIterator)
    and \l{STL-style iterators} (QOrderedMap::const_iterator and
    QOrderedMap::iterator). Here's how to iterate over a QOrderedMap<QString, int>
    using a Java-style iterator:

    \snippet code/src_corelib_tools_qmap.cpp 7

    Here's the same code, but using an STL-style iterator this time:

    \snippet code/src_corelib_tools_qmap.cpp 8

    The items are traversed in ascending key order.

    Normally, a QOrderedMap allows only one value per key. If you call
    insert() with a key that already exists in the QOrderedMap, the
    previous value will be erased. For example:

    \snippet code/src_corelib_tools_qmap.cpp 9

    However, you can store multiple values per key by using
    insertMulti() instead of insert() (or using the convenience
    subclass QOrderedMultiMap). If you want to retrieve all the values for a
    single key, you can use values(const Key &key), which returns a
    QList<T>:

    \snippet code/src_corelib_tools_qmap.cpp 10

    The items that share the same key are available from most
    recently to least recently inserted. Another approach is to call
    find() to get the STL-style iterator for the first item with a
    key and iterate from there:

    \snippet code/src_corelib_tools_qmap.cpp 11

    If you only need to extract the values from a map (not the keys),
    you can also use \l{foreach}:

    \snippet code/src_corelib_tools_qmap.cpp 12

    Items can be removed from the map in several ways. One way is to
    call remove(); this will remove any item with the given key.
    Another way is to use QMutableMapIterator::remove(). In addition,
    you can clear the entire map using clear().

    QOrderedMap's key and value data types must be \l{assignable data
    types}. This covers most data types you are likely to encounter,
    but the compiler won't let you, for example, store a QWidget as a
    value; instead, store a QWidget *. In addition, QOrderedMap's key type
    must provide operator<(). QOrderedMap uses it to keep its items sorted,
    and assumes that two keys \c x and \c y are equal if neither \c{x
    < y} nor \c{y < x} is true.

    Example:
    \snippet code/src_corelib_tools_qmap.cpp 13

    In the example, we start by comparing the employees' names. If
    they're equal, we compare their dates of birth to break the tie.

    \sa QOrderedMapIterator, QMutableMapIterator, QHash, QSet
*/

/*! \fn QOrderedMap::QOrderedMap()

    Constructs an empty map.

    \sa clear()
*/

/*!
    \fn QOrderedMap::QOrderedMap(QOrderedMap<Key, T> &&other)

    Move-constructs a QOrderedMap instance, making it point at the same
    object that \a other was pointing to.

    \since 5.2
*/

/*! \fn QOrderedMap::QOrderedMap(const QOrderedMap<Key, T> &other)

    Constructs a copy of \a other.

    This operation occurs in \l{constant time}, because QOrderedMap is
    \l{implicitly shared}. This makes returning a QOrderedMap from a
    function very fast. If a shared instance is modified, it will be
    copied (copy-on-write), and this takes \l{linear time}.

    \sa operator=()
*/

/*! \fn QOrderedMap::QOrderedMap(const std::map<Key, T> & other)

    Constructs a copy of \a other.

    \sa toStdMap()
*/

/*! \fn QOrderedMap::QOrderedMap(std::initializer_list<std::pair<Key,T> > list)
    \since 5.1

    Constructs a map with a copy of each of the elements in the
    initializer list \a list.

    This function is only available if the program is being
    compiled in C++11 mode.
*/

/*! \fn std::map<Key, T> QOrderedMap::toStdMap() const

    Returns an STL map equivalent to this QOrderedMap.
*/

/*! \fn QOrderedMap::~QOrderedMap()

    Destroys the map. References to the values in the map, and all
    iterators over this map, become invalid.
*/

/*! \fn QOrderedMap<Key, T> &QOrderedMap::operator=(const QOrderedMap<Key, T> &other)

    Assigns \a other to this map and returns a reference to this map.
*/

/*!
    \fn QOrderedMap<Key, T> &QOrderedMap::operator=(QOrderedMap<Key, T> &&other)

    Move-assigns \a other to this QOrderedMap instance.

    \since 5.2
*/

/*! \fn void QOrderedMap::swap(QOrderedMap<Key, T> &other)
    \since 4.8

    Swaps map \a other with this map. This operation is very
    fast and never fails.
*/

/*! \fn void QOrderedMultiMap::swap(QOrderedMultiMap<Key, T> &other)
    \since 4.8

    Swaps map \a other with this map. This operation is very
    fast and never fails.
*/

/*! \fn bool QOrderedMap::operator==(const QOrderedMap<Key, T> &other) const

    Returns \c true if \a other is equal to this map; otherwise returns
    false.

    Two maps are considered equal if they contain the same (key,
    value) pairs.

    This function requires the value type to implement \c
    operator==().

    \sa operator!=()
*/

/*! \fn bool QOrderedMap::operator!=(const QOrderedMap<Key, T> &other) const

    Returns \c true if \a other is not equal to this map; otherwise
    returns \c false.

    Two maps are considered equal if they contain the same (key,
    value) pairs.

    This function requires the value type to implement \c
    operator==().

    \sa operator==()
*/

/*! \fn int QOrderedMap::size() const

    Returns the number of (key, value) pairs in the map.

    \sa isEmpty(), count()
*/

/*!
    \fn bool QOrderedMap::isEmpty() const

    Returns \c true if the map contains no items; otherwise returns
    false.

    \sa size()
*/

/*! \fn void QOrderedMap::detach()

    \internal

    Detaches this map from any other maps with which it may share
    data.

    \sa isDetached()
*/

/*! \fn bool QOrderedMap::isDetached() const

    \internal

    Returns \c true if the map's internal data isn't shared with any
    other map object; otherwise returns \c false.

    \sa detach()
*/

/*! \fn void QOrderedMap::setSharable(bool sharable)

    \internal
*/

/*! \fn bool QOrderedMap::isSharedWith(const QOrderedMap<Key, T> &other) const

    \internal
*/

/*! \fn void QOrderedMap::clear()

    Removes all items from the map.

    \sa remove()
*/

/*! \fn int QOrderedMap::remove(const Key &key)

    Removes all the items that have the key \a key from the map.
    Returns the number of items removed which is usually 1 but will be
    0 if the key isn't in the map, or \> 1 if insertMulti() has been
    used with the \a key.

    \sa clear(), take(), QOrderedMultiMap::remove()
*/

/*! \fn T QOrderedMap::take(const Key &key)

    Removes the item with the key \a key from the map and returns
    the value associated with it.

    If the item does not exist in the map, the function simply
    returns a \l{default-constructed value}. If there are multiple
    items for \a key in the map, only the most recently inserted one
    is removed and returned.

    If you don't use the return value, remove() is more efficient.

    \sa remove()
*/

/*! \fn bool QOrderedMap::contains(const Key &key) const

    Returns \c true if the map contains an item with key \a key;
    otherwise returns \c false.

    \sa count(), QOrderedMultiMap::contains()
*/

/*! \fn const T QOrderedMap::value(const Key &key, const T &defaultValue) const

    Returns the value associated with the key \a key.

    If the map contains no item with key \a key, the function returns
    \a defaultValue. If no \a defaultValue is specified, the function
    returns a \l{default-constructed value}. If there are multiple
    items for \a key in the map, the value of the most recently
    inserted one is returned.

    \sa key(), values(), contains(), operator[]()
*/

/*! \fn T &QOrderedMap::operator[](const Key &key)

    Returns the value associated with the key \a key as a modifiable
    reference.

    If the map contains no item with key \a key, the function inserts
    a \l{default-constructed value} into the map with key \a key, and
    returns a reference to it. If the map contains multiple items
    with key \a key, this function returns a reference to the most
    recently inserted value.

    \sa insert(), value()
*/

/*! \fn const T QOrderedMap::operator[](const Key &key) const

    \overload

    Same as value().
*/

/*! \fn QList<Key> QOrderedMap::uniqueKeys() const
    \since 4.2

    Returns a list containing all the keys in the map in ascending
    order. Keys that occur multiple times in the map (because items
    were inserted with insertMulti(), or unite() was used) occur only
    once in the returned list.

    \sa keys(), values()
*/

/*! \fn QList<Key> QOrderedMap::keys() const

    Returns a list containing all the keys in the map in ascending
    order. Keys that occur multiple times in the map (because items
    were inserted with insertMulti(), or unite() was used) also
    occur multiple times in the list.

    To obtain a list of unique keys, where each key from the map only
    occurs once, use uniqueKeys().

    The order is guaranteed to be the same as that used by values().

    \sa uniqueKeys(), values(), key()
*/

/*! \fn QList<Key> QOrderedMap::keys(const T &value) const

    \overload

    Returns a list containing all the keys associated with value \a
    value in ascending order.

    This function can be slow (\l{linear time}), because QOrderedMap's
    internal data structure is optimized for fast lookup by key, not
    by value.
*/

/*!
    \fn Key QOrderedMap::key(const T &value, const Key &defaultKey) const
    \since 4.3
    \overload

    Returns the first key with value \a value, or \a defaultKey if
    the map contains no item with value \a value. If no \a defaultKey
    is provided the function returns a
    \l{default-constructed value}{default-constructed key}.

    This function can be slow (\l{linear time}), because QOrderedMap's
    internal data structure is optimized for fast lookup by key, not
    by value.

    \sa value(), keys()
*/

/*! \fn QList<T> QOrderedMap::values() const

    Returns a list containing all the values in the map, in ascending
    order of their keys. If a key is associated with multiple values,
    all of its values will be in the list, and not just the most
    recently inserted one.

    \sa keys(), value()
*/

/*! \fn QList<T> QOrderedMap::values(const Key &key) const

    \overload

    Returns a list containing all the values associated with key
    \a key, from the most recently inserted to the least recently
    inserted one.

    \sa count(), insertMulti()
*/

/*! \fn int QOrderedMap::count(const Key &key) const

    Returns the number of items associated with key \a key.

    \sa contains(), insertMulti(), QOrderedMultiMap::count()
*/

/*! \fn int QOrderedMap::count() const

    \overload

    Same as size().
*/

/*! \fn QOrderedMap::iterator QOrderedMap::begin()

    Returns an \l{STL-style iterators}{STL-style iterator} pointing to the first item in
    the map.

    \sa constBegin(), end()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::begin() const

    \overload
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::cbegin() const
    \since 5.0

    Returns a const \l{STL-style iterators}{STL-style iterator} pointing to the first item
    in the map.

    \sa begin(), cend()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::constBegin() const

    Returns a const \l{STL-style iterators}{STL-style iterator} pointing to the first item
    in the map.

    \sa begin(), constEnd()
*/

/*! \fn QOrderedMap::key_iterator QOrderedMap::keyBegin() const
    \since 5.6

    Returns a const \l{STL-style iterators}{STL-style iterator} pointing to the first key
    in the map.

    \sa keyEnd(), firstKey()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::end()

    Returns an \l{STL-style iterators}{STL-style iterator} pointing to the imaginary item
    after the last item in the map.

    \sa begin(), constEnd()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::end() const

    \overload
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::cend() const
    \since 5.0

    Returns a const \l{STL-style iterators}{STL-style iterator} pointing to the imaginary
    item after the last item in the map.

    \sa cbegin(), end()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::constEnd() const

    Returns a const \l{STL-style iterators}{STL-style iterator} pointing to the imaginary
    item after the last item in the map.

    \sa constBegin(), end()
*/

/*! \fn QOrderedMap::key_iterator QOrderedMap::keyEnd() const
    \since 5.6

    Returns a const \l{STL-style iterators}{STL-style iterator} pointing to the imaginary
    item after the last key in the map.

    \sa keyBegin(), lastKey()
*/

/*! \fn const Key &QOrderedMap::firstKey() const
    \since 5.2

    Returns a reference to the smallest key in the map.
    This function assumes that the map is not empty.

    This executes in \l{constant time}.

    \sa lastKey(), first(), keyBegin(), isEmpty()
*/

/*! \fn const Key &QOrderedMap::lastKey() const
    \since 5.2

    Returns a reference to the largest key in the map.
    This function assumes that the map is not empty.

    This executes in \l{logarithmic time}.

    \sa firstKey(), last(), keyEnd(), isEmpty()
*/

/*! \fn T &QOrderedMap::first()
    \since 5.2

    Returns a reference to the first value in the map, that is the value mapped
    to the smallest key. This function assumes that the map is not empty.

    When unshared (or const version is called), this executes in \l{constant time}.

    \sa last(), firstKey(), isEmpty()
*/

/*! \fn const T &QOrderedMap::first() const
    \since 5.2

    \overload
*/

/*! \fn T &QOrderedMap::last()
    \since 5.2

    Returns a reference to the last value in the map, that is the value mapped
    to the largest key. This function assumes that the map is not empty.

    When unshared (or const version is called), this executes in \l{logarithmic time}.

    \sa first(), lastKey(), isEmpty()
*/

/*! \fn const T &QOrderedMap::last() const
    \since 5.2

    \overload
*/

/*! \fn QOrderedMap::iterator QOrderedMap::erase(iterator pos)

    Removes the (key, value) pair pointed to by the iterator \a pos
    from the map, and returns an iterator to the next item in the
    map.

    \sa remove()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::find(const Key &key)

    Returns an iterator pointing to the item with key \a key in the
    map.

    If the map contains no item with key \a key, the function
    returns end().

    If the map contains multiple items with key \a key, this
    function returns an iterator that points to the most recently
    inserted value. The other values are accessible by incrementing
    the iterator. For example, here's some code that iterates over all
    the items with the same key:

    \snippet code/src_corelib_tools_qmap.cpp 14

    \sa constFind(), value(), values(), lowerBound(), upperBound(), QOrderedMultiMap::find()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::find(const Key &key) const

    \overload
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::constFind(const Key &key) const
    \since 4.1

    Returns an const iterator pointing to the item with key \a key in the
    map.

    If the map contains no item with key \a key, the function
    returns constEnd().

    \sa find(), QOrderedMultiMap::constFind()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::lowerBound(const Key &key)

    Returns an iterator pointing to the first item with key \a key in
    the map. If the map contains no item with key \a key, the
    function returns an iterator to the nearest item with a greater
    key.

    Example:
    \snippet code/src_corelib_tools_qmap.cpp 15

    If the map contains multiple items with key \a key, this
    function returns an iterator that points to the most recently
    inserted value. The other values are accessible by incrementing
    the iterator. For example, here's some code that iterates over all
    the items with the same key:

    \snippet code/src_corelib_tools_qmap.cpp 16

    \sa upperBound(), find()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::lowerBound(const Key &key) const

    \overload
*/

/*! \fn QOrderedMap::iterator QOrderedMap::upperBound(const Key &key)

    Returns an iterator pointing to the item that immediately follows
    the last item with key \a key in the map. If the map contains no
    item with key \a key, the function returns an iterator to the
    nearest item with a greater key.

    Example:
    \snippet code/src_corelib_tools_qmap.cpp 17

    \sa lowerBound(), find()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::upperBound(const Key &key) const

    \overload
*/

/*! \fn QOrderedMap::iterator QOrderedMap::insert(const Key &key, const T &value)

    Inserts a new item with the key \a key and a value of \a value.

    If there is already an item with the key \a key, that item's value
    is replaced with \a value.

    If there are multiple items with the key \a key, the most
    recently inserted item's value is replaced with \a value.

    \sa insertMulti()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::insert(const_iterator pos, const Key &key, const T &value)
    \overload
    \since 5.1
    Inserts a new item with the key \a key and value \a value and with hint \a pos
    suggesting where to do the insert.

    If constBegin() is used as hint it indicates that the \a key is less than any key in the map
    while constEnd() suggests that the \a key is (strictly) larger than any key in the map.
    Otherwise the hint should meet the condition (\a pos - 1).key() < \a key <= pos.key().
    If the hint \a pos is wrong it is ignored and a regular insert is done.

    If there is already an item with the key \a key, that item's value
    is replaced with \a value.

    If there are multiple items with the key \a key, then exactly one of them
    is replaced with \a value.

    If the hint is correct and the map is unshared, the insert executes in amortized \l{constant time}.

    When creating a map from sorted data inserting the largest key first with constBegin()
    is faster than inserting in sorted order with constEnd(), since constEnd() - 1 (which is needed
    to check if the hint is valid) needs \l{logarithmic time}.

    \b {Note:} Be careful with the hint. Providing an iterator from an older shared instance might
    crash but there is also a risk that it will silently corrupt both the map and the \a pos map.

    \sa insertMulti()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::insertMulti(const Key &key, const T &value)

    Inserts a new item with the key \a key and a value of \a value.

    If there is already an item with the same key in the map, this
    function will simply create a new one. (This behavior is
    different from insert(), which overwrites the value of an
    existing item.)

    \sa insert(), values()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::insertMulti(const_iterator pos, const Key &key, const T &value)
    \overload
    \since 5.1
    Inserts a new item with the key \a key and value \a value and with hint \a pos
    suggesting where to do the insert.

    If constBegin() is used as hint it indicates that the \a key is less than any key in the map
    while constEnd() suggests that the \a key is larger than any key in the map.
    Otherwise the hint should meet the condition (\a pos - 1).key() < \a key <= pos.key().
    If the hint \a pos is wrong it is ignored and a regular insertMulti is done.

    If there is already an item with the same key in the map, this function will simply create a new one.

    \b {Note:} Be careful with the hint. Providing an iterator from an older shared instance might
    crash but there is also a risk that it will silently corrupt both the map and the \a pos map.

    \sa insert()
*/


/*! \fn QOrderedMap<Key, T> &QOrderedMap::unite(const QOrderedMap<Key, T> &other)

    Inserts all the items in the \a other map into this map. If a
    key is common to both maps, the resulting map will contain the
    key multiple times.

    \sa insertMulti()
*/

/*! \typedef QOrderedMap::Iterator

    Qt-style synonym for QOrderedMap::iterator.
*/

/*! \typedef QOrderedMap::ConstIterator

    Qt-style synonym for QOrderedMap::const_iterator.
*/

/*! \typedef QOrderedMap::difference_type

    Typedef for ptrdiff_t. Provided for STL compatibility.
*/

/*! \typedef QOrderedMap::key_type

    Typedef for Key. Provided for STL compatibility.
*/

/*! \typedef QOrderedMap::mapped_type

    Typedef for T. Provided for STL compatibility.
*/

/*! \typedef QOrderedMap::size_type

    Typedef for int. Provided for STL compatibility.
*/

/*!
    \fn bool QOrderedMap::empty() const

    This function is provided for STL compatibility. It is equivalent
    to isEmpty(), returning true if the map is empty; otherwise
    returning false.
*/

/*!
  \fn QPair<iterator, iterator> QOrderedMap::equal_range(const Key &key)

  Returns a pair of iterators delimiting the range of values \c{[first, second)}, that
  are stored under \a key.
*/

/*!
    \fn QPair<const_iterator, const_iterator> QOrderedMap::equal_range(const Key &key) const
    \overload
    \since 5.6
*/


/*! \class QOrderedMap::iterator
    \inmodule QtCore
    \brief The QOrderedMap::iterator class provides an STL-style non-const iterator for QOrderedMap and QOrderedMultiMap.

    QOrderedMap features both \l{STL-style iterators} and \l{Java-style
    iterators}. The STL-style iterators are more low-level and more
    cumbersome to use; on the other hand, they are slightly faster
    and, for developers who already know STL, have the advantage of
    familiarity.

    QOrderedMap\<Key, T\>::iterator allows you to iterate over a QOrderedMap (or
    QOrderedMultiMap) and to modify the value (but not the key) stored under
    a particular key. If you want to iterate over a const QOrderedMap, you
    should use QOrderedMap::const_iterator. It is generally good practice to
    use QOrderedMap::const_iterator on a non-const QOrderedMap as well, unless you
    need to change the QOrderedMap through the iterator. Const iterators are
    slightly faster, and can improve code readability.

    The default QOrderedMap::iterator constructor creates an uninitialized
    iterator. You must initialize it using a QOrderedMap function like
    QOrderedMap::begin(), QOrderedMap::end(), or QOrderedMap::find() before you can
    start iterating. Here's a typical loop that prints all the (key,
    value) pairs stored in a map:

    \snippet code/src_corelib_tools_qmap.cpp 18

    Unlike QHash, which stores its items in an arbitrary order, QOrderedMap
    stores its items ordered by key. Items that share the same key
    (because they were inserted using QOrderedMap::insertMulti(), or due to a
    unite()) will appear consecutively, from the most recently to the
    least recently inserted value.

    Let's see a few examples of things we can do with a
    QOrderedMap::iterator that we cannot do with a QOrderedMap::const_iterator.
    Here's an example that increments every value stored in the QOrderedMap
    by 2:

    \snippet code/src_corelib_tools_qmap.cpp 19

    Here's an example that removes all the items whose key is a
    string that starts with an underscore character:

    \snippet code/src_corelib_tools_qmap.cpp 20

    The call to QOrderedMap::erase() removes the item pointed to by the
    iterator from the map, and returns an iterator to the next item.
    Here's another way of removing an item while iterating:

    \snippet code/src_corelib_tools_qmap.cpp 21

    It might be tempting to write code like this:

    \snippet code/src_corelib_tools_qmap.cpp 22

    However, this will potentially crash in \c{++i}, because \c i is
    a dangling iterator after the call to erase().

    Multiple iterators can be used on the same map. If you add items
    to the map, existing iterators will remain valid. If you remove
    items from the map, iterators that point to the removed items
    will become dangling iterators.

    \warning Iterators on implicitly shared containers do not work
    exactly like STL-iterators. You should avoid copying a container
    while iterators are active on that container. For more information,
    read \l{Implicit sharing iterator problem}.

    \sa QOrderedMap::const_iterator, QOrderedMap::key_iterator, QMutableMapIterator
*/

/*! \typedef QOrderedMap::iterator::difference_type

    \internal
*/

/*! \typedef QOrderedMap::iterator::iterator_category

  A synonym for \e {std::bidirectional_iterator_tag} indicating
  this iterator is a bidirectional iterator.
*/

/*! \typedef QOrderedMap::iterator::pointer

    \internal
*/

/*! \typedef QOrderedMap::iterator::reference

    \internal
*/

/*! \typedef QOrderedMap::iterator::value_type

    \internal
*/

/*! \fn QOrderedMap::iterator::iterator()

    Constructs an uninitialized iterator.

    Functions like key(), value(), and operator++() must not be
    called on an uninitialized iterator. Use operator=() to assign a
    value to it before using it.

    \sa QOrderedMap::begin(), QOrderedMap::end()
*/

/*! \fn QOrderedMap::iterator::iterator(Node *)

    \internal
*/

/*! \fn const Key &QOrderedMap::iterator::key() const

    Returns the current item's key as a const reference.

    There is no direct way of changing an item's key through an
    iterator, although it can be done by calling QOrderedMap::erase()
    followed by QOrderedMap::insert() or QOrderedMap::insertMulti().

    \sa value()
*/

/*! \fn T &QOrderedMap::iterator::value() const

    Returns a modifiable reference to the current item's value.

    You can change the value of an item by using value() on
    the left side of an assignment, for example:

    \snippet code/src_corelib_tools_qmap.cpp 23

    \sa key(), operator*()
*/

/*! \fn T &QOrderedMap::iterator::operator*() const

    Returns a modifiable reference to the current item's value.

    Same as value().

    \sa key()
*/

/*! \fn T *QOrderedMap::iterator::operator->() const

    Returns a pointer to the current item's value.

    \sa value()
*/

/*!
    \fn bool QOrderedMap::iterator::operator==(const iterator &other) const
    \fn bool QOrderedMap::iterator::operator==(const const_iterator &other) const

    Returns \c true if \a other points to the same item as this
    iterator; otherwise returns \c false.

    \sa operator!=()
*/

/*!
    \fn bool QOrderedMap::iterator::operator!=(const iterator &other) const
    \fn bool QOrderedMap::iterator::operator!=(const const_iterator &other) const

    Returns \c true if \a other points to a different item than this
    iterator; otherwise returns \c false.

    \sa operator==()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::iterator::operator++()

    The prefix ++ operator (\c{++i}) advances the iterator to the
    next item in the map and returns an iterator to the new current
    item.

    Calling this function on QOrderedMap::end() leads to undefined results.

    \sa operator--()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::iterator::operator++(int)

    \overload

    The postfix ++ operator (\c{i++}) advances the iterator to the
    next item in the map and returns an iterator to the previously
    current item.
*/

/*! \fn QOrderedMap::iterator QOrderedMap::iterator::operator--()

    The prefix -- operator (\c{--i}) makes the preceding item
    current and returns an iterator pointing to the new current item.

    Calling this function on QOrderedMap::begin() leads to undefined
    results.

    \sa operator++()
*/

/*! \fn QOrderedMap::iterator QOrderedMap::iterator::operator--(int)

    \overload

    The postfix -- operator (\c{i--}) makes the preceding item
    current and returns an iterator pointing to the previously
    current item.
*/

/*! \fn QOrderedMap::iterator QOrderedMap::iterator::operator+(int j) const

    Returns an iterator to the item at \a j positions forward from
    this iterator. (If \a j is negative, the iterator goes backward.)

    This operation can be slow for large \a j values.

    \sa operator-()

*/

/*! \fn QOrderedMap::iterator QOrderedMap::iterator::operator-(int j) const

    Returns an iterator to the item at \a j positions backward from
    this iterator. (If \a j is negative, the iterator goes forward.)

    This operation can be slow for large \a j values.

    \sa operator+()
*/

/*! \fn QOrderedMap::iterator &QOrderedMap::iterator::operator+=(int j)

    Advances the iterator by \a j items. (If \a j is negative, the
    iterator goes backward.)

    \sa operator-=(), operator+()
*/

/*! \fn QOrderedMap::iterator &QOrderedMap::iterator::operator-=(int j)

    Makes the iterator go back by \a j items. (If \a j is negative,
    the iterator goes forward.)

    \sa operator+=(), operator-()
*/

/*! \class QOrderedMap::const_iterator
    \inmodule QtCore
    \brief The QOrderedMap::const_iterator class provides an STL-style const iterator for QOrderedMap and QOrderedMultiMap.

    QOrderedMap features both \l{STL-style iterators} and \l{Java-style
    iterators}. The STL-style iterators are more low-level and more
    cumbersome to use; on the other hand, they are slightly faster
    and, for developers who already know STL, have the advantage of
    familiarity.

    QOrderedMap\<Key, T\>::const_iterator allows you to iterate over a QOrderedMap
    (or a QOrderedMultiMap). If you want to modify the QOrderedMap as you iterate
    over it, you must use QOrderedMap::iterator instead. It is generally
    good practice to use QOrderedMap::const_iterator on a non-const QOrderedMap as
    well, unless you need to change the QOrderedMap through the iterator.
    Const iterators are slightly faster, and can improve code
    readability.

    The default QOrderedMap::const_iterator constructor creates an
    uninitialized iterator. You must initialize it using a QOrderedMap
    function like QOrderedMap::constBegin(), QOrderedMap::constEnd(), or
    QOrderedMap::find() before you can start iterating. Here's a typical
    loop that prints all the (key, value) pairs stored in a map:

    \snippet code/src_corelib_tools_qmap.cpp 24

    Unlike QHash, which stores its items in an arbitrary order, QOrderedMap
    stores its items ordered by key. Items that share the same key
    (because they were inserted using QOrderedMap::insertMulti()) will
    appear consecutively, from the most recently to the least
    recently inserted value.

    Multiple iterators can be used on the same map. If you add items
    to the map, existing iterators will remain valid. If you remove
    items from the map, iterators that point to the removed items
    will become dangling iterators.

    \warning Iterators on implicitly shared containers do not work
    exactly like STL-iterators. You should avoid copying a container
    while iterators are active on that container. For more information,
    read \l{Implicit sharing iterator problem}.

    \sa QOrderedMap::iterator, QOrderedMap::key_iterator, QOrderedMapIterator
*/

/*! \typedef QOrderedMap::const_iterator::difference_type

    \internal
*/

/*! \typedef QOrderedMap::const_iterator::iterator_category

  A synonym for \e {std::bidirectional_iterator_tag} indicating
  this iterator is a bidirectional iterator.
*/

/*! \typedef QOrderedMap::const_iterator::pointer

    \internal
*/

/*! \typedef QOrderedMap::const_iterator::reference

    \internal
*/

/*! \typedef QOrderedMap::const_iterator::value_type

    \internal
*/

/*! \fn QOrderedMap::const_iterator::const_iterator()

    Constructs an uninitialized iterator.

    Functions like key(), value(), and operator++() must not be
    called on an uninitialized iterator. Use operator=() to assign a
    value to it before using it.

    \sa QOrderedMap::constBegin(), QOrderedMap::constEnd()
*/

/*! \fn QOrderedMap::const_iterator::const_iterator(const Node *)

    \internal
*/

/*! \fn QOrderedMap::const_iterator::const_iterator(const iterator &other)

    Constructs a copy of \a other.
*/

/*! \fn const Key &QOrderedMap::const_iterator::key() const

    Returns the current item's key.

    \sa value()
*/

/*! \fn const T &QOrderedMap::const_iterator::value() const

    Returns the current item's value.

    \sa key(), operator*()
*/

/*! \fn const T &QOrderedMap::const_iterator::operator*() const

    Returns the current item's value.

    Same as value().

    \sa key()
*/

/*! \fn const T *QOrderedMap::const_iterator::operator->() const

    Returns a pointer to the current item's value.

    \sa value()
*/

/*! \fn bool QOrderedMap::const_iterator::operator==(const const_iterator &other) const

    Returns \c true if \a other points to the same item as this
    iterator; otherwise returns \c false.

    \sa operator!=()
*/

/*! \fn bool QOrderedMap::const_iterator::operator!=(const const_iterator &other) const

    Returns \c true if \a other points to a different item than this
    iterator; otherwise returns \c false.

    \sa operator==()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::const_iterator::operator++()

    The prefix ++ operator (\c{++i}) advances the iterator to the
    next item in the map and returns an iterator to the new current
    item.

    Calling this function on QOrderedMap::end() leads to undefined results.

    \sa operator--()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::const_iterator::operator++(int)

    \overload

    The postfix ++ operator (\c{i++}) advances the iterator to the
    next item in the map and returns an iterator to the previously
    current item.
*/

/*! \fn QOrderedMap::const_iterator &QOrderedMap::const_iterator::operator--()

    The prefix -- operator (\c{--i}) makes the preceding item
    current and returns an iterator pointing to the new current item.

    Calling this function on QOrderedMap::begin() leads to undefined
    results.

    \sa operator++()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::const_iterator::operator--(int)

    \overload

    The postfix -- operator (\c{i--}) makes the preceding item
    current and returns an iterator pointing to the previously
    current item.
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::const_iterator::operator+(int j) const

    Returns an iterator to the item at \a j positions forward from
    this iterator. (If \a j is negative, the iterator goes backward.)

    This operation can be slow for large \a j values.

    \sa operator-()
*/

/*! \fn QOrderedMap::const_iterator QOrderedMap::const_iterator::operator-(int j) const

    Returns an iterator to the item at \a j positions backward from
    this iterator. (If \a j is negative, the iterator goes forward.)

    This operation can be slow for large \a j values.

    \sa operator+()
*/

/*! \fn QOrderedMap::const_iterator &QOrderedMap::const_iterator::operator+=(int j)

    Advances the iterator by \a j items. (If \a j is negative, the
    iterator goes backward.)

    This operation can be slow for large \a j values.

    \sa operator-=(), operator+()
*/

/*! \fn QOrderedMap::const_iterator &QOrderedMap::const_iterator::operator-=(int j)

    Makes the iterator go back by \a j items. (If \a j is negative,
    the iterator goes forward.)

    This operation can be slow for large \a j values.

    \sa operator+=(), operator-()
*/

/*! \class QOrderedMap::key_iterator
    \inmodule QtCore
    \since 5.6
    \brief The QOrderedMap::key_iterator class provides an STL-style const iterator for QOrderedMap and QOrderedMultiMap keys.

    QOrderedMap::key_iterator is essentially the same as QOrderedMap::const_iterator
    with the difference that operator*() and operator->() return a key
    instead of a value.

    For most uses QOrderedMap::iterator and QOrderedMap::const_iterator should be used,
    you can easily access the key by calling QOrderedMap::iterator::key():

    \snippet code/src_corelib_tools_qmap.cpp keyiterator1

    However, to have interoperability between QOrderedMap's keys and STL-style
    algorithms we need an iterator that dereferences to a key instead
    of a value. With QOrderedMap::key_iterator we can apply an algorithm to a
    range of keys without having to call QOrderedMap::keys(), which is inefficient
    as it costs one QOrderedMap iteration and memory allocation to create a temporary
    QList.

    \snippet code/src_corelib_tools_qmap.cpp keyiterator2

    QOrderedMap::key_iterator is const, it's not possible to modify the key.

    The default QOrderedMap::key_iterator constructor creates an uninitialized
    iterator. You must initialize it using a QOrderedMap function like
    QOrderedMap::keyBegin() or QOrderedMap::keyEnd().

    \warning Iterators on implicitly shared containers do not work
    exactly like STL-iterators. You should avoid copying a container
    while iterators are active on that container. For more information,
    read \l{Implicit sharing iterator problem}.

    \sa QOrderedMap::const_iterator, QOrderedMap::iterator
*/

/*! \typedef QOrderedMap::key_iterator::difference_type
    \internal
*/

/*! \typedef QOrderedMap::key_iterator::iterator_category
    \internal
*/

/*! \typedef QOrderedMap::key_iterator::pointer
    \internal
*/

/*! \typedef QOrderedMap::key_iterator::reference
    \internal
*/

/*! \typedef QOrderedMap::key_iterator::value_type
    \internal
*/

/*! \fn const T &QOrderedMap::key_iterator::operator*() const

    Returns the current item's key.
*/

/*! \fn const T *QOrderedMap::key_iterator::operator->() const

    Returns a pointer to the current item's key.
*/

/*! \fn bool QOrderedMap::key_iterator::operator==(key_iterator other) const

    Returns \c true if \a other points to the same item as this
    iterator; otherwise returns \c false.

    \sa operator!=()
*/

/*! \fn bool QOrderedMap::key_iterator::operator!=(key_iterator other) const

    Returns \c true if \a other points to a different item than this
    iterator; otherwise returns \c false.

    \sa operator==()
*/

/*!
    \fn QOrderedMap::key_iterator &QOrderedMap::key_iterator::operator++()

    The prefix ++ operator (\c{++i}) advances the iterator to the
    next item in the hash and returns an iterator to the new current
    item.

    Calling this function on QOrderedMap::keyEnd() leads to undefined results.

    \sa operator--()
*/

/*! \fn QOrderedMap::key_iterator QOrderedMap::key_iterator::operator++(int)

    \overload

    The postfix ++ operator (\c{i++}) advances the iterator to the
    next item in the hash and returns an iterator to the previous
    item.
*/

/*! \fn QOrderedMap::key_iterator &QOrderedMap::key_iterator::operator--()

    The prefix -- operator (\c{--i}) makes the preceding item
    current and returns an iterator pointing to the new current item.

    Calling this function on QOrderedMap::keyBegin() leads to undefined
    results.

    \sa operator++()
*/

/*! \fn QOrderedMap::key_iterator QOrderedMap::key_iterator::operator--(int)

    \overload

    The postfix -- operator (\c{i--}) makes the preceding item
    current and returns an iterator pointing to the previous
    item.
*/

/*! \fn const_iterator QOrderedMap::key_iterator::base() const
    Returns the underlying const_iterator this key_iterator is based on.
*/

/*! \fn QDataStream &operator<<(QDataStream &out, const QOrderedMap<Key, T> &map)
    \relates QOrderedMap

    Writes the map \a map to stream \a out.

    This function requires the key and value types to implement \c
    operator<<().

    \sa{Serializing Qt Data Types}{Format of the QDataStream operators}
*/

/*! \fn QDataStream &operator>>(QDataStream &in, QOrderedMap<Key, T> &map)
    \relates QOrderedMap

    Reads a map from stream \a in into \a map.

    This function requires the key and value types to implement \c
    operator>>().

    \sa{Serializing Qt Data Types}{Format of the QDataStream operators}
*/

/*! \class QOrderedMultiMap
    \inmodule QtCore
    \brief The QOrderedMultiMap class is a convenience QOrderedMap subclass that provides multi-valued maps.

    \ingroup tools
    \ingroup shared

    \reentrant

    QOrderedMultiMap\<Key, T\> is one of Qt's generic \l{container classes}.
    It inherits QOrderedMap and extends it with a few convenience functions
    that make it more suitable than QOrderedMap for storing multi-valued
    maps. A multi-valued map is a map that allows multiple values
    with the same key; QOrderedMap normally doesn't allow that, unless you
    call QOrderedMap::insertMulti().

    Because QOrderedMultiMap inherits QOrderedMap, all of QOrderedMap's functionality also
    applies to QOrderedMultiMap. For example, you can use isEmpty() to test
    whether the map is empty, and you can traverse a QOrderedMultiMap using
    QOrderedMap's iterator classes (for example, QOrderedMapIterator). But in
    addition, it provides an insert() function that corresponds to
    QOrderedMap::insertMulti(), and a replace() function that corresponds to
    QOrderedMap::insert(). It also provides convenient operator+() and
    operator+=().

    Example:
    \snippet code/src_corelib_tools_qmap.cpp 25

    Unlike QOrderedMap, QOrderedMultiMap provides no operator[]. Use value() or
    replace() if you want to access the most recently inserted item
    with a certain key.

    If you want to retrieve all the values for a single key, you can
    use values(const Key &key), which returns a QList<T>:

    \snippet code/src_corelib_tools_qmap.cpp 26

    The items that share the same key are available from most
    recently to least recently inserted.

    If you prefer the STL-style iterators, you can call find() to get
    the iterator for the first item with a key and iterate from
    there:

    \snippet code/src_corelib_tools_qmap.cpp 27

    QOrderedMultiMap's key and value data types must be \l{assignable data
    types}. This covers most data types you are likely to encounter,
    but the compiler won't let you, for example, store a QWidget as a
    value; instead, store a QWidget *. In addition, QOrderedMultiMap's key type
    must provide operator<(). See the QOrderedMap documentation for details.

    \sa QOrderedMap, QOrderedMapIterator, QMutableMapIterator, QMultiHash
*/

/*! \fn QOrderedMultiMap::QOrderedMultiMap()

    Constructs an empty map.
*/

/*! \fn QOrderedMultiMap::QOrderedMultiMap(std::initializer_list<std::pair<Key,T> > list)
    \since 5.1

    Constructs a multi-map with a copy of each of the elements in the
    initializer list \a list.

    This function is only available if the program is being
    compiled in C++11 mode.
*/

/*! \fn QOrderedMultiMap::QOrderedMultiMap(const QOrderedMap<Key, T> &other)

    Constructs a copy of \a other (which can be a QOrderedMap or a
    QOrderedMultiMap).

    \sa operator=()
*/

/*! \fn QOrderedMultiMap::iterator QOrderedMultiMap::replace(const Key &key, const T &value)

    Inserts a new item with the key \a key and a value of \a value.

    If there is already an item with the key \a key, that item's value
    is replaced with \a value.

    If there are multiple items with the key \a key, the most
    recently inserted item's value is replaced with \a value.

    \sa insert()
*/

/*! \fn QOrderedMultiMap::iterator QOrderedMultiMap::insert(const Key &key, const T &value)

    Inserts a new item with the key \a key and a value of \a value.

    If there is already an item with the same key in the map, this
    function will simply create a new one. (This behavior is
    different from replace(), which overwrites the value of an
    existing item.)

    \sa replace()
*/

/*! \fn QOrderedMultiMap::iterator QOrderedMultiMap::insert(QOrderedMap<Key, T>::const_iterator pos, const Key &key, const T &value)

    \since 5.1
    Inserts a new item with the key \a key and value \a value and with hint \a pos
    suggesting where to do the insert.

    If constBegin() is used as hint it indicates that the \a key is less than any key in the map
    while constEnd() suggests that the \a key is larger than any key in the map.
    Otherwise the hint should meet the condition (\a pos - 1).key() < \a key <= pos.key().
    If the hint \a pos is wrong it is ignored and a regular insert is done.

    If there is already an item with the same key in the map, this function will simply create a new one.

    \b {Note:} Be careful with the hint. Providing an iterator from an older shared instance might
    crash but there is also a risk that it will silently corrupt both the map and the \a pos map.
*/

/*! \fn QOrderedMultiMap &QOrderedMultiMap::operator+=(const QOrderedMultiMap &other)

    Inserts all the items in the \a other map into this map and
    returns a reference to this map.

    \sa insert(), operator+()
*/

/*! \fn QOrderedMultiMap QOrderedMultiMap::operator+(const QOrderedMultiMap &other) const

    Returns a map that contains all the items in this map in
    addition to all the items in \a other. If a key is common to both
    maps, the resulting map will contain the key multiple times.

    \sa operator+=()
*/

/*!
    \fn bool QOrderedMultiMap::contains(const Key &key, const T &value) const
    \since 4.3

    Returns \c true if the map contains an item with key \a key and
    value \a value; otherwise returns \c false.

    \sa QOrderedMap::contains()
*/

/*!
    \fn int QOrderedMultiMap::remove(const Key &key, const T &value)
    \since 4.3

    Removes all the items that have the key \a key and the value \a
    value from the map. Returns the number of items removed.

    \sa QOrderedMap::remove()
*/

/*!
    \fn int QOrderedMultiMap::count(const Key &key, const T &value) const
    \since 4.3

    Returns the number of items with key \a key and value \a value.

    \sa QOrderedMap::count()
*/

/*!
    \fn typename QOrderedMap<Key, T>::iterator QOrderedMultiMap::find(const Key &key, const T &value)
    \since 4.3

    Returns an iterator pointing to the item with key \a key and
    value \a value in the map.

    If the map contains no such item, the function returns end().

    If the map contains multiple items with key \a key, this
    function returns an iterator that points to the most recently
    inserted value.

    \sa QOrderedMap::find()
*/

/*!
    \fn typename QOrderedMap<Key, T>::const_iterator QOrderedMultiMap::find(const Key &key, const T &value) const
    \since 4.3
    \overload

    Returns a const iterator pointing to the item with the given \a key and
    \a value in the map.

    If the map contains no such item, the function returns end().

    If the map contains multiple items with the specified \a key, this
    function returns a const iterator that points to the most recently
    inserted value.

    \sa QOrderedMap::find()
*/

/*!
    \fn typename QOrderedMap<Key, T>::const_iterator QOrderedMultiMap::constFind(const Key &key, const T &value) const
    \since 4.3

    Returns an iterator pointing to the item with key \a key and the
    value \a value in the map.

    If the map contains no such item, the function returns
    constEnd().

    \sa QOrderedMap::constFind()
*/

QT_END_NAMESPACE
