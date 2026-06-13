#include <iostream>
#include <cstdlib> // Para generacion de numeros aleatorios
#include <ctime> 
#include "ArrayList.h"
#include "LinkedList.h"
#include "DLinkedList.h"

using namespace std;

// Funcion para imprimir el menu de operaciones
void printMenu() {
    cout << "Operaciones disponibles:" << endl;
    cout << "1. Insertar elemento en la posicion actual" << endl;
    cout << "2. Agregar elemento al final" << endl;
    cout << "3. Eliminar elemento en la posicion actual" << endl;
    cout << "4. Limpiar lista" << endl;
    cout << "5. Obtener elemento en la posicion actual" << endl;
    cout << "6. Mover posicion actual al inicio de la lista" << endl;
    cout << "7. Mover posicion actual al final de la lista" << endl;
    cout << "8. Mover posicion actual a una posicion especifica" << endl;
    cout << "9. Mover a la posicion siguiente" << endl;
    cout << "10. Mover a la posicion anterior" << endl;
    cout << "11. Verificar si la posicion actual esta al inicio" << endl;
    cout << "12. Verificar si la posicion actual esta al final" << endl;
    cout << "13. Obtener la posicion actual" << endl;
    cout << "14. Obtener el tamano de la lista" << endl;
    cout << "15. Encontrar el indice de un elemento" << endl;
    cout << "16. Verificar si la lista contiene un elemento" << endl;
    cout << "17. Cargar la lista con numeros aleatorios" << endl;
    cout << "18. Salir" << endl;
}

// Funcion para ejecutar las operaciones seleccionadas por el usuario
template <typename ListType>
void performOperation(ListType* list, int choice) {
    int pos, value, index;
    switch (choice) {
    case 1:
        cout << "Ingrese el elemento a insertar: ";
        cin >> value;
        list->insert(value);
        break;
    case 2:
        cout << "Ingrese el elemento a agregar: ";
        cin >> value;
        list->append(value);
        break;
    case 3:
        try {
            value = list->remove();
            cout << "Elemento eliminado: " << value << endl;
        }
        catch (runtime_error& e) {
            cout << e.what() << endl;
        }
        break;
    case 4:
        list->clear();
        cout << "Lista limpiada." << endl;
        break;
    case 5:
        try {
            value = list->getElement();
            cout << "Elemento en la posicion actual: " << value << endl;
        }
        catch (runtime_error& e) {
            cout << e.what() << endl;
        }
        break;
    case 6:
        list->goToStart();
        cout << "Posicion actual movida al inicio." << endl;
        break;
    case 7:
        list->goToEnd();
        cout << "Posicion actual movida al final." << endl;
        break;
    case 8:
        cout << "Ingrese la posicion a la que desea moverse: ";
        cin >> pos;
        list->goToPos(pos);
        break;
    case 9:
        list->next();
        cout << "Movido a la posicion siguiente." << endl;
        break;
    case 10:
        list->previous();
        cout << "Movido a la posicion anterior." << endl;
        break;
    case 11:
        cout << (list->atStart() ? "La posicion actual esta al inicio." : "La posicion actual no esta al inicio.") << endl;
        break;
    case 12:
        cout << (list->atEnd() ? "La posicion actual esta al final." : "La posicion actual no esta al final.") << endl;
        break;
    case 13:
        pos = list->getPos();
        cout << "La posicion actual es: " << pos << endl;
        break;
    case 14:
        pos = list->getSize();
        cout << "El tamano de la lista es: " << pos << endl;
        break;
    case 15:
        cout << "Ingrese el elemento a buscar: ";
        cin >> value;
        index = list->indexOf(value);
        if (index != -1)
            cout << "El elemento esta en la posiciopn: " << index << endl;
        else
            cout << "El elemento no está en la lista." << endl;
        break;
    case 16:
        cout << "Ingrese el elemento a buscar: ";
        cin >> value;
        cout << (list->contains(value) ? "La lista contiene el elemento." : "La lista no contiene el elemento.") << endl;
        break;
    case 17:
        int numRandom;
        cout << "Ingrese la cantidad de numeros aleatorios a agregar: ";
        cin >> numRandom;
        srand(time(0)); // Semilla aleatoria
        for (int i = 0; i < numRandom; ++i) {
            value = rand() % 100; // Números aleatorios entre 0 y 99
            list->append(value);
        }
        cout << "Numeros aleatorios agregados." << endl;
        break;
    case 18:
        cout << "Saliendo del programa." << endl;
        break;
    default:
        cout << "Opcion no valida." << endl;
        break;
    }
}

int main() {
    int choice;
    List<int>* list = nullptr;

    cout << "Que tipo de lista desea utilizar?" << endl;
    cout << "1. ArrayList" << endl;
    cout << "2. LinkedList" << endl;
    cout << "3. DLinkedList" << endl;
    cout << "Indique aca la que desea utilizar: ";
    cin >> choice;

    switch (choice) {
    case 1:
        list = new ArrayList<int>();
        break;
    case 2:
        list = new LinkedList<int>();
        break;
    case 3:
        list = new DLinkedList<int>();
        break;
    default:
        cout << "Opcion no valida." << endl;
        return 0;
    }

    do {
        cout << "\nContenido de la lista: ";
        list->print();
        cout << "Posicion actual: " << list->getPos() << endl;

        printMenu();
        cout << "Ingrese el numero de la operacion que desea realizar: ";
        cin >> choice;

        if (choice != 18)
            performOperation(list, choice);

    } while (choice != 18);

    delete list;
    return 0;
}

