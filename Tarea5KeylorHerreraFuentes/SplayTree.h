#ifndef SPLAYTREE_H
#define SPLAYTREE_H


#include <stdexcept>
#include <iostream>
#include "SNode.h"
#include "DLinkedList.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class SplayTree {
private:
    SNode<E> *root;
    SNode<E> *last;

    SNode<E>* insertAux(SNode<E> *current, E element) {
        if (current == nullptr) {
            SNode<E> *result = new SNode<E>(element);
            last = result;
            return result;
        }
        if (element == current->element) {
            last = current;
            throw runtime_error("Duplicated element.");
        }
        if (element < current->element) {
            current->left = insertAux(current->left, element);
            current->left->parent = current;
            return current;
        } else {
            current->right = insertAux(current->right, element);
            current->right->parent = current;
            return current;
        }
    }
    E findAux(SNode<E> *current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found.");
        last = current;
        if (element == current->element) {
            return current->element;
        }
        if (element < current->element)
            return findAux(current->left, element);
        else
            return findAux(current->right, element);
    }
    E* findPointerAux(SNode<E> *current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found.");
        last = current;
        if (element == current->element)
            return &(current->element);
        if (element < current->element)
            return findPointerAux(current->left, element);
        else
            return findPointerAux(current->right, element);
    }
    bool containsAux(SNode<E> *current, E element) {
        if (current == nullptr)
            return false;
        last = current;
        if (element == current->element)
            return true;
        if (element < current->element)
            return containsAux(current->left, element);
        else
            return containsAux(current->right, element);
    }
    SNode<E>* removeAux(SNode<E> *current, E element, E *result) {
        if (current == nullptr)
            throw runtime_error("Element not found.");
        if (element < current->element) {
            last = current;
            current->left = removeAux(current->left, element, result);
            if (current->left != nullptr)
                current->left->parent = current;
            return current;
        }
        if (element > current->element) {
            last = current;
            current->right = removeAux(current->right, element, result);
            if (current->right != nullptr)
                current->right->parent = current;
            return current;
        } else {
            // element == current->element;
            last = current->parent;
            *result = current->element;
            if (current->childrenCount() == 0) {
                delete current;
                return nullptr;
            }
            if (current->childrenCount() == 1) {
                SNode<E> *child = current->getUniqueChild();
                child->parent = current->parent;
                delete current;
                return child;
            } else {
                // current->childrenCount() == 2
                SNode<E> *successor = getSuccessor(current);
                swap(current, successor);
                current->right = removeAux(current->right, element, result);
                if (current->right != nullptr)
                    current->right->parent = current;
                return current;
            }
        }
    }
    SNode<E> *getSuccessor(SNode<E> *current) {
        SNode<E> *successor = current->right;
        while (successor->left != nullptr)
            successor = successor->left;
        return successor;
    }
    void swap(SNode<E> *n1, SNode<E> *n2) {
        E temp = n1->element;
        n1->element = n2->element;
        n2->element = temp;
    }
    void clearAux(SNode<E> *current) {
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }
    void getElementsAux(SNode<E> *current, List<E> *elements) {
        if (current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }
    int getSizeAux(SNode<E> *current) {
        if (current == nullptr)
            return 0;
        return 1 + getSizeAux(current->left) + getSizeAux(current->right);
    }
    int height(SNode<E> *current) {
        if (current == nullptr)
            return 0;
        int lh = height(current->left);
        int rh = height(current->right);
        return 1 + (lh > rh? lh : rh);
    }
    void rotateRight(SNode<E> *current) {
        if (current == nullptr)
            throw runtime_error("Can't rotate right a null tree.");
        if (current->left == nullptr)
            throw runtime_error("Can't rotate right with a null left child.");
        SNode<E> *temp = current->left;
        temp->parent = current->parent;
        current->left = temp->right;
        if (current->left != nullptr)
            current->left->parent = current;
        temp->right = current;
        current->parent = temp;
        if (current == root)
            root = temp;
        else if (temp->parent->right == current)
            temp->parent->right = temp;
        else
            temp->parent->left = temp;
    }
    void rotateLeft(SNode<E> *current) {
        if (current == nullptr)
            throw runtime_error("Can't rotate left a null tree.");
        if (current->right == nullptr)
            throw runtime_error("Can't rotate left with a null right child.");
        SNode<E> *temp = current->right;
        temp->parent = current->parent;
        current->right = temp->left;
        if (current->right != nullptr)
            current->right->parent = current;
        temp->left = current;
        current->parent = temp;
        if (current == root)
            root = temp;
        else if (temp->parent->right == current)
            temp->parent->right = temp;
        else
            temp->parent->left = temp;
    }
    void splay() {
        if (last == nullptr)
            return;
        SNode<E> *current = last;
        while (last != root) {
            if (current == root->left) {
                rotateRight(root);
                root->parent = nullptr;
            } else if (current == root->right) {
                rotateLeft(root);
                root->parent = nullptr;
            } else {
                SNode<E> *grand = current->parent->parent;
                if (grand->left != nullptr &&
                    grand->left->left == current) {
                    rotateRight(grand);
                    rotateRight(current->parent);
                } else if (grand->right != nullptr &&
                           grand->right->right == current) {
                    rotateLeft(grand);
                    rotateLeft(current->parent);
                } else if (grand->left != nullptr &&
                           grand->left->right == current) {
                    rotateLeft(current->parent);
                    rotateRight(grand);
                } else {
                    rotateRight(current->parent);
                    rotateLeft(grand);
                }
            }

        }
    }

public:
    SplayTree() {
        root = nullptr;
        last = nullptr;
    }
    ~SplayTree() {
        clear();
    }
    void insert(E element) {
        try {
            root = insertAux(root, element);
            root->parent = nullptr;
            splay();
        }
        catch (runtime_error &e) {
            splay();
            throw e;
        }
    }
    E find(E element) {
        try {
            E result = findAux(root, element);
            splay();
            return result;
        }
        catch (runtime_error &e) {
            splay();
            throw e;
        }
    }
    E* findPointer(E element) {
        try {
            E *result = findPointerAux(root, element);
            splay();
            return result;
        }
        catch (runtime_error &e) {
            splay();
            throw e;
        }
    }
    bool contains(E element) {
        bool result = containsAux(root, element);
        splay();
        return result;
    }
    E remove(E element) {
        try {
            E result;
            root = removeAux(root, element, &result);
            if (root != nullptr) root->parent = nullptr;
            splay();
            return result;
        }
        catch (runtime_error &e) {
            splay();
            throw e;
        }
    }
    void clear() {
        clearAux(root);
        root = nullptr;
    }
    List<E> *getElements() {
        List<E> *elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }
    int getSize() {
        return getSizeAux(root);
    }
    int getHeight() {
        return height(root);
    }
    void print() {
        List<E>* elements = getElements();
        elements->print();
        delete elements;
    }
};

#endif // SPLAYTREE_H
