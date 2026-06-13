#pragma once

#include <iostream>
#include "PriorityQueue.h"
#include "LinkedQueue.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedPriorityQueue : public PriorityQueue<E>
{
private:
	LinkedQueue<E>* queues;
	int size;
	int priorities; //Cantidad de prioridades

public: 
	LinkedPriorityQueue(int priorities) {
		queues = new LinkedQueue<E>[priorities]; //Arreglo de LinkedQueue
		this->priorities = priorities;
		size = 0;
	}
	~LinkedPriorityQueue() {
		delete[] queues;
	}
	void insert(E element, int priority) {
		if (priority < 0 || priority >= priorities)
			throw runtime_error("Invalid priority.");
		queues[priority].enqueue(element);
		size++;
	}
	E min() {
		if (size == 0)
			throw runtime_error("Priority queue is empty.");
		for (int i = 0; i < priorities; i++) {
			if (!queues[i].isEmpty())
				return queues[i].frontValue();
		}
		throw runtime_error("Queues are empty, and they should have elements.");
	}
	E removeMin() {
		if (size == 0)
			throw runtime_error("Priority queue is empty.");
		for (int i = 0; i < priorities; i++) {
			if (!queues[i].isEmpty()) {
				size--;
				return queues[i].dequeue();
			}
		}
		throw runtime_error("Queues are empty, and they should have elements.");
	}
	void clear() {
		for (int i = 0; i < priorities; i++) {
			queues[i].clear();
		}
	}
	int getSize() {
		return size;
	}
	bool isEmpty() {
		return size == 0;
	}
	void print() {
		for (int i = 0; i < priorities; i++) {
			cout << i << ": ";
			queues[i].print();
		}
	}
};

