#pragma once
#include <stdexcept>
#include <iostream>
#include "BSTNode.h"
#include "DLinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

/*	AVLTree programado por : Prof. Mauricio Avilés
*	Un árbol que se mantiene balanceado;
*/

template <typename E>
class AVLTree {
private:
	AVLTree(const AVLTree<E>& other) {}
	void operator =(const AVLTree<E>& other) {}

	BSTNode<E>* root;

	BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return new BSTNode<E>(element);
		if (element == current->element)
			throw runtime_error("Duplicated element.");
		if (element < current->element) {
			current->left = insertAux(current->left, element);
			return rebalanceLeft(current);
		}
		else { // es mayor
			current->right = insertAux(current->right, element);
			return rebalanceRight(current);
		}
	}
	void findAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Element not found.");
		if (element == current->element)
			*result = current->element;
		else if (element < current->element)
			findAux(current->left, element, result);
		else
			findAux(current->right, element, result);
	}
	BSTNode<E>* removeAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Element not found.");
		if (element < current->element) {
			current->left = removeAux(current->left, element, result);
			return rebalanceRight(current);
		}
		if (element > current->element) {
			current->right = removeAux(current->right, element, result);
			return rebalanceLeft(current);
		}
		else { // element == current->element
			*result = current->element;
			int children = current->childrenCount();
			if (children == 0) {
				delete current;
				return nullptr;
			}
			if (children == 1) {
				BSTNode<E>* child = current->getOnlyChild();
				delete current;
				return child;
			}
			else { // children == 2
				BSTNode<E>* successor = getSuccessor(current);
				swap(current, successor);
				current->right = removeAux(current->right, element, result);
				return rebalanceLeft(current);
			}
		}
	}
	BSTNode<E>* getSuccessor(BSTNode<E>* current) {
		BSTNode<E>* successor = current->right;
		while (successor->left != nullptr)
			successor = successor->left;
		return successor;
	}
	void swap(BSTNode<E>* node1, BSTNode<E>* node2) {
		E temp = node1->element;
		node1->element = node2->element;
		node2->element = temp;
	}
	bool containsAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return false;
		if (element == current->element)
			return true;
		if (element < current->element)
			return containsAux(current->left, element);
		else
			return containsAux(current->right, element);
	}
	void clearAux(BSTNode<E>* current) {
		if (current == nullptr)
			return;
		clearAux(current->left);
		clearAux(current->right);
		delete current;
	}

	void getElementsAux(BSTNode<E>* current, List<E>* elements) {
		if (current == nullptr)
			return;
		getElementsAux(current->left, elements);
		elements->append(current->element);
		getElementsAux(current->right, elements);
	}
	int getSizeAux(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		return 1 + getSizeAux(current->left)
			+ getSizeAux(current->right);
	}
	BSTNode<E>* rotateLeft(BSTNode<E>* current) {
		if (current->right == nullptr)
			throw runtime_error("Can't left with null right child.");
		BSTNode<E>* temp = current->right;
		current->right = temp->left;
		temp->left = current;
		return temp;
	}
	BSTNode<E>* rotateRight(BSTNode<E>* current) {
		if (current->left == nullptr)
			throw runtime_error("Can't right with null left child.");
		BSTNode<E>* temp = current->left;
		current->left = temp->right;
		temp->right = current;
		return temp;
	}
	int heightAux(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		int leftHeight = heightAux(current->left);
		int rightHeight = heightAux(current->right);
		return 1 + (leftHeight > rightHeight? leftHeight : rightHeight);
	}
	BSTNode<E>* rebalanceLeft(BSTNode<E>* current) {
		if (current == nullptr) 
			return current;
		if (current->left == nullptr && current->right == nullptr)
			return current;
		int lh = heightAux(current->left);
		int rh = heightAux(current->right);
		if (lh - rh > 1) {
			int llh = heightAux(current->left->left);
			int lrh = heightAux(current->left->right);
			if (llh >= lrh)
				return rotateRight(current);
			else {
				current->left = rotateLeft(current->left);
				return rotateRight(current);
			}
		}
		return current;
	}
	BSTNode<E>* rebalanceRight(BSTNode<E>* current) {
		if (current == nullptr)
			return current;
		if (current->left == nullptr && current->right == nullptr)
			return current;
		int rh = heightAux(current->right);
		int lh = heightAux(current->left);
		if (rh - lh > 1) {
			int rrh = heightAux(current->right->right);
			int rlh = heightAux(current->right->left);
			if (rrh >= rlh)
				return rotateLeft(current);
			else {
				current->right = rotateRight(current->right);
				return rotateLeft(current);
			}
		}
		return current;
	}

public:
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
		clear();
	}
	void insert(E element) {
		root = insertAux(root, element);
	}
	E find(E element) {
		E result;
		findAux(root, element, &result);
		return result;
	}
	E remove(E element) {
		E result;
		root = removeAux(root, element, &result);
		return result;
	}
	bool contains(E element) {
		return containsAux(root, element);
	}
	void clear() {
		clearAux(root);
		root = nullptr;
	}
	List<E>* getElements() {
		List<E>* elements = new DLinkedList<E>();
		getElementsAux(root, elements);
		return elements;
	}
	int getSize() {
		return getSizeAux(root);
	}
	void print() {
		List<E>* elements = getElements();
		elements->print();
		delete elements;
	}
	int height() {
		return heightAux(root);
	}
};
