#pragma once
#define DEFAULT_MAX_SIZE 60000

#include <stdexcept>
#include <iostream>
#include "ArrayList.h"

using std::runtime_error;
using std::cout;
using std::endl;

/*	MaxHeap programado por : Flora
*	Esta clase funciona con un arreglo que ordena de forma
*	descendete los elementos que contiene un árbol.
*/

template <typename E>
class MaxHeap
{
private:
	E* elements;
	int max;
	int size;

	MaxHeap(const MaxHeap<E>& other) {}
	void operator =(const MaxHeap<E>& other) {}

	// Ordena los elementos de la litsa de mayor a menor
	void siftUp(int pos) {
		while (pos != 0 && elements[pos] > elements[parent(pos)]) { // No raíz y que yo siga siendo mayor que mi padre
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}
	// Ordena los elementos de la lista de mayor a menor
	void siftDown(int pos) {
		while (!isLeaf(pos) && elements[pos] < elements[maxChild(pos)]) { // Si no soy hoja y soy menor que el mayor de mis hijos
			int mChild = maxChild(pos);
			swap(pos, mChild);
			pos = mChild;
		}
	}
	// Obtiene la posición del padre
	int parent(int pos) {
		return (pos - 1) / 2;
	}
	// Ontiene la posicón del hijo izquierdo
	int leftChild(int pos) {
		return 2 * pos + 1;
	}
	// Obtiene la posición del hijo derecho
	int rightChild(int pos) {
		return 2 * pos + 2;
	}
	// Obtiene la posición del mayor de los hijos
	int maxChild(int pos) {
		if (rightChild(pos) >= size
			|| elements[leftChild(pos)] > elements[rightChild(pos)]) {
			return leftChild(pos);
		}
		return rightChild(pos);
	}
	// Revisa si es una hoja
	bool isLeaf(int pos) {
		return leftChild(pos) >= size;
	}
	// Intercambia el lugar de dos elmentos
	void swap(int pos1, int pos2) {
		E temp = elements[pos1];
		elements[pos1] = elements[pos2];
		elements[pos2] = temp;
	}

public:
	// Constructor de la clase
	MaxHeap(int max = DEFAULT_MAX_SIZE) {
		elements = new E[max]; //Puntero a arreglo de E elementos
		size = 0;
		this->max = max;
	}
	// Destructor de la clase
	~MaxHeap() {
		delete[] elements;
	}
	// Inserta un elmento en el heap
	void insert(E element) {
		if (size == max)
			throw runtime_error("Heap is full.");
		elements[size] = element;
		size++;
		siftUp(size - 1);
	}
	// Devuelve el primer elmeento del heap
	E first() {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		return elements[0];
	}
	// Elimina el elemento más grande del heap
	E removeFirst() {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		return remove(0);
	}
	// Elimina un elemento del heap usando la posición
	E remove(int pos) {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		if (pos < 0 || pos >= size)
			throw runtime_error("Index out of bounds.");
		swap(pos, size - 1);
		size--;
		siftDown(0);
		return elements[size];
	}
	// Convierte un arreglo en un MaxHeap
	void heapify(E* arr, int n) {
		if (n > max || n < 0)
			throw runtime_error("Index out of bounds.");
		size = n;
		for (int i = 0; i < n; i++) {
			elements[i] = arr[i];
		}
		int j = size;
		while (j != 0) {
			siftDown(j - 1);
			j--;
		}
	}
	// Une dos heap en uno solo
	void merge(MaxHeap<E>* other) {
		int disponible = max - size;
		if (other->size > disponible)
			throw runtime_error("The current Heap does't support the merge. Limit exced.");
		for (int i = 0; i < other->size; i++)
			insert(other->elements[i]);
	}
	// Elimina los n elementos con más valor del heap
	List<E>* removeTop(int n) {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		if (n > max)
			throw runtime_error("Index out of bounds.");
		List<E>* lista = new ArrayList<E>(n);
		for (int i = 0; i < n; i++)
			lista->append(removeFirst());
		return lista;
	}
	// Limpia la lista
	void clear() {
		size = 0;
	}
	// Obtiene el tamaño del heap
	int getSize() {
		return size;
	}
	// Revisa si el tamaño del heap es 0
	bool isEmpty() {
		return size == 0;
	}
	// Imprime los elmentos en el heap
	void print() {
		cout << "[ ";
		for (int i = 0; i < size; i++) {
			cout << elements[i] << " ";
		}
		cout << "]" << endl;
	}
};

