#include "Node.hpp"

template <class T>
AVLTreeNode<T>::AVLTreeNode(T value)
	: value(value), childrenCount(1), height(1), parent(nullptr), left(nullptr), right(nullptr)
{
}

template <class T>
AVLTreeNode<T>::~AVLTreeNode()
{
}

template <class T>
void AVLTreeNode<T>::updateParams()
{
	count = (left != nullptr ? left->count : 0) + (right != nullptr ? right->count : 0) + 1;
	height = std::max(left != nullptr ? left->height : 0, right != nullptr ? right->height : 0) + 1;
}

template <class T>
int AVLTreeNode<T>::getBalanceFactor()
{
	return (left != nullptr ? left->height : 0) - (right != nullptr ? right->height : 0);
}

template <class T>
void AVLTreeNode<T>::leftRotate()
{
	AVLTreeNode * r = right;
	
	// Shift left branch of rightChild to rightChild
	right = right->left;
	if (right != nullptr) {
		right->parent = this;
	}

	// Shift current to the left branch of original rightChild
	r->left = this;
	r->parent = parent;
	parent = r;

	this->updateValues();
	r->updateValues();
}

template <class T>
void AVLTreeNode<T>::rightRotate()
{
	AVLTreeNode * l = left;
	
	// Shift right branch of leftChild to leftChild
	left = left->right;
	if (left != nullptr) {
		left->parent = this;
	}

	// Shift current to the left branch of original rightChild
	l->right = this;
	l->parent = parent;
	parent = l;

	this->updateValues(); // the order is important
	l->updateValues();
}

template class AVLTreeNode<int>;
template class AVLTreeNode<short>;
template class AVLTreeNode<long>;
template class AVLTreeNode<long long>;
template class AVLTreeNode<std::string>;
