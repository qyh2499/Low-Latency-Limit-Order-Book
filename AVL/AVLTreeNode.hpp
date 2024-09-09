#ifndef AVLTreeNode_hpp
#define AVLTreeNode_hpp

#include <string>
#include <algorithm>

template <class T>
struct AVLTreeNode
{
    AVLTreeNode *left;
    AVLTreeNode *right;
    const T value;
    unsigned int height;
 
    AVLTreeNode(T value);
    ~AVLTreeNode();
    void updateHeight();
    int getBalanceFactor();

    AVLTreeNode * leftRotate();
    AVLTreeNode * rightRotate();
};

#endif
