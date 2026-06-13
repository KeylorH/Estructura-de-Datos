#pragma once

#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>
#include "Stack.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayStack : public Stack<E> {
private:
    E* elements;
    int max;
    int top;

public:
    ArrayStack(int max = 1024) {
        elements = new E[max];
        this->max = max;
        top = 0;
    }
    ~ArrayStack() {
        delete[] elements;
    }
    void push(E element) {
        if (top == max) {
            E* temp = new E[max * 2];
            for (int i = 0; i < top; i++)
                temp[i] = elements[i];
            delete[] elements;
            elements = temp;
            max *= 2;
        }
        elements[top] = element;
        top++;
    }
    E pop() {
        if (top == 0) {
            throw runtime_error("Stack underflow.");
        }
        top--;
        return elements[top];
    }
    E topValue() {
        if (top == 0) {
            throw runtime_error("Stack is empty.");
        }
        return elements[top - 1];
    }
    void clear() {
        top = 0;
    }
    bool isEmpty() {
        return top == 0;
    }
    int getSize() {
        return top;
    }
    void print() {
        cout << "[ ";
        for (int i = top - 1; i >= 0; i--) {
            cout << elements[i] << " ";
        }
        cout << "]" << endl;
    }
};