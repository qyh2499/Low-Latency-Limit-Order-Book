#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "AVLTreeNode.hpp"

template <class T>
class AVLTree
{

private:
    AVLTreeNode<T> *root;
    AVLTreeNode<T> *minNode;
    AVLTreeNode<T> *maxNode;
    std::unordered_map<int, AVLTreeNode<T> *> nodeMap;
    int size;

    AVLTreeNode<T> *balance(AVLTreeNode<T> *node);
    AVLTreeNode<T> *findMin(AVLTreeNode<T> *node);
    AVLTreeNode<T> *findMax(AVLTreeNode<T> *node);
    AVLTreeNode<T> *removeMin(AVLTreeNode<T> *node);
    AVLTreeNode<T> *insertHelper(AVLTreeNode<T> *node, AVLTreeNode<T> *newNode);
    AVLTreeNode<T> *removeHelper(AVLTreeNode<T> *node, const int key);
    void _display(AVLTreeNode<T> *cur, int depth = 0, int state = 0);

public:
    AVLTree();
    ~AVLTree();

    bool isEmpty() const;
    int getSize() const;
    AVLTreeNode<T> *getMinNode() const;
    AVLTreeNode<T> *getMaxNode() const;
    AVLTreeNode<T> *find(int key) const;

    // query and modify functions
    void insert(const int key, const T value);
    void remove(const int key);
    void display();
};

template <class T>
AVLTree<T>::AVLTree() : root(nullptr), size(0), maxNode(nullptr), minNode(nullptr)
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
AVLTreeNode<T> *AVLTree<T>::getMinNode() const
{
    return minNode;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::getMaxNode() const
{
    return maxNode;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::find(int key) const
{
    if (nodeMap.find(key) == nodeMap.end())
    {
        return nullptr;
    }
    return nodeMap.at(key);
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
AVLTreeNode<T> *AVLTree<T>::insertHelper(AVLTreeNode<T> *node, AVLTreeNode<T> *newNode)
{
    if (node == nullptr)
    {
        return newNode;
    }
    if (newNode->key < node->key)
    {
        node->left = insertHelper(node->left, newNode);
    }
    else
    {
        node->right = insertHelper(node->right, newNode);
    }
    return balance(node);
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::findMin(AVLTreeNode<T> *node) // Find the leftmost in the node tree
{
    return node->left ? findMin(node->left) : node;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::findMax(AVLTreeNode<T> *node) // Find the rightmost in the node tree
{
    return node->right ? findMax(node->right) : node;
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
AVLTreeNode<T> *AVLTree<T>::removeHelper(AVLTreeNode<T> *node, const int key) // Remove the key from the tree at node
{
    if (node == nullptr)
        return nullptr;
    if (key < node->key)
        node->left = removeHelper(node->left, key);
    else if (key > node->key)
        node->right = removeHelper(node->right, key);
    else //  key == node->key
    {
        // Remove from tree
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
        printf("---- ");
    else if (state == 2) // right
        printf("---- ");

    std::cout << "[" << cur->key << "] - (";
    cur->value.printInfoString();
    std::cout << ")" << std::endl;

    if (cur->right)
        _display(cur->right, depth + 1, 2);
}

// PUBLIC FUNCTIONS

template <class T>
void AVLTree<T>::insert(const int key, const T value)
{
    if (nodeMap.find(key) == nodeMap.end()) // Only insert unique elements
    {
        AVLTreeNode<T> *newNode = new AVLTreeNode<T>(key, value);

        // Insert into tree
        root = insertHelper(root, newNode);

        // Update other references
        if (maxNode == nullptr || key > maxNode->key)
        {
            maxNode = newNode;
        }
        if (minNode == nullptr || key < minNode->key)
        {
            minNode = newNode;
        }
        nodeMap.emplace(key, newNode);
    }
}

template <class T>
void AVLTree<T>::remove(const int key)
{
    int maxKey = maxNode->key;
    int minKey = minNode->key;

    // Remove from tree
    root = removeHelper(root, key);

    // Remove from references
    if (root == nullptr)
    {
        maxNode = nullptr;
        minNode = nullptr;
    }
    else
    {
        if (key == maxKey)
        {
            maxNode = findMax(root);
        }
        if (key == minKey)
        {
            minNode = findMin(root);
        }
    }
    nodeMap.erase(key);
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
