#pragma once

template <typename E>
class Node {
public:
    E element;
    Node* next;

    Node(E element, Node* next = nullptr) {
        this->element = element;
        this->next = next;
    }
};