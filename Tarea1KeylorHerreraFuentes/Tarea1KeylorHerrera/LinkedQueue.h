#pragma once
#include <stdexcept>
#include <iostream>
#include "Queue.h"
#include "Node.h"

using namespace std;

template <typename E>
class LinkedQueue : public Queue<E>
{
private:
    Node<E>* front;
    Node<E>* back;
    int size;

public:
    LinkedQueue() {
        back = front = new Node<E>();
        size = 0;
    }

    ~LinkedQueue() {
        clear();
        delete front;
    }

    void enqueue(E element) override {
        back = back->next = new Node<E>(element);
        size++;
    }

    E dequeue() override {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        Node<E>* temp = front->next;
        front->next = temp->next;
        E result = temp->element;
        delete temp;
        if (size == 1)
            back = front;
        size--;
        return result;
    }

    E frontValue() override {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        return front->next->element;
    }

    void clear() override {
        while (front->next != nullptr) {
            Node<E>* temp = front->next;
            front->next = temp->next;
            delete temp;
        }
        back = front;
        size = 0;
    }

    bool isEmpty() override {
        return size == 0;
    }

    int getSize() override {
        return size;
    }

    void enqueueFront(E element) override {
        front->next = new Node<E>(element, front->next);
        if (size == 0)
            back = front->next;
        size++;
    }

    E dequeueBack() override {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        Node<E>* temp = front;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        E result = temp->next->element;
        delete temp->next;
        temp->next = nullptr;
        back = temp;
        size--;
        return result;
    }

    E backValue() override {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        return back->element;
    }

    void print() override {
        Node<E>* temp = front->next;
        cout << "[ ";
        while (temp != nullptr) {
            cout << temp->element << " ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }
};
