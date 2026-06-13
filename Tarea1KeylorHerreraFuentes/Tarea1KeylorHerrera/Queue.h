#pragma once

template <typename E>
class Queue
{
public:
    Queue() {}
    virtual ~Queue() {}
    virtual void enqueue(E element) = 0;
    virtual E dequeue() = 0;
    virtual E frontValue() = 0;
    virtual void clear() = 0;
    virtual bool isEmpty() = 0;
    virtual int getSize() = 0;
    virtual void enqueueFront(E element) = 0;
    virtual E dequeueBack() = 0;
    virtual E backValue() = 0;
    virtual void print() = 0;
};
