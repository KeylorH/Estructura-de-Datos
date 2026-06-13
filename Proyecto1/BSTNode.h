#pragma once

/*	BSTNose programado por : Prof. Mauricio Avilés
*	Funciona como almacen de elementos para el AVLTree.
*/

template <typename E>
class BSTNode {
public:
	E element;
	BSTNode<E>* left;
	BSTNode<E>* right;

	BSTNode(E element, BSTNode<E>* left = nullptr, BSTNode<E>* right = nullptr) {
		this->element = element;
		this->left = left;
		this->right = right;
	}
	int childrenCount() {
		return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
	}
	BSTNode<E>* getOnlyChild() {
		return left == nullptr ? right : left;
	}
};