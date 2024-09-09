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
void AVLTree<T>::insert(T value)
{
    Node<T> *current = root;
    std::vector<Node<T> *> path;

    while (current != nullptr and current->value != value)
    {
        path.push_back(current);
        if (current->value > value)
            current = current->left;
        else
            current = current->right;
    }

    if (current != nullptr and current->value == value)
    {
        return; // The value already exist
    }

    Node<T> *newNode = new Node<T>(value);
    newNode->parent = current;
    path.push_back(newNode);

    balance(path);
    size++;
}

template <class T>
void AVLTree<T>::remove(T value)
{
    Node<T> *current = root;
    std::vector<Node<T> *> path;

    while (current != nullptr and current->value != value)
    {
        path.push_back(current);
        if (current->value > value)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr)
    {
        return; // The value does not exist
    }

    path.push_back(current);
    std::size_t index = path.size();
    Node **curParent = &(current->parent);
    Node **childSide = (*curParent)->value < current->value ? &((*curParent)->leftChild) : &((*curParent)->rightChild);

    if (current->right == nullptr) // No right children
    {
        

        if (current->left == nullptr) // No left children too
        {
            (*childSide) = nullptr;
        }
        else
        {
            (*childSide) = current->left;
        }

        delete current;
        path.pop_back();
    }
    else // Right child exists
    {
        Node<T> *successor = current->right;
        while (successor->left != nullptr)
        {
            path.push_back(successor);
            successor = successor->left;
        }

        if (successor == current->right)
        {
            successor->left = current->left;

            Node<T> *toRemove = *indirect;
            *indirect = *successor;
            delete toRemove;
        }

        else
        {
            AVLTreeNode<T> *tmp = *path.back(), *suc = *successor;

            tmp->left = (*successor)->right;
            suc->left = (*indirect)->left;
            suc->right = (*indirect)->right;

            delete *indirect;
            *indirect = suc;
            path[index] = &(suc->right);
        }
    }

    balance(path);
    size--;
}

template <class T>
void AVLTree<T>::balance(std::vector<Node<T> *> path)
{
    std::reverse(path.begin(), path.end()); // starting from the end

    for (auto current : path)
    {
        current->updateParams();

        if (current->getBalanceFactor() >= 2 and current->left->getBalanceFactor() >= 0) // left - left
        {
            current->rightRotate();
        }
        else if (current->getBalanceFactor() >= 2) // left - right
        {
            (current->left)->leftRotate();
            current->rightRotate();
        }
        else if (current->getBalanceFactor() <= -2 and current->right->getBalanceFactor() <= 0) // right - right
        {
            current->leftRotate();
        }
        else if (current->getBalanceFactor() <= -2) // right - left
        {
            (current->right)->rightRotate();
            current->leftRotate();
        }
    }
}

template <class T>
int AVLTree<T>::find(T value) const
{
    AVLTreeNode<T> *direct = root;
    int idx = 0;

    while (direct != nullptr and direct->value != value)
    {
        if (direct->value > value)
            direct = direct->left;
        else
        {
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }

    if (direct == nullptr)
        return -1;

    else
        return idx + (direct->left ? direct->left->count : 0);
}

template <class T>
int AVLTree<T>::upper_bound(T value) const
{
    AVLTreeNode<T> *direct = root;
    int idx = 0;

    while (direct != nullptr)
    {
        if (direct->value > value)
            direct = direct->left;
        else
        {
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }

    return idx;
}

template <class T>
int AVLTree<T>::lower_bound(T value) const
{
    AVLTreeNode<T> *direct = root;
    int idx = 0;

    while (direct != nullptr)
    {
        if (direct->value >= value)
            direct = direct->left;
        else
        {
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }

    return idx;
}

template <class T>
const T &AVLTree<T>::find_min() const
{
    AVLTreeNode<T> *cur = root;

    while (cur->left != nullptr)
        cur = cur->left;

    return cur->value;
}

template <class T>
const T &AVLTree<T>::find_max() const
{
    AVLTreeNode<T> *cur = root;

    while (cur->right != nullptr)
        cur = cur->right;

    return cur->value;
}

template <class T>
const T &AVLTree<T>::operator[](std::size_t idx) const
{
    AVLTreeNode<T> *cur = root;
    int left = cur->left != nullptr ? cur->left->count : 0;

    while (left != idx)
    {
        if (left < idx)
        {
            idx -= left + 1;

            cur = cur->right;
            left = cur->left != nullptr ? cur->left->count : 0;
        }

        else
        {
            cur = cur->left;
            left = cur->left != nullptr ? cur->left->count : 0;
        }
    }

    return cur->value;
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
void AVLTree<T>::display(AVLTreeNode<T> *cur, int depth, int state)
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