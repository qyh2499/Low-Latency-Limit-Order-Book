#include "AVLTreeNode.hpp"

template <class T>
AVLTreeNode<T>::AVLTreeNode(T value)
    : value(value), height(1), left(nullptr), right(nullptr)
{
}

template <class T>
AVLTreeNode<T>::~AVLTreeNode()
{
}

template <class T>
void AVLTreeNode<T>::updateHeight()
{
    height = std::max(left != nullptr ? left->height : 0, right != nullptr ? right->height : 0) + 1;
}

template <class T>
int AVLTreeNode<T>::getBalanceFactor()
{
    return (left != nullptr ? left->height : 0) - (right != nullptr ? right->height : 0);
}

template <class T>
AVLTreeNode<T> *AVLTreeNode<T>::leftRotate()
{
    AVLTreeNode *r = right;
    right = right->left;
    r->left = this;

    this->updateHeight();
    r->updateHeight();
    return r
}

template <class T>
AVLTreeNode<T> * AVLTreeNode<T>::rightRotate()
{
    AVLTreeNode *l = left;
    left = left->right;
    l->right = this;
    
    this->updateHeight();
    l->updateHeight();
    return l;
}

template class AVLTreeNode<int>;
template class AVLTreeNode<short>;
template class AVLTreeNode<long>;
template class AVLTreeNode<long long>;
template class AVLTreeNode<std::string>;