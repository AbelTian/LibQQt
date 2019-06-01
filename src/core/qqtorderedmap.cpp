#include <qqtorderedmap.h>

#include <stdlib.h>

#ifdef QT_QMAP_DEBUG
# include <qstring.h>
# include <qvector.h>
#endif

const QQtOrderedMapDataBase QQtOrderedMapDataBase::shared_null = { Q_REFCOUNT_INITIALIZE_STATIC, 0, { 0, 0, 0 }, 0 };

const QQtOrderedMapNodeBase* QQtOrderedMapNodeBase::nextNode() const
{
    const QQtOrderedMapNodeBase* n = this;
    if ( n->right )
    {
        n = n->right;
        while ( n->left )
            n = n->left;
    }
    else
    {
        const QQtOrderedMapNodeBase* y = n->parent();
        while ( y && n == y->right )
        {
            n = y;
            y = n->parent();
        }
        n = y;
    }
    return n;
}

const QQtOrderedMapNodeBase* QQtOrderedMapNodeBase::previousNode() const
{
    const QQtOrderedMapNodeBase* n = this;
    if ( n->left )
    {
        n = n->left;
        while ( n->right )
            n = n->right;
    }
    else
    {
        const QQtOrderedMapNodeBase* y = n->parent();
        while ( y && n == y->left )
        {
            n = y;
            y = n->parent();
        }
        n = y;
    }
    return n;
}


void QQtOrderedMapDataBase::rotateLeft ( QQtOrderedMapNodeBase* x )
{
    QQtOrderedMapNodeBase*& root = header.left;
    QQtOrderedMapNodeBase* y = x->right;
    x->right = y->left;
    if ( y->left != 0 )
        y->left->setParent ( x );
    y->setParent ( x->parent() );
    if ( x == root )
        root = y;
    else if ( x == x->parent()->left )
        x->parent()->left = y;
    else
        x->parent()->right = y;
    y->left = x;
    x->setParent ( y );
}


void QQtOrderedMapDataBase::rotateRight ( QQtOrderedMapNodeBase* x )
{
    QQtOrderedMapNodeBase*& root = header.left;
    QQtOrderedMapNodeBase* y = x->left;
    x->left = y->right;
    if ( y->right != 0 )
        y->right->setParent ( x );
    y->setParent ( x->parent() );
    if ( x == root )
        root = y;
    else if ( x == x->parent()->right )
        x->parent()->right = y;
    else
        x->parent()->left = y;
    y->right = x;
    x->setParent ( y );
}


void QQtOrderedMapDataBase::rebalance ( QQtOrderedMapNodeBase* x )
{
    QQtOrderedMapNodeBase*& root = header.left;
    x->setColor ( QQtOrderedMapNodeBase::Red );
    while ( x != root && x->parent()->color() == QQtOrderedMapNodeBase::Red )
    {
        if ( x->parent() == x->parent()->parent()->left )
        {
            QQtOrderedMapNodeBase* y = x->parent()->parent()->right;
            if ( y && y->color() == QQtOrderedMapNodeBase::Red )
            {
                x->parent()->setColor ( QQtOrderedMapNodeBase::Black );
                y->setColor ( QQtOrderedMapNodeBase::Black );
                x->parent()->parent()->setColor ( QQtOrderedMapNodeBase::Red );
                x = x->parent()->parent();
            }
            else
            {
                if ( x == x->parent()->right )
                {
                    x = x->parent();
                    rotateLeft ( x );
                }
                x->parent()->setColor ( QQtOrderedMapNodeBase::Black );
                x->parent()->parent()->setColor ( QQtOrderedMapNodeBase::Red );
                rotateRight ( x->parent()->parent() );
            }
        }
        else
        {
            QQtOrderedMapNodeBase* y = x->parent()->parent()->left;
            if ( y && y->color() == QQtOrderedMapNodeBase::Red )
            {
                x->parent()->setColor ( QQtOrderedMapNodeBase::Black );
                y->setColor ( QQtOrderedMapNodeBase::Black );
                x->parent()->parent()->setColor ( QQtOrderedMapNodeBase::Red );
                x = x->parent()->parent();
            }
            else
            {
                if ( x == x->parent()->left )
                {
                    x = x->parent();
                    rotateRight ( x );
                }
                x->parent()->setColor ( QQtOrderedMapNodeBase::Black );
                x->parent()->parent()->setColor ( QQtOrderedMapNodeBase::Red );
                rotateLeft ( x->parent()->parent() );
            }
        }
    }
    root->setColor ( QQtOrderedMapNodeBase::Black );
}

void QQtOrderedMapDataBase::freeNodeAndRebalance ( QQtOrderedMapNodeBase* z )
{
    QQtOrderedMapNodeBase*& root = header.left;
    QQtOrderedMapNodeBase* y = z;
    QQtOrderedMapNodeBase* x;
    QQtOrderedMapNodeBase* x_parent;
    if ( y->left == 0 )
    {
        x = y->right;
        if ( y == mostLeftNode )
        {
            if ( x )
                mostLeftNode = x; // It cannot have (left) children due the red black invariant.
            else
                mostLeftNode = y->parent();
        }
    }
    else
    {
        if ( y->right == 0 )
        {
            x = y->left;
        }
        else
        {
            y = y->right;
            while ( y->left != 0 )
                y = y->left;
            x = y->right;
        }
    }
    if ( y != z )
    {
        z->left->setParent ( y );
        y->left = z->left;
        if ( y != z->right )
        {
            x_parent = y->parent();
            if ( x )
                x->setParent ( y->parent() );
            y->parent()->left = x;
            y->right = z->right;
            z->right->setParent ( y );
        }
        else
        {
            x_parent = y;
        }
        if ( root == z )
            root = y;
        else if ( z->parent()->left == z )
            z->parent()->left = y;
        else
            z->parent()->right = y;
        y->setParent ( z->parent() );
        // Swap the colors
        QQtOrderedMapNodeBase::Color c = y->color();
        y->setColor ( z->color() );
        z->setColor ( c );
        y = z;
    }
    else
    {
        x_parent = y->parent();
        if ( x )
            x->setParent ( y->parent() );
        if ( root == z )
            root = x;
        else if ( z->parent()->left == z )
            z->parent()->left = x;
        else
            z->parent()->right = x;
    }
    if ( y->color() != QQtOrderedMapNodeBase::Red )
    {
        while ( x != root && ( x == 0 || x->color() == QQtOrderedMapNodeBase::Black ) )
        {
            if ( x == x_parent->left )
            {
                QQtOrderedMapNodeBase* w = x_parent->right;
                if ( w->color() == QQtOrderedMapNodeBase::Red )
                {
                    w->setColor ( QQtOrderedMapNodeBase::Black );
                    x_parent->setColor ( QQtOrderedMapNodeBase::Red );
                    rotateLeft ( x_parent );
                    w = x_parent->right;
                }
                if ( ( w->left == 0 || w->left->color() == QQtOrderedMapNodeBase::Black ) &&
                     ( w->right == 0 || w->right->color() == QQtOrderedMapNodeBase::Black ) )
                {
                    w->setColor ( QQtOrderedMapNodeBase::Red );
                    x = x_parent;
                    x_parent = x_parent->parent();
                }
                else
                {
                    if ( w->right == 0 || w->right->color() == QQtOrderedMapNodeBase::Black )
                    {
                        if ( w->left )
                            w->left->setColor ( QQtOrderedMapNodeBase::Black );
                        w->setColor ( QQtOrderedMapNodeBase::Red );
                        rotateRight ( w );
                        w = x_parent->right;
                    }
                    w->setColor ( x_parent->color() );
                    x_parent->setColor ( QQtOrderedMapNodeBase::Black );
                    if ( w->right )
                        w->right->setColor ( QQtOrderedMapNodeBase::Black );
                    rotateLeft ( x_parent );
                    break;
                }
            }
            else
            {
                QQtOrderedMapNodeBase* w = x_parent->left;
                if ( w->color() == QQtOrderedMapNodeBase::Red )
                {
                    w->setColor ( QQtOrderedMapNodeBase::Black );
                    x_parent->setColor ( QQtOrderedMapNodeBase::Red );
                    rotateRight ( x_parent );
                    w = x_parent->left;
                }
                if ( ( w->right == 0 || w->right->color() == QQtOrderedMapNodeBase::Black ) &&
                     ( w->left == 0 || w->left->color() == QQtOrderedMapNodeBase::Black ) )
                {
                    w->setColor ( QQtOrderedMapNodeBase::Red );
                    x = x_parent;
                    x_parent = x_parent->parent();
                }
                else
                {
                    if ( w->left == 0 || w->left->color() == QQtOrderedMapNodeBase::Black )
                    {
                        if ( w->right )
                            w->right->setColor ( QQtOrderedMapNodeBase::Black );
                        w->setColor ( QQtOrderedMapNodeBase::Red );
                        rotateLeft ( w );
                        w = x_parent->left;
                    }
                    w->setColor ( x_parent->color() );
                    x_parent->setColor ( QQtOrderedMapNodeBase::Black );
                    if ( w->left )
                        w->left->setColor ( QQtOrderedMapNodeBase::Black );
                    rotateRight ( x_parent );
                    break;
                }
            }
        }
        if ( x )
            x->setColor ( QQtOrderedMapNodeBase::Black );
    }
    free ( y );
    --size;
}

void QQtOrderedMapDataBase::recalcMostLeftNode()
{
    mostLeftNode = &header;
    while ( mostLeftNode->left )
        mostLeftNode = mostLeftNode->left;
}

static inline int qMapAlignmentThreshold()
{
    // malloc on 32-bit platforms should return pointers that are 8-byte
    // aligned or more while on 64-bit platforms they should be 16-byte aligned
    // or more
    return 2 * sizeof ( void* );
}

static inline void* qMapAllocate ( int alloc, int alignment )
{
    return alignment > qMapAlignmentThreshold()
           ? qMallocAligned ( alloc, alignment )
           : ::malloc ( alloc );
}

static inline void qMapDeallocate ( QQtOrderedMapNodeBase* node, int alignment )
{
    if ( alignment > qMapAlignmentThreshold() )
        qFreeAligned ( node );
    else
        ::free ( node );
}

QQtOrderedMapNodeBase* QQtOrderedMapDataBase::createNode ( int alloc, int alignment, QQtOrderedMapNodeBase* parent, bool left )
{
    QQtOrderedMapNodeBase* node = static_cast<QQtOrderedMapNodeBase*> ( qMapAllocate ( alloc, alignment ) );
    Q_CHECK_PTR ( node );

    memset ( node, 0, alloc );
    ++size;

    if ( parent )
    {
        if ( left )
        {
            parent->left = node;
            if ( parent == mostLeftNode )
                mostLeftNode = node;
        }
        else
        {
            parent->right = node;
        }
        node->setParent ( parent );
        rebalance ( node );
    }
    return node;
}

void QQtOrderedMapDataBase::freeTree ( QQtOrderedMapNodeBase* root, int alignment )
{
    if ( root->left )
        freeTree ( root->left, alignment );
    if ( root->right )
        freeTree ( root->right, alignment );
    qMapDeallocate ( root, alignment );
}

QQtOrderedMapDataBase* QQtOrderedMapDataBase::createData()
{
    QQtOrderedMapDataBase* d = new QQtOrderedMapDataBase;

    d->ref.initializeOwned();
    d->size = 0;

    d->header.p = 0;
    d->header.left = 0;
    d->header.right = 0;
    d->mostLeftNode = & ( d->header );

    return d;
}

void QQtOrderedMapDataBase::freeData ( QQtOrderedMapDataBase* d )
{
    delete d;
}
