#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <iostream>
#include <string>
#include <vector>
#include "AVLTreeNode.hpp"

template <class T>
class AVLTree
{

private:
    AVLTree<T> *root;
    int size;

    AVLTreeNode<T> *balance(AVLTreeNode<T> *node);
    AVLTreeNode<T> *findmin(AVLTreeNode<T> *node);
    AVLTreeNode<T> *removemin(AVLTreeNode<T> *node);
    void _display(AVLTreeNode<T> *cur, int depth = 0, int state = 0);

public:
    AVLTree();
    ~AVLTree();

    bool isEmpty() const;
    int getSize() const;

    // query and modify functions
    AVLTreeNode<T> *insert(AVLTreeNode<T> *node, const T value);
    AVLTreeNode<T> *remove(AVLTreeNode<T> *node, const T value);
    
    void display();
};

#endif
