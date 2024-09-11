#include <iostream>
#include "../AVL/AVLTree.hpp"

int main(int argc, const char * argv[]) {
    AVLTree<int> tree;
    
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(6);
    tree.insert(5);
    tree.display();
    
    tree.remove(2);
    tree.remove(1);
    tree.remove(3);
    tree.display();
    
    return 0;
}