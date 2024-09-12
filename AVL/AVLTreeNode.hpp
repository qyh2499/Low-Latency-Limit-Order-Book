#ifndef AVLTreeNode_hpp
#define AVLTreeNode_hpp

#include <string>
#include <algorithm>

template <class T>
struct AVLTreeNode
{
    AVLTreeNode *left;
    AVLTreeNode *right;
    const int key;
    T value;
    unsigned int height;

    AVLTreeNode(int key, T value);
    ~AVLTreeNode();
    void updateHeight();
    int getBalanceFactor();

    AVLTreeNode *leftRotate();
    AVLTreeNode *rightRotate();
    bool operator<(const AVLTreeNode<T> &other);
};

template <class T>
AVLTreeNode<T>::AVLTreeNode(int key, T value)
    : key(key), value(value), height(1), left(nullptr), right(nullptr)
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
    return (right != nullptr ? right->height : 0) - (left != nullptr ? left->height : 0);
}

template <class T>
AVLTreeNode<T> *AVLTreeNode<T>::leftRotate()
{
    AVLTreeNode *r = right;
    right = right->left;
    r->left = this;

    this->updateHeight();
    r->updateHeight();
    return r;
}

template <class T>
AVLTreeNode<T> *AVLTreeNode<T>::rightRotate()
{
    AVLTreeNode *l = left;
    left = left->right;
    l->right = this;

    this->updateHeight();
    l->updateHeight();
    return l;
}

template <class T>
bool AVLTreeNode<T>::operator<(const AVLTreeNode<T> &other)
{
    return key < other.key;
}

#endif
