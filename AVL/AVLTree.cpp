#include "AVLTree.hpp"

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
            node->right = node->right->rotateRight();
        }
        return node->rotateleft();
    }
    if (node->getBalanceFactor() == -2)
    {
        if (node->left->getBalanceFactor() > 0)
        {
            node->left = node->left->rotateleft();
        }
        return node->rotateright();
    }
    return node;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::insert(AVLTreeNode<T> *node, const T value)
{
    if (node == nullptr)
        return new AVLTreeNode<T>(value);
    if (value < node->value)
    {
        node->left = insert(node->left, value);
    }
    else
    {
        node->right = insert(node->right, value);
    }
    return balance(node);
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::findmin(AVLTreeNode<T> *node) // Find the leftmost in the node tree
{
    return node->left ? findmin(node->left) : node;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::removemin(AVLTreeNode<T> *node) // Remove the leftmost in the node tree
{
    if (node->left == nullptr)
        return node->right;
    node->left = removemin(node->left);
    return balance(node);
}


template <class T>
AVLTreeNode<T> *AVLTree<T>::remove(AVLTreeNode<T> *node, const T value) // Remove the value from the tree at node
{
    if (node == nullptr)
        return nullptr;
    if (value < node->value)
        node->left = remove(node->left, value);
    else if (k > p->key)
        node->right = remove(node->right, value);
    else //  value == node->value
    {
        AVLTreeNode<T> * l = node->left;
        AVLTreeNode<T> * r = node->right;
        delete node;
        if (r == nullptr){
            return l;
        }
        AVLTreeNode<T> *min = r->findmin();
        min->right = r->removemin();
        min->left = l;
        return balance(min);
    }
    return balance(node);
}


template <class T>
void AVLTree<T>::display()
{
    printf("\n");
    if (root != nullptr)
        display(root);
    else
        printf("Empty");
    printf("\n");
}

template <class T>
void AVLTree<T>::_display(AVLTreeNode<T> *cur, int depth, int state)
{ // state: 1 -> left, 2 -> right , 0 -> root
    if (cur->left)
        display(cur->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("┌───");
    else if (state == 2) // right
        printf("└───");

    std::cout << "[" << cur->value << "] - (" << cur->count << ", " << cur->height << ")" << std::endl;

    if (cur->right)
        display(cur->right, depth + 1, 2);
}

template class AVLTree<int>;
template class AVLTree<short>;
template class AVLTree<long>;
template class AVLTree<long long>;
template class AVLTree<std::string>;