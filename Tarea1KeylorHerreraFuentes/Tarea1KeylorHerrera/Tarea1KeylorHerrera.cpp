#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include "ArrayQueue.h"
#include "LinkedQueue.h"

using namespace std;

int main() {
    srand(time(nullptr));

    int choice;
    do {
        cout << "Presione 1 para usar (ArrayQueue), 2 para (LinkedQueue): ";
        cin >> choice;

        Queue<int>* queue;
        if (choice == 1)
            queue = new ArrayQueue<int>();
        else if (choice == 2)
            queue = new LinkedQueue<int>();
        else {
            cout << "Opcion no valida. Intentelo de nuevo." << endl;
            continue;
        }

        int numOperations;
        cout << "Indique la cantidad de operaciones a realizar: ";
        cin >> numOperations;

        for (int i = 1; i <= numOperations; ++i) {
            int operation = rand() % 4;

            switch (operation) {
            case 0:
                // enqueue
                queue->enqueue(rand() % 1000);
                cout << i << ". enqueue(" << queue->backValue() << ")\n";
                break;
            case 1:
                // dequeueBack
                if (!queue->isEmpty()) {
                    cout << i << ". dequeueBack(): " << queue->dequeueBack() << "\n";
                }
                else {
                    cout << i << ". dequeueBack(): cola vacia.\n";
                }
                break;
            case 2:
                // enqueue
                queue->enqueue(rand() % 1000);
                cout << i << ". enqueue(" << queue->backValue() << ")\n";
                break;
            case 3:
                // dequeue
                if (!queue->isEmpty()) {
                    cout << i << ". dequeue(): " << queue->dequeue() << "\n";
                }
                else {
                    cout << i << ". dequeue(): cola vacia.\n";
                }
                break;
            }

            cout << " Cola: ";
            queue->print();
        }

        queue->clear();
        delete queue;

        cout << "Desea repetir la prueba? (1: Si / 0: No): ";
        cin >> choice;

    } while (choice != 0);

    return 0;
}
