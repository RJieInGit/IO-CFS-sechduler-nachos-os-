

template <class T>
RBTree<T>::RBTree(int (*comp)(T x, T y)):mRoot(NULL)
{
    compare= comp;
    mRoot = NULL;
    num=0;
}


template <class T>
RBTree<T>::~RBTree() 
{
    destroy();
}


template <class T>
void RBTree<T>::preOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        cout<< tree->key << " " ;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void RBTree<T>::preOrder() 
{
    preOrder(mRoot);
}


template <class T>
void RBTree<T>::inOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        cout<< ((Thread*)tree->key)->vruntime << "("<<((Thread*)tree->key)->getName()<<")";
        inOrder(tree->right);
    }
}

template <class T>
void RBTree<T>::inOrder() 
{
    inOrder(mRoot);
   // printf("\n\n\n+++++++++++++++++++++\n\n\n");
}


template <class T>
void RBTree<T>::postOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout<< tree->key << " " ;
    }
}

template <class T>
void RBTree<T>::postOrder() 
{
    postOrder(mRoot);
}


template <class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, T key) const
{
//printf("%d , %d \n",(Thread*)(x->key)->vruntime,(Thread*)key->vruntime);
    if (x==NULL || x->key==key)
        return x;
    if (compare(key, x->key)<0)
        return search(x->left, key);
    else if(compare(key,x->key)>0){
        return search(x->right, key);
    }
    else{
        RBTNode<T>* l =search(x->left,key);
        if(l!=NULL)
            return l;
        else
        {
            return search(x->right,key);
        }
        
    }
}

template <class T>
RBTNode<T>* RBTree<T>::search(T key) 
{
    search(mRoot, key);
}


template <class T>
RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T>* x, T key) const
{
    while ((x!=NULL) && (x->key!=key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template <class T>
RBTNode<T>* RBTree<T>::iterativeSearch(T key)
{
    iterativeSearch(mRoot, key);
}


template <class T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T>
T RBTree<T>::minimum()
{
    RBTNode<T> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}
 

template <class T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T RBTree<T>::maximum()
{
    RBTNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}


template <class T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x)
{
    if (x->right != NULL)
        return minimum(x->right);
    RBTNode<T>* y = x->parent;
    while ((y!=NULL) && (x==y->right))
    {
        x = y;
        y = y->parent;
    }

    return y;
}
 

template <class T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T> *x)
{

    if (x->left != NULL)
        return maximum(x->left);
    RBTNode<T>* y = x->parent;
    while ((y!=NULL) && (x==y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/*
 *      px                              px
 *     /                               /
 *    x                               y                
 *   /     (left rotate)-->           / \                #
 *  lx   y                          x  ry     
 *     /   \                       /  \
 *    ly   ry                     lx  ly  
 *
 *
 */
template <class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
    RBTNode<T> *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
    {
        root = y;            
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;    
        else
            x->parent->right = y;    
    }
    
    y->left = x;
   
    x->parent = y;
}

/* 
 *
 *            py                               py
 *           /                                /
 *          y                                x                  
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y  
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 * 
 */
template <class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
    RBTNode<T> *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) 
    {
        root = x;            
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;    
        else
            y->parent->left = x;    
    }

    x->right = y;
    y->parent = x;
}


template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *parent, *gparent;

    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);
        if (parent == gparent->left)
        {  
            {
                RBTNode<T> *uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            if (parent->right == node)
            {
                RBTNode<T> *tmp;
                leftRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            rb_set_black(parent);
            rb_set_red(gparent);
            rightRotate(root, gparent);
        } 
        else
            {
                RBTNode<T> *uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            if (parent->left == node)
            {
                RBTNode<T> *tmp;
                rightRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            rb_set_black(parent);
            rb_set_red(gparent);
            leftRotate(root, gparent);
        }
    }
    rb_set_black(root);
}


template <class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *y = NULL;
    RBTNode<T> *x = root;

    while (x != NULL)
    {
        y = x;
        if (compare(node->key,x->key)<0)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y!=NULL)
    {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
        root = node;

    node->color = RED;

    insertFixUp(root, node);
}


 
template <class T>
void RBTree<T>::insert(T key)
{
    RBTNode<T> *z=NULL;

    if ((z=new RBTNode<T>(key,BLACK,NULL,NULL,NULL)) == NULL)
        return ;

    insert(mRoot, z);
    num++;
}


template <class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
    RBTNode<T> *other;

    while ((!node || rb_is_black(node)) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                rb_set_black(other);
                rb_set_red(parent);
                leftRotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rightRotate(root, other);
                    other = parent->right;
                }
 
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
      
                rb_set_black(other);
                rb_set_red(parent);
                rightRotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
            
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
   
                    rb_set_black(other->right);
                    rb_set_red(other);
                    leftRotate(root, other);
                    other = parent->left;
                }
  
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

template <class T>
void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T> *node)
{
    RBTNode<T> *child, *parent;
    RBTColor color;


    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        RBTNode<T> *replace = node;

        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        } 
        else 
            root = replace;
        child = replace->right;
        parent = rb_parent(replace);

        color = rb_color(replace);
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            removeFixUp(root, child, parent);

        //delete node;
        return ;
    }

    if (node->left !=NULL)
        child = node->left;
    else 
        child = node->right;

    parent = node->parent;
    color = node->color;

    if (child)
        child->parent = parent;


    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root = child;

    if (color == BLACK)
        removeFixUp(root, child, parent);
    //delete node;
}

template <class T>
void RBTree<T>::remove(T key)
{
    RBTNode<T> *node; 

    if ((node = search(mRoot, key)) != NULL){
        remove(mRoot, node);
        num--;
    }
    else{
        printf("fatal!! remove fail \n\n\n");
    }
}


template <class T>
void RBTree<T>::destroy(RBTNode<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree=NULL;
}

template <class T>
void RBTree<T>::destroy()
{
    destroy(mRoot);
}


template <class T>
void RBTree<T>::print(RBTNode<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    
            cout  << tree->key << "(B) is root" << endl;
        else                
            cout  << tree->key <<  (rb_is_red(tree)?"(R)":"(B)") << " is "  << key << "'s "   << (direction==1?"right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <class T>
void RBTree<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}

template <class T>
T RBTree<T>::removeMin(){
    //printf("num: %d\n",num);
    inOrder();
     RBTNode<T> *p = minimum(mRoot);
    if (p != NULL){
        remove(mRoot,p);
        num--;
        return p->key;
    }
       //  printf("remove Min encounter NUll\n");
    return (T)NULL;
}