#ifndef SNODE_H
#define SNODE_H

template <typename E>
class SNode {
public:
    SNode<E> *left;
    SNode<E> *right;
    SNode<E> *parent;
    E element;

    SNode(E element) {
        this->element = element;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    int childrenCount() {
        return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
    }
    SNode<E>* getUniqueChild() {
        return (left == nullptr? right : left);
    }
};

#endif // SNODE_H
