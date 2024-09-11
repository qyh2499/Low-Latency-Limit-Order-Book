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
    AVLTreeNode<T> *root;
    int size;

    AVLTreeNode<T> *balance(AVLTreeNode<T> *node);
    AVLTreeNode<T> *findMin(AVLTreeNode<T> *node);
    AVLTreeNode<T> *removeMin(AVLTreeNode<T> *node);
    AVLTreeNode<T> *insertHelper(AVLTreeNode<T> *node, const T value);
    AVLTreeNode<T> *removeHelper(AVLTreeNode<T> *node, const T value);
    void _display(AVLTreeNode<T> *cur, int depth = 0, int state = 0);

public:
    AVLTree();
    ~AVLTree();

    bool isEmpty() const;
    int getSize() const;

    // query and modify functions
    void insert(const T value);
    void remove(const T value);
    void display();
};

template <class T>
AVLTree<T>::AVLTree() : root(nullptr), size(0)
{
}

template <class T>
AVLTree<T>::~AVLTree()
{
}

template <class T>
bool AVLTree<T>::isEmpty() const
{
    return size == 0;
}

template <class T>
int AVLTree<T>::getSize() const
{
    return size;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::balance(AVLTreeNode<T> *node) // Balancing at the input node
{
    node->updateHeight();

    if (node->getBalanceFactor() == 2)
    {
        if (node->right->getBalanceFactor() < 0)
        {
            node->right = node->right->rightRotate();
        }
        return node->leftRotate();
    }
    if (node->getBalanceFactor() == -2)
    {
        if (node->left->getBalanceFactor() > 0)
        {
            node->left = node->left->leftRotate();
        }
        return node->rightRotate();
    }
    return node;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::insertHelper(AVLTreeNode<T> *node, const T value)
{
    if (node == nullptr)
    {
        return new AVLTreeNode<T>(value);
    }
    if (value < node->value)
    {
        node->left = insertHelper(node->left, value);
    }
    else
    {
        node->right = insertHelper(node->right, value);
    }
    return balance(node);
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::findMin(AVLTreeNode<T> *node) // Find the leftmost in the node tree
{
    return node->left ? findMin(node->left) : node;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::removeMin(AVLTreeNode<T> *node) // Remove the leftmost in the node tree
{
    if (node->left == nullptr)
        return node->right;
    node->left = removeMin(node->left);
    return balance(node);
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::removeHelper(AVLTreeNode<T> *node, const T value) // Remove the value from the tree at node
{
    if (node == nullptr)
        return nullptr;
    if (value < node->value)
        node->left = removeHelper(node->left, value);
    else if (value > node->value)
        node->right = removeHelper(node->right, value);
    else //  value == node->value
    {
        AVLTreeNode<T> *l = node->left;
        AVLTreeNode<T> *r = node->right;
        delete node;
        if (r == nullptr)
        {
            return l;
        }
        AVLTreeNode<T> *min = findMin(r);
        min->right = removeMin(r);
        min->left = l;
        return balance(min);
    }
    return balance(node);
}

template <class T>
void AVLTree<T>::_display(AVLTreeNode<T> *cur, int depth, int state)
{ // state: 1 -> left, 2 -> right , 0 -> root
    if (cur->left)
        _display(cur->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("┌───");
    else if (state == 2) // right
        printf("└───");

    std::cout << "[" << cur->value << "] - (" << cur->height << ")" << std::endl;

    if (cur->right)
        _display(cur->right, depth + 1, 2);
}

// PUBLIC FUNCTIONS

template <class T>
void AVLTree<T>::insert(const T value)
{
    root = insertHelper(root, value);
}

template <class T>
void AVLTree<T>::remove(const T value)
{
    root = removeHelper(root, value);
}

template <class T>
void AVLTree<T>::display()
{
    printf("\n");
    if (root != nullptr)
    {
        _display(root, 0, 0);
    }
    else
    {
        printf("Empty");
    }
    printf("\n");
}

#endif
