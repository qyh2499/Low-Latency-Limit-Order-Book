#include <iostream>
#include "../AVL/AVLTree.hpp"

int main(int argc, const char * argv[]) {
    AVLTree<int> tree;
    
    tree.insert(1, 1);
    tree.insert(2, 1);
    tree.insert(3, 1);
    tree.insert(4, 1);
    std::cerr << tree.getMaxNode()->key << "\n";
    tree.insert(6, 1);
    tree.insert(5, 1);
    std::cerr << tree.getMaxNode()->key << "\n";
    tree.display();
    
    tree.remove(2);
    tree.remove(1);
    std::cerr << tree.getMinNode()->key << "\n";
    tree.remove(3);
    tree.display();
    
    return 0;
}