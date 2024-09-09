#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <string>
#include <vector>
#include "Node.hpp"

template <class T>
class AVLTree
{

private:
    AVLTree<T> *root;
    int size;

    void balance(std::vector<Node<T> *> path);
    void display(Node<T> *cur, int depth = 0, int state = 0);


public:
    AVLTree();
    ~AVLTree();

    bool isEmpty() const;
    int getSize() const;

    // query and modify functions
    void insert(T value);
    void remove(T value);    
    int find(T value) const;
    int lower_bound(T value) const;
    int upper_bound(T value) const;

    const T &find_min() const;
    const T &find_max() const;
    const T &operator[](std::size_t idx) const;

    void display();
};

#endif
