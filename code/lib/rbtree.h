/**
 *https://www.cnblogs.com/skywang12345/p/3624291.html
 * @author skywang
 * @date 2013/11/07
 */

#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_ 

//#include <iomanip>
#include <iostream>
using namespace std;

enum RBTColor{RED, BLACK};

template <class T>
class RBTNode{
    public:
        RBTColor color;    
        T key;            
        RBTNode *left;    
        RBTNode *right;    
        RBTNode *parent; 

        RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r):
            key(value),color(c),parent(),left(l),right(r) {}
};

template <class T>
class RBTree {
    private:
        RBTNode<T> *mRoot;    

    public:
        RBTree(int (*comp)(T x, T y));
        ~RBTree();

        void preOrder();

        void inOrder();
    
        void postOrder();

        
        RBTNode<T>* search(T key);
      
        RBTNode<T>* iterativeSearch(T key);

       
        T minimum();

        T maximum();

        RBTNode<T>* successor(RBTNode<T> *x);
 
        RBTNode<T>* predecessor(RBTNode<T> *x);

        void insert(T key);

        void remove(T key);
        
        T removeMin();

        void destroy();

        void print();

        int getNum(){return num;};
    private:
        int num;      
         
        int (*compare)(T x, T y);
     
        void preOrder(RBTNode<T>* tree) const;
    
        void inOrder(RBTNode<T>* tree) const;
 
        void postOrder(RBTNode<T>* tree) const;

        RBTNode<T>* search(RBTNode<T>* x, T key) const;
     
        RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

        RBTNode<T>* minimum(RBTNode<T>* tree);

        RBTNode<T>* maximum(RBTNode<T>* tree);

        void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
    
        void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);

        void insert(RBTNode<T>* &root, RBTNode<T>* node);

        void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
 
        void remove(RBTNode<T>* &root, RBTNode<T> *node);
 
        void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

        void destroy(RBTNode<T>* &tree);

        void print(RBTNode<T>* tree, T key, int direction);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};
#include "rbtree.cc"


#endif