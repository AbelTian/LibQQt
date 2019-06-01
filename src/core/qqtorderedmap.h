#ifndef QQTORDEREDMAP_H
#define QQTORDEREDMAP_H

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

#include <qqt-local.h>

/*
    QQtOrderedMap uses QQtOrderedMapLessThanKey() to compare keys. The default
    implementation uses operator<(). For pointer types,
    QQtOrderedMapLessThanKey() uses std::less (because operator<() on
    pointers can be used only between pointers in the same array).
*/

template <class Key> inline bool QQtOrderedMapLessThanKey ( const Key& key1, const Key& key2 )
{
    return true;
}

template <class Ptr> inline bool QQtOrderedMapLessThanKey ( const Ptr* key1, const Ptr* key2 )
{
    return true;
}

struct QQtOrderedMapDataBase;
template <class Key, class T> struct QQtOrderedMapData;

struct QQTSHARED_EXPORT QQtOrderedMapNodeBase
{
    quintptr p;
    QQtOrderedMapNodeBase* left;
    QQtOrderedMapNodeBase* right;

    enum Color { Red = 0, Black = 1 };
    enum { Mask = 3 }; // reserve the second bit as well

    const QQtOrderedMapNodeBase* nextNode() const;
    QQtOrderedMapNodeBase* nextNode() { return const_cast<QQtOrderedMapNodeBase*> ( const_cast<const QQtOrderedMapNodeBase*> ( this )->nextNode() ); }
    const QQtOrderedMapNodeBase* previousNode() const;
    QQtOrderedMapNodeBase* previousNode() { return const_cast<QQtOrderedMapNodeBase*> ( const_cast<const QQtOrderedMapNodeBase*> ( this )->previousNode() ); }

    Color color() const { return Color ( p & 1 ); }
    void setColor ( Color c ) { if ( c == Black ) p |= Black; else p &= ~Black; }
    QQtOrderedMapNodeBase* parent() const { return reinterpret_cast<QQtOrderedMapNodeBase*> ( p & ~Mask ); }
    void setParent ( QQtOrderedMapNodeBase* pp ) { p = ( p & Mask ) | quintptr ( pp ); }

    template <typename T>
    static typename std::enable_if<QTypeInfo<T>::isComplex>::type
    callDestructorIfNecessary ( T& t ) Q_DECL_NOTHROW { Q_UNUSED ( t ); t.~T(); } // Q_UNUSED: silence MSVC unused 't' warning
    template <typename T>
    static typename std::enable_if < !QTypeInfo<T>::isComplex >::type
    callDestructorIfNecessary ( T& ) Q_DECL_NOTHROW {}
};

template <class Key, class T>
struct QQtOrderedMapNode : public QQtOrderedMapNodeBase
{
    Key key;
    T value;

    inline QQtOrderedMapNode* leftNode() const { return static_cast<QQtOrderedMapNode*> ( left ); }
    inline QQtOrderedMapNode* rightNode() const { return static_cast<QQtOrderedMapNode*> ( right ); }

    inline const QQtOrderedMapNode* nextNode() const { return static_cast<const QQtOrderedMapNode*> ( QQtOrderedMapNodeBase::nextNode() ); }
    inline const QQtOrderedMapNode* previousNode() const { return static_cast<const QQtOrderedMapNode*> ( QQtOrderedMapNodeBase::previousNode() ); }
    inline QQtOrderedMapNode* nextNode() { return static_cast<QQtOrderedMapNode*> ( QQtOrderedMapNodeBase::nextNode() ); }
    inline QQtOrderedMapNode* previousNode() { return static_cast<QQtOrderedMapNode*> ( QQtOrderedMapNodeBase::previousNode() ); }

    QQtOrderedMapNode<Key, T>* copy ( QQtOrderedMapData<Key, T>* d ) const;

    void destroySubTree() {
        callDestructorIfNecessary ( key );
        callDestructorIfNecessary ( value );
        doDestroySubTree ( std::integral_constant < bool, QTypeInfo<T>::isComplex || QTypeInfo<Key>::isComplex > () );
    }

    QQtOrderedMapNode<Key, T>* lowerBound ( const Key& key );
    QQtOrderedMapNode<Key, T>* upperBound ( const Key& key );

private:
    void doDestroySubTree ( std::false_type ) {}
    void doDestroySubTree ( std::true_type ) {
        if ( left )
            leftNode()->destroySubTree();
        if ( right )
            rightNode()->destroySubTree();
    }

    QQtOrderedMapNode() Q_DECL_EQ_DELETE;
    Q_DISABLE_COPY ( QQtOrderedMapNode )
};

template <class Key, class T>
inline QQtOrderedMapNode<Key, T>* QQtOrderedMapNode<Key, T>::lowerBound ( const Key& akey )
{
    QQtOrderedMapNode<Key, T>* n = this;
    QQtOrderedMapNode<Key, T>* lastNode = Q_NULLPTR;
    while ( n )
    {
        if ( !QQtOrderedMapLessThanKey ( n->key, akey ) )
        {
            lastNode = n;
            n = n->leftNode();
        }
        else
        {
            n = n->rightNode();
        }
    }
    return lastNode;
}

template <class Key, class T>
inline QQtOrderedMapNode<Key, T>* QQtOrderedMapNode<Key, T>::upperBound ( const Key& akey )
{
    QQtOrderedMapNode<Key, T>* n = this;
    QQtOrderedMapNode<Key, T>* lastNode = Q_NULLPTR;
    while ( n )
    {
        if ( QQtOrderedMapLessThanKey ( akey, n->key ) )
        {
            lastNode = n;
            n = n->leftNode();
        }
        else
        {
            n = n->rightNode();
        }
    }
    return lastNode;
}



struct QQTSHARED_EXPORT QQtOrderedMapDataBase
{
    QtPrivate::RefCount ref;
    int size;
    QQtOrderedMapNodeBase header;
    QQtOrderedMapNodeBase* mostLeftNode;

    void rotateLeft ( QQtOrderedMapNodeBase* x );
    void rotateRight ( QQtOrderedMapNodeBase* x );
    void rebalance ( QQtOrderedMapNodeBase* x );
    void freeNodeAndRebalance ( QQtOrderedMapNodeBase* z );
    void recalcMostLeftNode();

    QQtOrderedMapNodeBase* createNode ( int size, int alignment, QQtOrderedMapNodeBase* parent, bool left );
    void freeTree ( QQtOrderedMapNodeBase* root, int alignment );

    static const QQtOrderedMapDataBase shared_null;

    static QQtOrderedMapDataBase* createData();
    static void freeData ( QQtOrderedMapDataBase* d );
};

template <class Key, class T>
struct QQtOrderedMapData : public QQtOrderedMapDataBase
{
    typedef QQtOrderedMapNode<Key, T> Node;

    Node* root() const { return static_cast<Node*> ( header.left ); }

    // using reinterpret_cast because QQtOrderedMapDataBase::header is not
    // actually a QQtOrderedMapNode.
    const Node* end() const { return reinterpret_cast<const Node*> ( &header ); }
    Node* end() { return reinterpret_cast<Node*> ( &header ); }
    const Node* begin() const { if ( root() ) return static_cast<const Node*> ( mostLeftNode ); return end(); }
    Node* begin() { if ( root() ) return static_cast<Node*> ( mostLeftNode ); return end(); }

    void deleteNode ( Node* z );
    Node* findNode ( const Key& akey ) const;
    void nodeRange ( const Key& akey, Node** firstNode, Node** lastNode );

    Node* createNode ( const Key& k, const T& v, Node* parent = Q_NULLPTR, bool left = false ) {
        Node* n = static_cast<Node*> ( QQtOrderedMapDataBase::createNode ( sizeof ( Node ), Q_ALIGNOF ( Node ),
                                                                           parent, left ) );
        QT_TRY
        {
            new ( &n->key ) Key ( k );
            QT_TRY {
                new ( &n->value ) T ( v );
            } QT_CATCH ( ... ) {
                n->key.~Key();
                QT_RETHROW;
            }
        } QT_CATCH ( ... ) {
            QQtOrderedMapDataBase::freeNodeAndRebalance ( n );
            QT_RETHROW;
        }
        return n;
    }

    static QQtOrderedMapData* create() {
        return static_cast<QQtOrderedMapData*> ( createData() );
    }

    void destroy() {
        if ( root() ) {
            root()->destroySubTree();
            freeTree ( header.left, Q_ALIGNOF ( Node ) );
        }
        freeData ( this );
    }
};

template <class Key, class T>
QQtOrderedMapNode<Key, T>* QQtOrderedMapNode<Key, T>::copy ( QQtOrderedMapData<Key, T>* d ) const
{
    QQtOrderedMapNode<Key, T>* n = d->createNode ( key, value );
    n->setColor ( color() );
    if ( left )
    {
        n->left = leftNode()->copy ( d );
        n->left->setParent ( n );
    }
    else
    {
        n->left = Q_NULLPTR;
    }
    if ( right )
    {
        n->right = rightNode()->copy ( d );
        n->right->setParent ( n );
    }
    else
    {
        n->right = Q_NULLPTR;
    }
    return n;
}

template <class Key, class T>
void QQtOrderedMapData<Key, T>::deleteNode ( QQtOrderedMapNode<Key, T>* z )
{
    QQtOrderedMapNodeBase::callDestructorIfNecessary ( z->key );
    QQtOrderedMapNodeBase::callDestructorIfNecessary ( z->value );
    freeNodeAndRebalance ( z );
}

template <class Key, class T>
QQtOrderedMapNode<Key, T>* QQtOrderedMapData<Key, T>::findNode ( const Key& akey ) const
{
    if ( Node* r = root() )
    {
        Node* lb = r->lowerBound ( akey );
        if ( lb && !QQtOrderedMapLessThanKey ( akey, lb->key ) )
            return lb;
    }
    return Q_NULLPTR;
}


template <class Key, class T>
void QQtOrderedMapData<Key, T>::nodeRange ( const Key& akey, QQtOrderedMapNode<Key, T>** firstNode, QQtOrderedMapNode<Key, T>** lastNode )
{
    Node* n = root();
    Node* l = end();
    while ( n )
    {
        if ( QQtOrderedMapLessThanKey ( akey, n->key ) )
        {
            l = n;
            n = n->leftNode();
        }
        else if ( QQtOrderedMapLessThanKey ( n->key, akey ) )
        {
            n = n->rightNode();
        }
        else
        {
            *firstNode = n->leftNode() ? n->leftNode()->lowerBound ( akey ) : Q_NULLPTR;
            if ( !*firstNode )
                *firstNode = n;
            *lastNode = n->rightNode() ? n->rightNode()->upperBound ( akey ) : Q_NULLPTR;
            if ( !*lastNode )
                *lastNode = l;
            return;
        }
    }
    *firstNode = *lastNode = l;
}


template <class Key, class T>
class QQtOrderedMap
{
    typedef QQtOrderedMapNode<Key, T> Node;

    QQtOrderedMapData<Key, T>* d;

public:
inline QQtOrderedMap() Q_DECL_NOTHROW : d ( static_cast<QQtOrderedMapData<Key, T> *> ( const_cast<QQtOrderedMapDataBase*> ( &QQtOrderedMapDataBase::shared_null ) ) ) { }
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline QQtOrderedMap ( std::initializer_list<std::pair<Key, T> > list )
        : d ( static_cast<QQtOrderedMapData<Key, T> *> ( const_cast<QQtOrderedMapDataBase*> ( &QQtOrderedMapDataBase::shared_null ) ) ) {
        for ( typename std::initializer_list<std::pair<Key, T> >::const_iterator it = list.begin(); it != list.end(); ++it )
            insert ( it->first, it->second );
    }
#endif
    QQtOrderedMap ( const QQtOrderedMap<Key, T>& other );

    inline ~QQtOrderedMap() { if ( !d->ref.deref() ) d->destroy(); }

    QQtOrderedMap<Key, T>& operator= ( const QQtOrderedMap<Key, T>& other );
#ifdef Q_COMPILER_RVALUE_REFS
    inline QQtOrderedMap ( QQtOrderedMap<Key, T>&& other ) Q_DECL_NOTHROW
: d ( other.d ) {
        other.d = static_cast<QQtOrderedMapData<Key, T> *> (
                      const_cast<QQtOrderedMapDataBase*> ( &QQtOrderedMapDataBase::shared_null ) );
    }

    inline QQtOrderedMap<Key, T>& operator= ( QQtOrderedMap<Key, T>&& other ) Q_DECL_NOTHROW
    { QQtOrderedMap moved ( std::move ( other ) ); swap ( moved ); return *this; }
#endif
    inline void swap ( QQtOrderedMap<Key, T>& other ) Q_DECL_NOTHROW { qSwap ( d, other.d ); }
    explicit QQtOrderedMap ( const typename std::map<Key, T>& other );
    std::map<Key, T> toStdMap() const;

    bool operator== ( const QQtOrderedMap<Key, T>& other ) const;
    inline bool operator!= ( const QQtOrderedMap<Key, T>& other ) const { return ! ( *this == other ); }

    inline int size() const { return d->size; }

    inline bool isEmpty() const { return d->size == 0; }

    inline void detach() { if ( d->ref.isShared() ) detach_helper(); }
    inline bool isDetached() const { return !d->ref.isShared(); }
#if !defined(QT_NO_UNSHARABLE_CONTAINERS)
    inline void setSharable ( bool sharable ) {
        if ( sharable == d->ref.isSharable() )
            return;
        if ( !sharable )
            detach();
        // Don't call on shared_null
        d->ref.setSharable ( sharable );
    }
#endif
    inline bool isSharedWith ( const QQtOrderedMap<Key, T>& other ) const { return d == other.d; }

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

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef qptrdiff difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        inline iterator() : i ( Q_NULLPTR ) { }
        inline iterator ( Node* node ) : i ( node ) { }

        inline const Key& key() const { return i->key; }
        inline T& value() const { return i->value; }
        inline T& operator*() const { return i->value; }
        inline T* operator->() const { return &i->value; }
        inline bool operator== ( const iterator& o ) const { return i == o.i; }
        inline bool operator!= ( const iterator& o ) const { return i != o.i; }

        inline iterator& operator++() {
            i = i->nextNode();
            return *this;
        }
        inline iterator operator++ ( int ) {
            iterator r = *this;
            i = i->nextNode();
            return r;
        }
        inline iterator& operator--() {
            i = i->previousNode();
            return *this;
        }
        inline iterator operator-- ( int ) {
            iterator r = *this;
            i = i->previousNode();
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
        friend class QQtOrderedMap<Key, T>;
    };
    friend class iterator;

    class const_iterator
    {
        friend class iterator;
        const Node* i;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef qptrdiff difference_type;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;

        Q_DECL_CONSTEXPR inline const_iterator() : i ( Q_NULLPTR ) { }
        inline const_iterator ( const Node* node ) : i ( node ) { }
#ifdef QT_STRICT_ITERATORS
        explicit inline const_iterator ( const iterator& o )
#else
        inline const_iterator ( const iterator& o )
#endif
        { i = o.i; }

        inline const Key& key() const { return i->key; }
        inline const T& value() const { return i->value; }
        inline const T& operator*() const { return i->value; }
        inline const T* operator->() const { return &i->value; }
        Q_DECL_CONSTEXPR inline bool operator== ( const const_iterator& o ) const { return i == o.i; }
        Q_DECL_CONSTEXPR inline bool operator!= ( const const_iterator& o ) const { return i != o.i; }

        inline const_iterator& operator++() {
            i = i->nextNode();
            return *this;
        }
        inline const_iterator operator++ ( int ) {
            const_iterator r = *this;
            i = i->nextNode();
            return r;
        }
        inline const_iterator& operator--() {
            i = i->previousNode();
            return *this;
        }
        inline const_iterator operator-- ( int ) {
            const_iterator r = *this;
            i = i->previousNode();
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
        friend class QQtOrderedMap<Key, T>;
    };
    friend class const_iterator;

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
    inline iterator begin() { detach(); return iterator ( d->begin() ); }
    inline const_iterator begin() const { return const_iterator ( d->begin() ); }
    inline const_iterator constBegin() const { return const_iterator ( d->begin() ); }
    inline const_iterator cbegin() const { return const_iterator ( d->begin() ); }
    inline iterator end() { detach(); return iterator ( d->end() ); }
    inline const_iterator end() const { return const_iterator ( d->end() ); }
    inline const_iterator constEnd() const { return const_iterator ( d->end() ); }
    inline const_iterator cend() const { return const_iterator ( d->end() ); }
    inline key_iterator keyBegin() const { return key_iterator ( begin() ); }
    inline key_iterator keyEnd() const { return key_iterator ( end() ); }
    iterator erase ( iterator it );

    // more Qt
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    inline int count() const { return d->size; }
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
    QQtOrderedMap<Key, T>& unite ( const QQtOrderedMap<Key, T>& other );

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
        const QQtOrderedMapNodeBase* n = ci.i;
        while ( n->parent() )
            n = n->parent();
        return n->left == d->root();
#else
        Q_UNUSED ( ci );
        return true;
#endif
    }
};

template <class Key, class T>
inline QQtOrderedMap<Key, T>::QQtOrderedMap ( const QQtOrderedMap<Key, T>& other )
{
    if ( other.d->ref.ref() )
    {
        d = other.d;
    }
    else
    {
        d = QQtOrderedMapData<Key, T>::create();
        if ( other.d->header.left )
        {
            d->header.left = static_cast<Node*> ( other.d->header.left )->copy ( d );
            d->header.left->setParent ( &d->header );
            d->recalcMostLeftNode();
        }
    }
}

template <class Key, class T>
Q_INLINE_TEMPLATE QQtOrderedMap<Key, T>& QQtOrderedMap<Key, T>::operator= ( const QQtOrderedMap<Key, T>& other )
{
    if ( d != other.d )
    {
        QQtOrderedMap<Key, T> tmp ( other );
        tmp.swap ( *this );
    }
    return *this;
}

template <class Key, class T>
Q_INLINE_TEMPLATE void QQtOrderedMap<Key, T>::clear()
{
    *this = QQtOrderedMap<Key, T>();
}

QT_WARNING_PUSH
QT_WARNING_DISABLE_CLANG ( "-Wreturn-stack-address" )

template <class Key, class T>
Q_INLINE_TEMPLATE const T QQtOrderedMap<Key, T>::value ( const Key& akey, const T& adefaultValue ) const
{
    Node* n = d->findNode ( akey );
    return n ? n->value : adefaultValue;
}

QT_WARNING_POP

template <class Key, class T>
Q_INLINE_TEMPLATE const T QQtOrderedMap<Key, T>::operator[] ( const Key& akey ) const
{
    return value ( akey );
}

template <class Key, class T>
Q_INLINE_TEMPLATE T& QQtOrderedMap<Key, T>::operator[] ( const Key& akey )
{
    detach();
    Node* n = d->findNode ( akey );
    if ( !n )
        return *insert ( akey, T() );
    return n->value;
}

template <class Key, class T>
Q_INLINE_TEMPLATE int QQtOrderedMap<Key, T>::count ( const Key& akey ) const
{
    Node* firstNode;
    Node* lastNode;
    d->nodeRange ( akey, &firstNode, &lastNode );

    const_iterator ci_first ( firstNode );
    const const_iterator ci_last ( lastNode );
    int cnt = 0;
    while ( ci_first != ci_last )
    {
        ++cnt;
        ++ci_first;
    }
    return cnt;
}

template <class Key, class T>
Q_INLINE_TEMPLATE bool QQtOrderedMap<Key, T>::contains ( const Key& akey ) const
{
    return d->findNode ( akey ) != Q_NULLPTR;
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::iterator QQtOrderedMap<Key, T>::insert ( const Key& akey, const T& avalue )
{
    detach();
    Node* n = d->root();
    Node* y = d->end();
    Node* lastNode = Q_NULLPTR;
    bool  left = true;
    while ( n )
    {
        y = n;
        if ( !QQtOrderedMapLessThanKey ( n->key, akey ) )
        {
            lastNode = n;
            left = true;
            n = n->leftNode();
        }
        else
        {
            left = false;
            n = n->rightNode();
        }
    }
    if ( lastNode && !QQtOrderedMapLessThanKey ( akey, lastNode->key ) )
    {
        lastNode->value = avalue;
        return iterator ( lastNode );
    }
    Node* z = d->createNode ( akey, avalue, y, left );
    return iterator ( z );
}

template <class Key, class T>
typename QQtOrderedMap<Key, T>::iterator QQtOrderedMap<Key, T>::insert ( const_iterator pos, const Key& akey, const T& avalue )
{
    if ( d->ref.isShared() )
        return this->insert ( akey, avalue );

    Q_ASSERT_X ( isValidIterator ( pos ), "QQtOrderedMap::insert", "The specified const_iterator argument 'it' is invalid" );

    if ( pos == constEnd() )
    {
        // Hint is that the Node is larger than (or equal to) the largest value.
        Node* n = static_cast<Node*> ( pos.i->left );
        if ( n )
        {
            while ( n->right )
                n = static_cast<Node*> ( n->right );

            if ( !QQtOrderedMapLessThanKey ( n->key, akey ) )
                return this->insert ( akey, avalue ); // ignore hint
            // This can be optimized by checking equal too.
            // we can overwrite if previous node key is strictly smaller
            // (or there is no previous node)

            Node* z = d->createNode ( akey, avalue, n, false ); // insert right most
            return iterator ( z );
        }
        return this->insert ( akey, avalue );
    }
    else
    {
        // Hint indicates that the node should be less (or equal to) the hint given
        // but larger than the previous value.
        Node* next = const_cast<Node*> ( pos.i );
        if ( QQtOrderedMapLessThanKey ( next->key, akey ) )
            return this->insert ( akey, avalue ); // ignore hint

        if ( pos == constBegin() )
        {
            // There is no previous value
            // Maybe overwrite left most value
            if ( !QQtOrderedMapLessThanKey ( akey, next->key ) )
            {
                next->value = avalue; // overwrite current iterator
                return iterator ( next );
            }
            // insert left most.
            Node* z = d->createNode ( akey, avalue, begin().i, true );
            return iterator ( z );
        }
        else
        {
            Node* prev = const_cast<Node*> ( pos.i->previousNode() );
            if ( !QQtOrderedMapLessThanKey ( prev->key, akey ) )
            {
                return this->insert ( akey, avalue ); // ignore hint
            }
            // Hint is ok
            if ( !QQtOrderedMapLessThanKey ( akey, next->key ) )
            {
                next->value = avalue; // overwrite current iterator
                return iterator ( next );
            }

            // we need to insert (not overwrite)
            if ( prev->right == Q_NULLPTR )
            {
                Node* z = d->createNode ( akey, avalue, prev, false );
                return iterator ( z );
            }
            if ( next->left == Q_NULLPTR )
            {
                Node* z = d->createNode ( akey, avalue, next, true );
                return iterator ( z );
            }
            Q_ASSERT ( false ); // We should have prev->right == Q_NULLPTR or next->left == Q_NULLPTR.
            return this->insert ( akey, avalue );
        }
    }
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::iterator QQtOrderedMap<Key, T>::insertMulti ( const Key& akey,
        const T& avalue )
{
    detach();
    Node* y = d->end();
    Node* x = static_cast<Node*> ( d->root() );
    bool left = true;
    while ( x != Q_NULLPTR )
    {
        left = !QQtOrderedMapLessThanKey ( x->key, akey );
        y = x;
        x = left ? x->leftNode() : x->rightNode();
    }
    Node* z = d->createNode ( akey, avalue, y, left );
    return iterator ( z );
}

template <class Key, class T>
typename QQtOrderedMap<Key, T>::iterator QQtOrderedMap<Key, T>::insertMulti ( const_iterator pos, const Key& akey, const T& avalue )
{
    if ( d->ref.isShared() )
        return this->insertMulti ( akey, avalue );

    Q_ASSERT_X ( isValidIterator ( pos ), "QQtOrderedMap::insertMulti", "The specified const_iterator argument 'pos' is invalid" );

    if ( pos == constEnd() )
    {
        // Hint is that the Node is larger than (or equal to) the largest value.
        Node* n = static_cast<Node*> ( pos.i->left );
        if ( n )
        {
            while ( n->right )
                n = static_cast<Node*> ( n->right );

            if ( !QQtOrderedMapLessThanKey ( n->key, akey ) )
                return this->insertMulti ( akey, avalue ); // ignore hint
            Node* z = d->createNode ( akey, avalue, n, false ); // insert right most
            return iterator ( z );
        }
        return this->insertMulti ( akey, avalue );
    }
    else
    {
        // Hint indicates that the node should be less (or equal to) the hint given
        // but larger than the previous value.
        Node* next = const_cast<Node*> ( pos.i );
        if ( QQtOrderedMapLessThanKey ( next->key, akey ) )
            return this->insertMulti ( akey, avalue ); // ignore hint

        if ( pos == constBegin() )
        {
            // There is no previous value (insert left most)
            Node* z = d->createNode ( akey, avalue, begin().i, true );
            return iterator ( z );
        }
        else
        {
            Node* prev = const_cast<Node*> ( pos.i->previousNode() );
            if ( !QQtOrderedMapLessThanKey ( prev->key, akey ) )
                return this->insertMulti ( akey, avalue ); // ignore hint

            // Hint is ok - do insert
            if ( prev->right == Q_NULLPTR )
            {
                Node* z = d->createNode ( akey, avalue, prev, false );
                return iterator ( z );
            }
            if ( next->left == Q_NULLPTR )
            {
                Node* z = d->createNode ( akey, avalue, next, true );
                return iterator ( z );
            }
            Q_ASSERT ( false ); // We should have prev->right == Q_NULLPTR or next->left == Q_NULLPTR.
            return this->insertMulti ( akey, avalue );
        }
    }
}


template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::const_iterator QQtOrderedMap<Key, T>::constFind ( const Key& akey ) const
{
    Node* n = d->findNode ( akey );
    return const_iterator ( n ? n : d->end() );
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::const_iterator QQtOrderedMap<Key, T>::find ( const Key& akey ) const
{
    return constFind ( akey );
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::iterator QQtOrderedMap<Key, T>::find ( const Key& akey )
{
    detach();
    Node* n = d->findNode ( akey );
    return iterator ( n ? n : d->end() );
}

template <class Key, class T>
Q_INLINE_TEMPLATE QQtOrderedMap<Key, T>& QQtOrderedMap<Key, T>::unite ( const QQtOrderedMap<Key, T>& other )
{
    QQtOrderedMap<Key, T> copy ( other );
    const_iterator it = copy.constEnd();
    const const_iterator b = copy.constBegin();
    while ( it != b )
    {
        --it;
        insertMulti ( it.key(), it.value() );
    }
    return *this;
}

template <class Key, class T>
QPair<typename QQtOrderedMap<Key, T>::iterator, typename QQtOrderedMap<Key, T>::iterator> QQtOrderedMap<Key, T>::equal_range ( const Key& akey )
{
    detach();
    Node* firstNode, *lastNode;
    d->nodeRange ( akey, &firstNode, &lastNode );
    return QPair<iterator, iterator> ( iterator ( firstNode ), iterator ( lastNode ) );
}

template <class Key, class T>
QPair<typename QQtOrderedMap<Key, T>::const_iterator, typename QQtOrderedMap<Key, T>::const_iterator>
QQtOrderedMap<Key, T>::equal_range ( const Key& akey ) const
{
    Node* firstNode, *lastNode;
    d->nodeRange ( akey, &firstNode, &lastNode );
    return qMakePair ( const_iterator ( firstNode ), const_iterator ( lastNode ) );
}

#ifdef Q_MAP_DEBUG
template <class Key, class T>
void QQtOrderedMap<Key, T>::dump() const
{
    const_iterator it = begin();
    qDebug ( "map dump:" );
    while ( it != end() )
    {
        const QQtOrderedMapNodeBase* n = it.i;
        int depth = 0;
        while ( n && n != d->root() )
        {
            ++depth;
            n = n->parent();
        }
        QByteArray space ( 4 * depth, ' ' );
        qDebug() << space << ( it.i->color() == Node::Red ? "Red  " : "Black" ) << it.i << it.i->left << it.i->right
                 << it.key() << it.value();
        ++it;
    }
    qDebug ( "---------" );
}
#endif

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE int QQtOrderedMap<Key, T>::remove ( const Key& akey )
{
    detach();
    int n = 0;
    while ( Node* node = d->findNode ( akey ) )
    {
        d->deleteNode ( node );
        ++n;
    }
    return n;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE T QQtOrderedMap<Key, T>::take ( const Key& akey )
{
    detach();

    Node* node = d->findNode ( akey );
    if ( node )
    {
        T t = node->value;
        d->deleteNode ( node );
        return t;
    }
    return T();
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE typename QQtOrderedMap<Key, T>::iterator QQtOrderedMap<Key, T>::erase ( iterator it )
{
    if ( it == iterator ( d->end() ) )
        return it;

    Q_ASSERT_X ( isValidIterator ( const_iterator ( it ) ), "QQtOrderedMap::erase", "The specified iterator argument 'it' is invalid" );

    if ( d->ref.isShared() )
    {
        const_iterator oldBegin = constBegin();
        const_iterator old = const_iterator ( it );
        int backStepsWithSameKey = 0;

        while ( old != oldBegin )
        {
            --old;
            if ( QQtOrderedMapLessThanKey ( old.key(), it.key() ) )
                break;
            ++backStepsWithSameKey;
        }

        it = find ( old.key() ); // ensures detach
        Q_ASSERT_X ( it != iterator ( d->end() ), "QQtOrderedMap::erase", "Unable to locate same key in erase after detach." );

        while ( backStepsWithSameKey > 0 )
        {
            ++it;
            --backStepsWithSameKey;
        }
    }

    Node* n = it.i;
    ++it;
    d->deleteNode ( n );
    return it;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE void QQtOrderedMap<Key, T>::detach_helper()
{
    QQtOrderedMapData<Key, T>* x = QQtOrderedMapData<Key, T>::create();
    if ( d->header.left )
    {
        x->header.left = static_cast<Node*> ( d->header.left )->copy ( x );
        x->header.left->setParent ( &x->header );
    }
    if ( !d->ref.deref() )
        d->destroy();
    d = x;
    d->recalcMostLeftNode();
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QQtOrderedMap<Key, T>::uniqueKeys() const
{
    QList<Key> res;
    res.reserve ( size() ); // May be too much, but assume short lifetime
    const_iterator i = begin();
    if ( i != end() )
    {
        for ( ;; )
        {
            const Key& aKey = i.key();
            res.append ( aKey );
            do
            {
                if ( ++i == end() )
                    goto break_out_of_outer_loop;
            } while ( !QQtOrderedMapLessThanKey ( aKey, i.key() ) ); // loop while (key == i.key())
        }
    }
break_out_of_outer_loop:
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QQtOrderedMap<Key, T>::keys() const
{
    QList<Key> res;
    res.reserve ( size() );
    const_iterator i = begin();
    while ( i != end() )
    {
        res.append ( i.key() );
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QQtOrderedMap<Key, T>::keys ( const T& avalue ) const
{
    QList<Key> res;
    const_iterator i = begin();
    while ( i != end() )
    {
        if ( i.value() == avalue )
            res.append ( i.key() );
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE const Key QQtOrderedMap<Key, T>::key ( const T& avalue, const Key& defaultKey ) const
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
Q_OUTOFLINE_TEMPLATE QList<T> QQtOrderedMap<Key, T>::values() const
{
    QList<T> res;
    res.reserve ( size() );
    const_iterator i = begin();
    while ( i != end() )
    {
        res.append ( i.value() );
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<T> QQtOrderedMap<Key, T>::values ( const Key& akey ) const
{
    QList<T> res;
    Node* n = d->findNode ( akey );
    if ( n )
    {
        const_iterator it ( n );
        do
        {
            res.append ( *it );
            ++it;
        } while ( it != constEnd() && !QQtOrderedMapLessThanKey<Key> ( akey, it.key() ) );
    }
    return res;
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::const_iterator QQtOrderedMap<Key, T>::lowerBound ( const Key& akey ) const
{
    Node* lb = d->root() ? d->root()->lowerBound ( akey ) : Q_NULLPTR;
    if ( !lb )
        lb = d->end();
    return const_iterator ( lb );
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::iterator QQtOrderedMap<Key, T>::lowerBound ( const Key& akey )
{
    detach();
    Node* lb = d->root() ? d->root()->lowerBound ( akey ) : Q_NULLPTR;
    if ( !lb )
        lb = d->end();
    return iterator ( lb );
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::const_iterator
QQtOrderedMap<Key, T>::upperBound ( const Key& akey ) const
{
    Node* ub = d->root() ? d->root()->upperBound ( akey ) : Q_NULLPTR;
    if ( !ub )
        ub = d->end();
    return const_iterator ( ub );
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QQtOrderedMap<Key, T>::iterator QQtOrderedMap<Key, T>::upperBound ( const Key& akey )
{
    detach();
    Node* ub = d->root() ? d->root()->upperBound ( akey ) : Q_NULLPTR;
    if ( !ub )
        ub = d->end();
    return iterator ( ub );
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE bool QQtOrderedMap<Key, T>::operator== ( const QQtOrderedMap<Key, T>& other ) const
{
    if ( size() != other.size() )
        return false;
    if ( d == other.d )
        return true;

    const_iterator it1 = begin();
    const_iterator it2 = other.begin();

    while ( it1 != end() )
    {
        if ( ! ( it1.value() == it2.value() ) || QQtOrderedMapLessThanKey ( it1.key(), it2.key() ) || QQtOrderedMapLessThanKey ( it2.key(), it1.key() ) )
            return false;
        ++it2;
        ++it1;
    }
    return true;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QQtOrderedMap<Key, T>::QQtOrderedMap ( const std::map<Key, T>& other )
{
    d = QQtOrderedMapData<Key, T>::create();
    typename std::map<Key, T>::const_iterator it = other.end();
    while ( it != other.begin() )
    {
        --it;
        d->createNode ( ( *it ).first, ( *it ).second, d->begin(), true ); // insert on most left node.
    }
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE std::map<Key, T> QQtOrderedMap<Key, T>::toStdMap() const
{
    std::map<Key, T> map;
    const_iterator it = end();
    while ( it != begin() )
    {
        --it;
        map.insert ( map.begin(), std::pair<Key, T> ( it.key(), it.value() ) );
    }
    return map;
}

template <class Key, class T>
class QQtOrderedMultiMap : public QQtOrderedMap<Key, T>
{
public:
    QQtOrderedMultiMap() Q_DECL_NOTHROW {}
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline QQtOrderedMultiMap ( std::initializer_list<std::pair<Key, T> > list ) {
        for ( typename std::initializer_list<std::pair<Key, T> >::const_iterator it = list.begin(); it != list.end(); ++it )
            insert ( it->first, it->second );
    }
#endif
    QQtOrderedMultiMap ( const QQtOrderedMap<Key, T>& other ) : QQtOrderedMap<Key, T> ( other ) {}
#ifdef Q_COMPILER_RVALUE_REFS
QQtOrderedMultiMap ( QQtOrderedMap<Key, T>&& other ) Q_DECL_NOTHROW : QQtOrderedMap<Key, T> ( std::move ( other ) ) {}
#endif
    void swap ( QQtOrderedMultiMap<Key, T>& other ) Q_DECL_NOTHROW { QQtOrderedMap<Key, T>::swap ( other ); }

    inline typename QQtOrderedMap<Key, T>::iterator replace ( const Key& key, const T& value )
    { return QQtOrderedMap<Key, T>::insert ( key, value ); }
    inline typename QQtOrderedMap<Key, T>::iterator insert ( const Key& key, const T& value )
    { return QQtOrderedMap<Key, T>::insertMulti ( key, value ); }
    inline typename QQtOrderedMap<Key, T>::iterator insert ( typename QQtOrderedMap<Key, T>::const_iterator pos, const Key& key, const T& value )
    { return QQtOrderedMap<Key, T>::insertMulti ( pos, key, value ); }

    inline QQtOrderedMultiMap& operator+= ( const QQtOrderedMultiMap& other )
    { this->unite ( other ); return *this; }
    inline QQtOrderedMultiMap operator+ ( const QQtOrderedMultiMap& other ) const
    { QQtOrderedMultiMap result = *this; result += other; return result; }

    using QQtOrderedMap<Key, T>::contains;
    using QQtOrderedMap<Key, T>::remove;
    using QQtOrderedMap<Key, T>::count;
    using QQtOrderedMap<Key, T>::find;
    using QQtOrderedMap<Key, T>::constFind;

    bool contains ( const Key& key, const T& value ) const;

    int remove ( const Key& key, const T& value );

    int count ( const Key& key, const T& value ) const;

    typename QQtOrderedMap<Key, T>::iterator find ( const Key& key, const T& value ) {
        typename QQtOrderedMap<Key, T>::iterator i ( find ( key ) );
        typename QQtOrderedMap<Key, T>::iterator end ( this->end() );
        while ( i != end && !QQtOrderedMapLessThanKey<Key> ( key, i.key() ) ) {
            if ( i.value() == value )
                return i;
            ++i;
        }
        return end;
    }
    typename QQtOrderedMap<Key, T>::const_iterator find ( const Key& key, const T& value ) const {
        typename QQtOrderedMap<Key, T>::const_iterator i ( constFind ( key ) );
        typename QQtOrderedMap<Key, T>::const_iterator end ( QQtOrderedMap<Key, T>::constEnd() );
        while ( i != end && !QQtOrderedMapLessThanKey<Key> ( key, i.key() ) ) {
            if ( i.value() == value )
                return i;
            ++i;
        }
        return end;
    }
    typename QQtOrderedMap<Key, T>::const_iterator constFind ( const Key& key, const T& value ) const
    { return find ( key, value ); }
private:
    T& operator[] ( const Key& key );
    const T operator[] ( const Key& key ) const;
};

template <class Key, class T>
Q_INLINE_TEMPLATE bool QQtOrderedMultiMap<Key, T>::contains ( const Key& key, const T& value ) const
{
    return constFind ( key, value ) != QQtOrderedMap<Key, T>::constEnd();
}

template <class Key, class T>
Q_INLINE_TEMPLATE int QQtOrderedMultiMap<Key, T>::remove ( const Key& key, const T& value )
{
    int n = 0;
    typename QQtOrderedMap<Key, T>::iterator i ( find ( key ) );
    typename QQtOrderedMap<Key, T>::iterator end ( QQtOrderedMap<Key, T>::end() );
    while ( i != end && !QQtOrderedMapLessThanKey<Key> ( key, i.key() ) )
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
Q_INLINE_TEMPLATE int QQtOrderedMultiMap<Key, T>::count ( const Key& key, const T& value ) const
{
    int n = 0;
    typename QQtOrderedMap<Key, T>::const_iterator i ( constFind ( key ) );
    typename QQtOrderedMap<Key, T>::const_iterator end ( QQtOrderedMap<Key, T>::constEnd() );
    while ( i != end && !QQtOrderedMapLessThanKey<Key> ( key, i.key() ) )
    {
        if ( i.value() == value )
            ++n;
        ++i;
    }
    return n;
}

Q_DECLARE_ASSOCIATIVE_ITERATOR ( QtOrderedMap )
Q_DECLARE_MUTABLE_ASSOCIATIVE_ITERATOR ( QtOrderedMap )

#endif // QQTORDEREDMAP_H
