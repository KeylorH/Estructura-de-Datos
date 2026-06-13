#pragma once
#include <stdexcept>
#include <iostream>
#include "Queue.h"

using namespace std;

template <typename E>
class ArrayQueue : public Queue<E>
{
private:
    E* elements;
    int front;
    int back;
    int size;
    int max;

public:
    static const int DEFAULT_MAX_SIZE = 100;

    ArrayQueue(int max = DEFAULT_MAX_SIZE) {
        elements = new E[max];
        front = back = size = 0;
        this->max = max;
    }

    ~ArrayQueue() {
        delete[] elements;
    }

    void enqueue(E element) override {
        if (size == max)
            throw runtime_error("Queue is full.");
        elements[back] = element;
        back = (back + 1) % max;
        size++;
    }

    E dequeue() override {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        front = (front + 1) % max;
        size--;
        return elements[(front + max - 1) % max];
    }

    E frontValue() override {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        return elements[front];
    }

    void clear() override {
        front = back = size = 0;
    }

    bool isEmpty() override {
        return size == 0;
    }

    int getSize() override {
        return size;
    }

    void enqueueFront(E element) override {
        if (size == max)
            throw runtime_error("Queue is full.");
        front = (front + max - 1) % max;
        elements[front] = element;
        size++;
    }

    E dequeueBack() override {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        back = (back + max - 1) % max;
        size--;
        return elements[back];
    }

    E backValue() override {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        return elements[(back + max - 1) % max];
    }

    void print() override {
        cout << "[ ";
        for (int i = front; i != back; i = (i + 1) % max) {
            cout << elements[i] << " ";
        }
        cout << "]" << endl;
    }
};