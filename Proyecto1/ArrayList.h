#pragma once

#define DEFAULT_MAX_SIZE 60000

#include <stdexcept>
#include <iostream>
#include "List.h"

using std::runtime_error;
using std::cout;
using std::endl;

/*	ArrayList modificado por : Flora
*	Usa un arreglo para manejar una lista;
*	se le agregó el método contains(), por lo
*	demás es igual al que se programó en clase.
*/

template <typename E>
class ArrayList : public List<E> {
protected:
	E* elements; // Puntero
	int max; // Máximo 
	int size; // Tamño
	int pos; // Posición

public:
	// Constructor de la clase
	ArrayList(int max = DEFAULT_MAX_SIZE) {
		elements = new E[max];
		this->max = max;
		size = pos = 0;
	}
	// Destructor de al clase
	~ArrayList() {
		delete[] elements;
	}
	// Inserta un elemento en la posción actual de la lista
	void insert(E element) {
		if (size == max)
			throw runtime_error("List is full.");
		for (int i = size; i > pos; i--) 
			elements[i] = elements[i - 1];
		elements[pos] = element;
		size++;
	}
	// Agrega un elemento al final de la lista
	void append(E element) {
		if (size == max)
			throw runtime_error("List is full.");
		elements[size] = element;
		size++;
	}
	// Cambia el elemento actual de la lista
	void set(E element) {
		if (pos == size)
			throw runtime_error("No current element.");
		elements[pos] = element;
	}
	// Elimina el elemento actual de la lista y lo devuelve
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (pos == size)
			throw runtime_error("No current element.");
		E result = elements[pos];
		for (int i = pos; i < size - 1; i++)
			elements[i] = elements[i + 1];
		size--;
		return result;
	}
	// Limpia el la lista
	void clear() {
		pos = size = 0;
	}
	// Obtiene el elemento de la posición actual
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (pos == size)
			throw runtime_error("No current element.");
		return elements[pos];
	}
	//Busca un elemento en el arreglo
	bool contains(E element) {
		for (int i = 0; i < size; i++) {
			if (element == elements[i])
				return true;
		}
		return false;
	}
	// Cambia la posición al inicio de la lista
	void goToStart() {
		pos = 0;
	}
	// Cambia la posición al final de la lista
	void goToEnd() {
		pos = size;
	}
	// Mueve la posición actual a la asignada
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds.");
		this->pos = pos;
	}
	// Avanza una posición
	void next() {
		if (pos < size)
			pos++;
	}
	// Retrocde una posición
	void previous() {
		if (pos > 0)
			pos--;
	}
	// Verifica si la posición actual es el incio de la lista
	bool atStart() {
		return pos == 0;
	}
	// Verifica si la posición actual es el final de la lista
	bool atEnd() {
		return pos == size;
	}
	// Obtiene el tamaño de la lista
	int getSize() {
		return size;
	}
	// Obtiene la posicón actual en la lista
	int getPos() {
		return pos;
	}
	// Imprime la lista
	void print() {
		cout << "[ ";
		for (int i = 0; i < size; i++)
			cout << elements[i] << " ";
		cout << "]" << endl;
	}
};

