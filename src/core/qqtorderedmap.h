#ifndef QQTORDEREDMAP_H
#define QQTORDEREDMAP_H

#include <qqt-local.h>

#include <QtCore/qiterator.h>
#include <QtCore/qlist.h>
#include <QtCore/qrefcount.h>
#include <QtCore/qpair.h>

#ifdef Q_MAP_DEBUG
#include <QtCore/qdebug.h>
#endif

#include <map>
#include <new>
#include <functional>

#ifdef Q_COMPILER_INITIALIZER_LISTS
#include <initializer_list>
#endif

QT_BEGIN_NAMESPACE

/*
    QOrderedMap uses qMapLessThanKey() to compare keys. The default
    implementation uses operator<(). For pointer types,
    qMapLessThanKey() uses std::less (because operator<() on
    pointers can be used only between pointers in the same array).
*/

template <class Key> inline bool QQtMapLessThanKey ( const Key& key1, const Key& key2 )
{
    return false;//key1 < key2;
}

template <class Ptr> inline bool QQtMapLessThanKey ( const Ptr* key1, const Ptr* key2 )
{
    return false;//std::less<const Ptr*>() ( key1, key2 );
}

template <class Key, class T>
class QQTSHARED_EXPORT QOrderedMap
{
    //一个map，里面包着一个list，
    //list里面存的很多key，value对，里面都是对list进行操作。
    typedef QPair<Key, T> Node;

    //Node root; //empty ????

    QList<Node> _d; //first() ... last()
    QList<Node>* d;

    //end() empty

public:
inline QOrderedMap() Q_DECL_NOTHROW : d ( &_d ) { }
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline QOrderedMap ( std::initializer_list<std::pair<Key, T> > list )
        : d ( &_d ) {
        for ( typename std::initializer_list<std::pair<Key, T> >::const_iterator it = list.begin(); it != list.end(); ++it )
            insert ( it->first, it->second );
    }
#endif
    QOrderedMap ( const QOrderedMap<Key, T>& other );

    inline ~QOrderedMap() { }

    QOrderedMap<Key, T>& operator= ( const QOrderedMap<Key, T>& other );
#ifdef Q_COMPILER_RVALUE_REFS
    inline QOrderedMap ( QOrderedMap<Key, T>&& other ) Q_DECL_NOTHROW
: d ( other.d ) {
        other.d = 0;
    }

    inline QOrderedMap<Key, T>& operator= ( QOrderedMap<Key, T>&& other ) Q_DECL_NOTHROW
    { QOrderedMap moved ( std::move ( other ) ); swap ( moved ); return *this; }
#endif
    inline void swap ( QOrderedMap<Key, T>& other ) Q_DECL_NOTHROW { qSwap ( _d, other._d ); }
    explicit QOrderedMap ( const typename std::map<Key, T>& other );
    std::map<Key, T> toStdMap() const;

    bool operator== ( const QOrderedMap<Key, T>& other ) const;
    inline bool operator!= ( const QOrderedMap<Key, T>& other ) const { return ! ( *this == other ); }

    inline int size() const { return d->size(); }

    inline bool isEmpty() const { return d->size() == 0; }

    inline void detach() { if ( d->isDetached() ) detach_helper(); }
    inline bool isDetached() const { return !d->isDetached(); }
#if !defined(QT_NO_UNSHARABLE_CONTAINERS)
    inline void setSharable ( bool sharable ) {
        if ( sharable == d->isDetached() )
            return;
        if ( !sharable )
            detach();
        // Don't call on shared_null
        d->setSharable ( sharable );
    }
#endif
    inline bool isSharedWith ( const QOrderedMap<Key, T>& other ) const { return d == other.d; }

    void clear();

    int remove ( const Key& key );
    T take ( const Key& key );

    bool contains ( const Key& key ) const;
    const Key key ( const T& value, const Key& defaultKey = Key() ) const;
    const T value ( const Key& key, const T& defaultValue = T() ) const;
    T& operator[] ( const Key& key );
    const T operator[] ( const Key& key ) const;

    QList<Key> uniqueKeys() const;
    QList<Key> keys() const;
    QList<Key> keys ( const T& value ) const;
    QList<T> values() const;
    QList<T> values ( const Key& key ) const;
    int count ( const Key& key ) const;

    inline const Key& firstKey() const { Q_ASSERT ( !isEmpty() ); return constBegin().key(); }
    inline const Key& lastKey() const { Q_ASSERT ( !isEmpty() ); return ( constEnd() - 1 ).key(); }

    inline T& first() { Q_ASSERT ( !isEmpty() ); return *begin(); }
    inline const T& first() const { Q_ASSERT ( !isEmpty() ); return *constBegin(); }
    inline T& last() { Q_ASSERT ( !isEmpty() ); return * ( end() - 1 ); }
    inline const T& last() const { Q_ASSERT ( !isEmpty() ); return * ( constEnd() - 1 ); }

    class const_iterator;

    class iterator
    {
        friend class const_iterator;
        Node* i;
        QList<Node>* d;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef qptrdiff difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        inline iterator() : i ( Q_NULLPTR ), d ( Q_NULLPTR ) { }
        inline iterator ( Node* an, QList<Node>* ad ) : i ( an ), d ( ad ) {}

        inline const Key& key() const { return i->first; }
        inline T& value() const { return i->second; }
        inline T& operator*() const { return i->second; }
        inline T* operator->() const { return &i->second; }
        inline bool operator== ( const iterator& o ) const { return i == o.i; }
        inline bool operator!= ( const iterator& o ) const { return i != o.i; }

        inline iterator& operator++() {

            for ( typename QList<Node>::Iterator itor = d->begin();
                  itor != d->end(); itor++ ) {
                Node* n = &*itor;
                if ( n == i ) {
                    i = &* ( ++itor );
                    break;
                }
            }

            return *this;
        }
        inline iterator operator++ ( int ) {
            iterator r = *this;

            for ( typename QList<Node>::Iterator itor = d->begin();
                  itor != d->end(); itor++ ) {
                Node* n = &*itor;
                if ( n == i ) {
                    i = &* ( ++itor );
                    break;
                }
            }

            return r;
        }
        inline iterator& operator--() {

            for ( typename QList<Node>::ConstIterator itor = d->constBegin();
                  itor <= d->constEnd(); itor++ ) {
                Node* n = &*itor;
                if ( n == i ) {
                    i = &* ( --itor );
                    break;
                }
            }

            return *this;
        }
        inline iterator operator-- ( int ) {
            iterator r = *this;

            for ( typename QList<Node>::ConstIterator itor = d->constBegin();
                  itor <= d->constEnd(); itor++ ) {
                Node* n = &*itor;
                if ( n == i ) {
                    i = &* ( --itor );
                    break;
                }
            }

            return r;
        }
        inline iterator operator+ ( int j ) const
        { iterator r = *this; if ( j > 0 ) while ( j-- ) ++r; else while ( j++ ) --r; return r; }
        inline iterator operator- ( int j ) const { return operator+ ( -j ); }
        inline iterator& operator+= ( int j ) { return *this = *this + j; }
        inline iterator& operator-= ( int j ) { return *this = *this - j; }

#ifndef QT_STRICT_ITERATORS
    public:
        inline bool operator== ( const const_iterator& o ) const
        { return i == o.i; }
        inline bool operator!= ( const const_iterator& o ) const
        { return i != o.i; }
#endif
        friend class QOrderedMap<Key, T>;
    };
    friend class iterator;

    class const_iterator
    {
        friend class iterator;
        const QList<Node>* d;
        const Node* i;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef qptrdiff difference_type;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;

        Q_DECL_CONSTEXPR inline const_iterator() : i ( Q_NULLPTR ), d ( Q_NULLPTR ) { }
        inline const_iterator ( const Node* node, const QList<Node>* ad ) : i ( node ), d ( ad ) { }
#ifdef QT_STRICT_ITERATORS
        explicit inline const_iterator ( const iterator& o )
#else
        inline const_iterator ( const iterator& o )
#endif
        { i = o.i; d = o.d; }

        inline const Key& key() const { return i->first; }
        inline const T& value() const { return i->second; }
        inline const T& operator*() const { return i->second; }
        inline const T* operator->() const { return &i->second; }
        Q_DECL_CONSTEXPR inline bool operator== ( const const_iterator& o ) const { return i == o.i; }
        Q_DECL_CONSTEXPR inline bool operator!= ( const const_iterator& o ) const { return i != o.i; }

        inline const_iterator& operator++() {

            for ( typename QList<Node>::ConstIterator itor = d->constBegin();
                  itor != d->constEnd(); itor++ ) {
                const Node* n = &*itor;
                if ( n == i ) {
                    i = &* ( ++itor );
                    break;
                }
            }

            return *this;
        }
        inline const_iterator operator++ ( int ) {
            const_iterator r = *this;

            for ( typename QList<Node>::ConstIterator itor = d->constBegin();
                  itor != d->constEnd(); itor++ ) {
                const Node* n = &*itor;
                if ( i == n ) {
                    i = &* ( ++itor );
                    break;
                }
            }

            return r;
        }
        inline const_iterator& operator--() {

            for ( typename QList<Node>::ConstIterator itor = d->constBegin();
                  itor <= d->constEnd(); itor++ ) {
                const Node* n = &*itor;
                if ( i == n ) {
                    i = &* ( --itor );
                    break;
                }
            }

            return *this;
        }
        inline const_iterator operator-- ( int ) {
            const_iterator r = *this;

            for ( typename QList<Node>::ConstIterator itor = d->constBegin();
                  itor <= d->constEnd(); itor++ ) {
                const Node* n = &*itor;
                if ( i == n ) {
                    i = &* ( --itor );
                    break;
                }
            }

            return r;
        }
        inline const_iterator operator+ ( int j ) const
        { const_iterator r = *this; if ( j > 0 ) while ( j-- ) ++r; else while ( j++ ) --r; return r; }
        inline const_iterator operator- ( int j ) const { return operator+ ( -j ); }
        inline const_iterator& operator+= ( int j ) { return *this = *this + j; }
        inline const_iterator& operator-= ( int j ) { return *this = *this - j; }

#ifdef QT_STRICT_ITERATORS
    private:
        inline bool operator== ( const iterator& o ) const { return operator== ( const_iterator ( o ) ); }
        inline bool operator!= ( const iterator& o ) const { return operator!= ( const_iterator ( o ) ); }
#endif
        friend class QOrderedMap<Key, T>;
    };
    friend class const_iterator;

    //need some test
    class key_iterator
    {
        const_iterator i;

    public:
        typedef typename const_iterator::iterator_category iterator_category;
        typedef typename const_iterator::difference_type difference_type;
        typedef Key value_type;
        typedef const Key* pointer;
        typedef const Key& reference;

        key_iterator() = default;
        explicit key_iterator ( const_iterator o ) : i ( o ) { }

        const Key& operator*() const { return i.key(); }
        const Key* operator->() const { return &i.key(); }
        bool operator== ( key_iterator o ) const { return i == o.i; }
        bool operator!= ( key_iterator o ) const { return i != o.i; }

        inline key_iterator& operator++() { ++i; return *this; }
        inline key_iterator operator++ ( int ) { return key_iterator ( i++ );}
        inline key_iterator& operator--() { --i; return *this; }
        inline key_iterator operator-- ( int ) { return key_iterator ( i-- ); }
        const_iterator base() const { return i; }
    };


    // STL style
    inline iterator begin() {
        detach();
        typename QList<Node>::Iterator itor = d->begin();
        Node* n = &*itor;
        return iterator ( n, d );
    }
    inline const_iterator begin() const {
        typename QList<Node>::Iterator itor = d->begin();
        const Node* n = &*itor;
        return const_iterator ( n, d );
    }
    inline const_iterator constBegin() const {
        typename QList<Node>::ConstIterator itor = d->constBegin();
        const Node* n = &*itor;
        return const_iterator ( n, d );
    }
    inline const_iterator cbegin() const { return const_iterator ( d->begin() ); }
    inline iterator end() {
        detach();
        typename QList<Node>::Iterator itor = d->end();
        Node* n = &*itor;
        return iterator ( n, d );
    }
    inline const_iterator end() const {
        typename QList<Node>::Iterator itor = d->end();
        const Node* n = &*itor;
        return const_iterator ( n, d );
    }
    inline const_iterator constEnd() const {
        typename QList<Node>::ConstIterator itor = d->constEnd();
        const Node* n = &*itor;
        return const_iterator ( n, d );
    }
    inline const_iterator cend() const { return const_iterator ( d->end() ); }
    inline key_iterator keyBegin() const { return key_iterator ( begin() ); }
    inline key_iterator keyEnd() const { return key_iterator ( end() ); }
    iterator erase ( iterator it );

    // more Qt
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    inline int count() const { return d->size(); }
    iterator find ( const Key& key );
    const_iterator find ( const Key& key ) const;
    const_iterator constFind ( const Key& key ) const;
    iterator lowerBound ( const Key& key );
    const_iterator lowerBound ( const Key& key ) const;
    iterator upperBound ( const Key& key );
    const_iterator upperBound ( const Key& key ) const;
    iterator insert ( const Key& key, const T& value );
    iterator insert ( const_iterator pos, const Key& key, const T& value );
    iterator insertMulti ( const Key& key, const T& value );
    iterator insertMulti ( const_iterator pos, const Key& akey, const T& avalue );
    QOrderedMap<Key, T>& unite ( const QOrderedMap<Key, T>& other );

    // STL compatibility
    typedef Key key_type;
    typedef T mapped_type;
    typedef qptrdiff difference_type;
    typedef int size_type;
    inline bool empty() const { return isEmpty(); }
    QPair<iterator, iterator> equal_range ( const Key& akey );
    QPair<const_iterator, const_iterator> equal_range ( const Key& akey ) const;

#ifdef Q_MAP_DEBUG
    void dump() const;
#endif

private:
    void detach_helper();
    bool isValidIterator ( const const_iterator& ci ) const {
#if defined(QT_DEBUG) && !defined(Q_MAP_NO_ITERATOR_DEBUG)
        typename QList<Node>::ConstIterator n = ci;
        return n >= d->begin() && n <= d->end();
#else
        Q_UNUSED ( ci );
        return true;
#endif
    }
};

template <class Key, class T>
inline QOrderedMap<Key, T>::QOrderedMap ( const QOrderedMap<Key, T>& other )
{
    _d = other._d;
    d = &_d;
}

template <class Key, class T>
Q_INLINE_TEMPLATE QOrderedMap<Key, T>& QOrderedMap<Key, T>::operator= ( const QOrderedMap<Key, T>& other )
{
    if ( _d != other._d )
    {
        QOrderedMap<Key, T> tmp ( other );
        tmp.swap ( *this );
    }
    return *this;
}

template <class Key, class T>
Q_INLINE_TEMPLATE void QOrderedMap<Key, T>::clear()
{
    *this = QOrderedMap<Key, T>();
}

QT_WARNING_PUSH
QT_WARNING_DISABLE_CLANG ( "-Wreturn-stack-address" )

template <class Key, class T>
Q_INLINE_TEMPLATE const T QOrderedMap<Key, T>::value ( const Key& akey, const T& adefaultValue ) const
{
    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n = &*itor;
        if ( n->first == akey )
        {
            return n->second;
        }
    }
    return adefaultValue;
}

QT_WARNING_POP

template <class Key, class T>
Q_INLINE_TEMPLATE const T QOrderedMap<Key, T>::operator[] ( const Key& akey ) const
{
    return value ( akey );
}

template <class Key, class T>
Q_INLINE_TEMPLATE T& QOrderedMap<Key, T>::operator[] ( const Key& akey )
{
    detach();
    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n = &*itor;
        if ( n->first == akey )
        {
            return n->second;
        }
    }
    return *insert ( akey, T() );
}

template <class Key, class T>
Q_INLINE_TEMPLATE int QOrderedMap<Key, T>::count ( const Key& akey ) const
{
    int cnt = 0;
    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n = &*itor;
        if ( n->first == akey )
            cnt++;
    }
    return cnt;
}

template <class Key, class T>
Q_INLINE_TEMPLATE bool QOrderedMap<Key, T>::contains ( const Key& akey ) const
{
    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n = &*itor;
        if ( n->first == akey )
            return true;
    }
    return false;
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QOrderedMap<Key, T>::iterator QOrderedMap<Key, T>::insert ( const Key& akey,
        const T& avalue )
{
    detach();

    Node n;
    n.first = akey;
    n.second = avalue;

    for ( int i = 0 ; i < d->size(); i++ )
    {
        Node* n_now = &d->operator [] ( i );
        if ( n_now->first == akey )
        {
            *n_now = n;
            return iterator ( n_now, d );
        }
    }

    d->push_back ( n );
    Node* z = &d->last();

    return iterator ( z, d );
}

//need more test
template <class Key, class T>
typename QOrderedMap<Key, T>::iterator QOrderedMap<Key, T>::insert ( const_iterator pos, const Key& akey,
                                                                     const T& avalue )
{
    detach();

    Node n;
    n.first = akey;
    n.second = avalue;

    for ( int i = 0 ; i < d->size(); i++ )
    {
        Node* n_now = &d->operator [] ( i );
        if ( n_now->first == akey )
        {
            *n_now = n;
            return iterator ( n_now, d );
        }
    }

    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n_before = itor;
        const_iterator p ( n_before, d );
        if ( p == pos )
        {
            typename QList<Node>::Iterator i = d->insert ( itor, n );
            Node* cur = &*i;
            return iterator ( cur, d );
        }
    }

    d->push_back ( n );
    Node* z = &d->last();
    return iterator ( z, d );
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QOrderedMap<Key, T>::iterator QOrderedMap<Key, T>::insertMulti ( const Key& akey,
        const T& avalue )
{
    detach();
#if 0
    Node n;
    n.first = akey;
    n.second = avalue;
    d->push_back ( n );

    Node* z = d->last();
    return iterator ( z );
#endif
    return insert ( akey, avalue );
}

//need more test
template <class Key, class T>
typename QOrderedMap<Key, T>::iterator QOrderedMap<Key, T>::insertMulti ( const_iterator pos, const Key& akey,
                                                                          const T& avalue )
{
    Node n;
    n.first = akey;
    n.second = avalue;

    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n_before = &*itor;
        const_iterator p ( n_before );
        if ( p == pos )
        {
            typename QList<Node>::Iterator i = d->insert ( itor, n );
            Node* n_now = &*i;
            return iterator ( n_now, d );
        }
    }
    d->push_back ( n );
    Node* n_now = &d->last();
    return iterator ( n_now, d );
}


template <class Key, class T>
Q_INLINE_TEMPLATE typename QOrderedMap<Key, T>::const_iterator QOrderedMap<Key, T>::constFind (
    const Key& akey ) const
{
    for ( typename QList<Node>::ConstIterator itor = d->constBegin();
          itor != d->constEnd(); itor++ )
    {
        Node* n = &*itor;
        if ( n->first == akey )
        {
            return const_iterator ( n, d );
        }
    }

    return constEnd();
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QOrderedMap<Key, T>::const_iterator QOrderedMap<Key, T>::find ( const Key& akey ) const
{
    return constFind ( akey );
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QOrderedMap<Key, T>::iterator QOrderedMap<Key, T>::find ( const Key& akey )
{
    detach();
    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n = &*itor;
        if ( n->first == akey )
        {
            return iterator ( n, d );
        }
    }

    return end();
}

//need
template <class Key, class T>
Q_INLINE_TEMPLATE QOrderedMap<Key, T>& QOrderedMap<Key, T>::unite ( const QOrderedMap<Key, T>& other )
{
    QOrderedMap<Key, T> copy ( other );
    const_iterator it = copy.constEnd();
    const const_iterator b = copy.constBegin();
    while ( it != b )
    {
        --it;
        insertMulti ( it.key(), it.value() );
    }
    return *this;
}

//need
template <class Key, class T>
QPair<typename QOrderedMap<Key, T>::iterator, typename QOrderedMap<Key, T>::iterator>
QOrderedMap<Key, T>::equal_range ( const Key& akey )
{
    detach();
    Node* firstNode, *lastNode;
    //d->nodeRange ( akey, &firstNode, &lastNode );
    //return QPair<iterator, iterator> ( iterator ( firstNode ), iterator ( lastNode ) );
}

template <class Key, class T>
QPair<typename QOrderedMap<Key, T>::const_iterator, typename QOrderedMap<Key, T>::const_iterator>
QOrderedMap<Key, T>::equal_range ( const Key& akey ) const
{
    Node* firstNode, *lastNode;
    //d->nodeRange ( akey, &firstNode, &lastNode );
    //return qMakePair ( const_iterator ( firstNode ), const_iterator ( lastNode ) );
}

#ifdef Q_MAP_DEBUG
template <class Key, class T>
void QOrderedMap<Key, T>::dump() const
{
    for ( typename QList<Node>::ConstIterator itor = d->constBegin();
          itor != d->constEnd(); itor++ )
    {
        const Node* n = &*itor;
        qDebug() << n->first << n->second;
    }
}
#endif

//找到key，再处理，不能直接处理list。
template <class Key, class T>
Q_OUTOFLINE_TEMPLATE int QOrderedMap<Key, T>::remove ( const Key& akey )
{
    detach();

    typename QList<Node>::Iterator p = d->end();

    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n = &*itor;
        if ( n->first == akey )
        {
            p = itor;
            break;
        }
    }

    Node* n = &*p;
    int cnt = d->removeAll ( *n );

    return cnt;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE T QOrderedMap<Key, T>::take ( const Key& akey )
{
    detach();

    typename QList<Node>::Iterator p = d->end();

    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* n = &*itor;
        if ( n->first == akey )
        {
            p = itor;
            break;
        }
    }

    if ( p == d->end() )
        return T();

    Node* n = &*p;
    T v = n->second;
    d->removeAll ( *n );

    return v;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE typename QOrderedMap<Key, T>::iterator QOrderedMap<Key, T>::erase ( iterator it )
{
    if ( it == iterator ( d->end(), d ) )
        return it;

    Node* n = &*it;
    ++it;
    d->removeAll ( n );
    return it;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE void QOrderedMap<Key, T>::detach_helper()
{
    d->detach();
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QOrderedMap<Key, T>::uniqueKeys() const
{
    QList<Key> res;
    for ( typename QList<Node>::Iterator itor = d->begin();
          itor != d->end(); itor++ )
    {
        Node* node = &*itor;
        const Key& key = node->first;
        if ( res.contains ( key ) )
            continue;
        res.push_back ( key );
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QOrderedMap<Key, T>::keys() const
{
    QList<Key> res;

    const_iterator i = begin();
    while ( i != end() )
    {
        res.push_back ( i.key() );
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QOrderedMap<Key, T>::keys ( const T& avalue ) const
{
    QList<Key> res;

    const_iterator i = begin();
    while ( i != end() )
    {
        if ( i.value() == avalue )
            res.push_back ( i.key() );
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE const Key QOrderedMap<Key, T>::key ( const T& avalue, const Key& defaultKey ) const
{
    const_iterator i = begin();
    while ( i != end() )
    {
        if ( i.value() == avalue )
            return i.key();
        ++i;
    }

    return defaultKey;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<T> QOrderedMap<Key, T>::values() const
{
    QList<T> res;

    const_iterator i = begin();
    while ( i != end() )
    {
        res.push_back ( i.value() );
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<T> QOrderedMap<Key, T>::values ( const Key& akey ) const
{
    QList<T> res;

    const_iterator i = begin();
    while ( i != end() )
    {
        if ( i.key() == akey )
            res.push_back ( i.value() );
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE bool QOrderedMap<Key, T>::operator== ( const QOrderedMap<Key, T>& other ) const
{
    if ( size() != other.size() )
        return false;

    if ( _d != other._d )
        return false;

    return true;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QOrderedMap<Key, T>::QOrderedMap ( const std::map<Key, T>& other )
{
    d->clear();
    typename std::map<Key, T>::const_iterator it = other.begin();
    while ( it != other.end() )
    {
        Node node;
        node.first = ( *it ).first;
        node.second = ( *it ).second;
        d->push_back ( node );
        ++it;
    }
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE std::map<Key, T> QOrderedMap<Key, T>::toStdMap() const
{
    std::map<Key, T> amap;

    const_iterator it = begin();
    while ( it != end() )
    {
        amap.insert ( amap.end(), std::pair<Key, T> ( it.key(), it.value() ) );
        ++it;
    }
    return amap;
}

template <class Key, class T>
class QQTSHARED_EXPORT QOrderedMultiMap : public QOrderedMap<Key, T>
{
public:
    QOrderedMultiMap() Q_DECL_NOTHROW {}
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline QOrderedMultiMap ( std::initializer_list<std::pair<Key, T> > list ) {
        for ( typename std::initializer_list<std::pair<Key, T> >::const_iterator it = list.begin(); it != list.end(); ++it )
            insert ( it->first, it->second );
    }
#endif
    QOrderedMultiMap ( const QOrderedMap<Key, T>& other ) : QOrderedMap<Key, T> ( other ) {}
#ifdef Q_COMPILER_RVALUE_REFS
QOrderedMultiMap ( QOrderedMap<Key, T>&& other ) Q_DECL_NOTHROW : QOrderedMap<Key, T> ( std::move ( other ) ) {}
#endif
    void swap ( QOrderedMultiMap<Key, T>& other ) Q_DECL_NOTHROW { QOrderedMap<Key, T>::swap ( other ); }

    inline typename QOrderedMap<Key, T>::iterator replace ( const Key& key, const T& value )
    { return QOrderedMap<Key, T>::insert ( key, value ); }
    inline typename QOrderedMap<Key, T>::iterator insert ( const Key& key, const T& value )
    { return QOrderedMap<Key, T>::insertMulti ( key, value ); }
    inline typename QOrderedMap<Key, T>::iterator insert ( typename QOrderedMap<Key, T>::const_iterator pos,
                                                           const Key& key,
                                                           const T& value )
    { return QOrderedMap<Key, T>::insertMulti ( pos, key, value ); }

    inline QOrderedMultiMap& operator+= ( const QOrderedMultiMap& other )
    { this->unite ( other ); return *this; }
    inline QOrderedMultiMap operator+ ( const QOrderedMultiMap& other ) const
    { QOrderedMultiMap result = *this; result += other; return result; }

    using QOrderedMap<Key, T>::contains;
    using QOrderedMap<Key, T>::remove;
    using QOrderedMap<Key, T>::count;
    using QOrderedMap<Key, T>::find;
    using QOrderedMap<Key, T>::constFind;

    bool contains ( const Key& key, const T& value ) const;

    int remove ( const Key& key, const T& value );

    int count ( const Key& key, const T& value ) const;

    typename QOrderedMap<Key, T>::iterator find ( const Key& key, const T& value ) {
        typename QOrderedMap<Key, T>::iterator i ( find ( key ) );
        typename QOrderedMap<Key, T>::iterator end ( this->end() );
        while ( i != end && !QQtMapLessThanKey<Key> ( key, i.key() ) ) {
            if ( i.value() == value )
                return i;
            ++i;
        }
        return end;
    }
    typename QOrderedMap<Key, T>::const_iterator find ( const Key& key, const T& value ) const {
        typename QOrderedMap<Key, T>::const_iterator i ( constFind ( key ) );
        typename QOrderedMap<Key, T>::const_iterator end ( QOrderedMap<Key, T>::constEnd() );
        while ( i != end && !QQtMapLessThanKey<Key> ( key, i.key() ) ) {
            if ( i.value() == value )
                return i;
            ++i;
        }
        return end;
    }
    typename QOrderedMap<Key, T>::const_iterator constFind ( const Key& key, const T& value ) const
    { return find ( key, value ); }
private:
    T& operator[] ( const Key& key );
    const T operator[] ( const Key& key ) const;
};

template <class Key, class T>
Q_INLINE_TEMPLATE bool QOrderedMultiMap<Key, T>::contains ( const Key& key, const T& value ) const
{
    return constFind ( key, value ) != QOrderedMap<Key, T>::constEnd();
}

template <class Key, class T>
Q_INLINE_TEMPLATE int QOrderedMultiMap<Key, T>::remove ( const Key& key, const T& value )
{
    int n = 0;
    typename QOrderedMap<Key, T>::iterator i ( find ( key ) );
    typename QOrderedMap<Key, T>::iterator end ( QOrderedMap<Key, T>::end() );
    while ( i != end && !QQtMapLessThanKey<Key> ( key, i.key() ) )
    {
        if ( i.value() == value )
        {
            i = this->erase ( i );
            ++n;
        }
        else
        {
            ++i;
        }
    }
    return n;
}

template <class Key, class T>
Q_INLINE_TEMPLATE int QOrderedMultiMap<Key, T>::count ( const Key& key, const T& value ) const
{
    int n = 0;
    typename QOrderedMap<Key, T>::const_iterator i ( constFind ( key ) );
    typename QOrderedMap<Key, T>::const_iterator end ( QOrderedMap<Key, T>::constEnd() );
    while ( i != end && !QQtMapLessThanKey<Key> ( key, i.key() ) )
    {
        if ( i.value() == value )
            ++n;
        ++i;
    }
    return n;
}

Q_DECLARE_ASSOCIATIVE_ITERATOR ( OrderedMap )
Q_DECLARE_MUTABLE_ASSOCIATIVE_ITERATOR ( OrderedMap )

QT_END_NAMESPACE

#endif // QQTORDEREDMAP_H
