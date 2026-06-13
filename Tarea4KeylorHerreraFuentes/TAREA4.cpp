#include <iostream>
#include <ctime>
#include "MinHeap.h"

using namespace std;

int main() {
    try {
        srand(static_cast<unsigned int>(time(0))); // Initialize seed for random numbers

        int numElements;
        cout << "Ingrese la cantidad de elementos para insertar en dos heaps: ";
        cin >> numElements;

        if (numElements <= 0) {
            throw runtime_error("El numero de elementos debe ser positivo.");
        }

        // Create two heaps
        MinHeap<int> heap1(numElements * 2); // Ensure sufficient space for fusion
        MinHeap<int> heap2(numElements * 2);

        // Insert random items into heaps
        for (int i = 0; i < numElements; i++) {
            int value = rand() % 100; // Generate a random number between 0 and 99
            heap1.insert(value);
            value = rand() % 100;
            heap2.insert(value);
        }

        // Print heap content
        cout << "Contenido del primer heap: ";
        heap1.print();
        cout << "Contenido del segundo heap: ";
        heap2.print();

        // Merge the second heap into the first
        heap1.merge(&heap2);

        // Print content of first heap after merge
        cout << "Contenido del primer heap despues de la fusion: ";
        heap1.print();

        int n;
        cout << "Ingrese un entero para calcular el top n del primer heap: ";
        cin >> n;

        if (n <= 0) {
            throw runtime_error("El numero debe ser positivo.");
        }

        // Get and print the top n elements from the first heap
        list<int>* topElements = heap1.removeTop(n);
        cout << "Top " << n << " elementos del primer heap: [ ";
        for (int elem : *topElements) {
            cout << elem << " ";
        }
        cout << "]" << endl;
        delete topElements; // Free dynamic memory

        // Print the rest of the content of the first heap
        cout << "Resto del primer heap despues de removeTop: ";
        while (!heap1.isEmpty()) {
            cout << heap1.removeFirst() << " ";
        }
        cout << endl;

        // Request a new quantity of items to test heapify
        int newSize;
        cout << "Ingrese otra cantidad de elementos para probar el metodo heapify: ";
        cin >> newSize;

        if (newSize <= 0) {
            throw runtime_error("El numero de elementos debe ser positivo.");
        }

        int* newArray = new int[newSize];
        for (int i = 0; i < newSize; i++) {
            newArray[i] = rand() % 100; // Generate random numbers
        }

        // Test the heapify method on the first heap
        heap1.heapify(newArray, newSize);
        delete[] newArray; // Free dynamic memory

        // Print heap content after heapify
        cout << "Contenido del heap despues de heapify: ";
        heap1.print();

        // Print the top of all the elements in the heap
        topElements = heap1.removeTop(heap1.getSize());
        cout << "Todos los elementos del heap despues de heapify: [ ";
        for (int elem : *topElements) {
            cout << elem << " ";
        }
        cout << "]" << endl;
        delete topElements; // Free dynamic memory
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

