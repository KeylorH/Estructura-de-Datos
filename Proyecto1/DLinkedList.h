#pragma once
#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

/*	DLinkedList modificado por : Flora
*	Lista que funciona con nodos en ambas direcciones;
*	Se le agregó el método containR() y se modificó
*	la forma de impresión.
*/

template <typename E>
class DLinkedList :  public List<E>
{
private:
	DNode<E>* head; // Inicio de la estructura
	DNode<E>* tail; // Final de la estructura
	DNode<E>* current; // Posicion del nodo actual
	int size;

public:
	// Constructor de la clase
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}
	// Destructor de la clase
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}
	// Inserta un elemento en la posición actual de la lista
	void insert(E element) {
		current->next = current->next->previous 
			= new DNode<E>(element, current->next, current);
		size++;
	}
	// Añade un elemenyo al final de la lista
	void append(E element) {
		tail->previous = tail->previous->next 
			= new DNode<E>(element, tail, tail->previous);
		size++;
	}
	// Cambia el elemento actual de la lista por otro
	void set(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
	// Elimina el elemento aactual de la lista
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		E result = current->next->element;
		current->next = current->next->next;
		delete current->next->previous;
		current->next->previous = current;
		size--;
		return result;
	}
	// Se limpia la lista, también se libera la memoria
	void clear() {
		while (head->next != tail) {
			head->next = head->next->next;
			delete head->next->previous;
		}
		current = tail->previous = head;
		size = 0;
	}
	// Se obtiene el elemento de la posición actual
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	// Current va a l inicio de la lista
	void goToStart() {
		current = head;
	}
	// Current va la final de la lista
	void goToEnd() {
		current = tail->previous;
	}
	// Current se vuelve la posicion solcitada
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out bounds.");
		current = head;
		for (int i = 0; i < pos; i++) {
			current = current->next;
		}
	}
	// Current avanza un espacio
	void next() {
		if (current != tail->previous)
			current = current->next;
	}
	// Current retrocede un espacio
	void previous() {
		if (current != head)
			current = current->previous;
	}
	// Verifica si current está al inicio
	bool atStart() {
		return current == head;
	}
	// Verifica si current está al final
	bool atEnd() {
		return current == tail->previous;
	}
	// Devuelve el tamaño actual de la lista
	int getSize() {
		return size;
	}
	// Obtiene la posicion actual en la lista
	int getPos() {
		// Elaborado por Alejandro Madrigal
		DNode<E>* temp = head;
		int i;
		for (i = 0; current != temp; i++)
			temp = temp->next;
		return i;
	}
	// Imprime lo contenido en la lista
	void print() {
		DNode<E>* temp = head->next;
		while (temp != tail) {
			cout << temp->element << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	// Busca un elemento 
	bool contains(E element) {
		goToStart();
		while (!atEnd()) {
			if (element == getElement()) {
				return true;
			}
			next();
		}
		return false;
	}
	// Busca um elemento y lo elimina
	bool containsR(E element) {
		goToStart();
		while (!atEnd()) {
			if (element == getElement()) {
				remove();
				return true;
			}
			next();
		}
		return false;
	}
};

