
#ifndef Node_hpp
#define Node_hpp

#include <string>
#include <algorithm>

template <class T>
struct AVLTreeNode
{
    AVLTreeNode *parent;
    AVLTreeNode *left;
    AVLTreeNode *right;
    const T value;

    int childrenCount;
    int height;

    AVLTreeNode(T value);
    ~AVLTreeNode();
    void updateParams();
    int getBalanceFactor();

    void leftRotate();
    void rightRotate();
};

#endif
