#include <iostream>
#include <iomanip> // Para manipulación de salida con setw
#include <cstdlib> // Para generar numeros aleatorios
#include "Matrix.h" // Asumiendo que el archivo de la clase Matrix se llama Matrix.h

using namespace std;

int main() {
    int rows, columns;
    cout << "Ingrese las dimensiones de la matriz (filas columnas): ";
    cin >> rows >> columns;

    // Crear una matriz con dimensiones dadas e inicialmente llena de ceros
    Matrix<int> matrix(rows, columns);
    cout << "\nMatriz inicial:" << endl;
    matrix.printFormatted();; // Imprimir la matriz inicial

    int choice;
    do {
        cout << endl;
        cout << "Seleccione una opcion: " << endl;
        cout << "1. Obtener valor (getValue)" << endl;
        cout << "2. Asignar valor (setValue)" << endl;
        cout << "3. Obtener cantidad de filas (getRows)" << endl;
        cout << "4. Obtener cantidad de columnas (getColumns)" << endl;
        cout << "5. Asignar valor a todas las celdas (setAll)" << endl;
        cout << "6. Transponer matriz (transpose)" << endl;
        cout << "7. Agregar fila (addRow)" << endl;
        cout << "8. Agregar columna (addColumn)" << endl;
        cout << "9. Eliminar fila (removeRow)" << endl;
        cout << "10. Eliminar columna (removeColumn)" << endl;
        cout << "11. Cargar matriz con numeros aleatorios" << endl;
        cout << "12. Salir" << endl;
        cout << "\nOpcion: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int row, col;
            cout << "\nIngrese la fila y la columna para obtener el valor: ";
            cin >> row >> col;
            try {
                cout << "\nEl valor en la posicion (" << row << ", " << col << ") es: " << matrix.getValue(row, col) << endl;
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 2: {
            int row, col, value;
            cout << "\nIngrese la fila, la columna y el valor a asignar: ";
            cin >> row >> col >> value;
            try {
                matrix.setValue(row, col, value);
                cout << "\nValor asignado correctamente.\n" << endl;
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            matrix.printFormatted();
            break;
        }
        case 3: {
            cout << "\nCantidad de filas: " << matrix.getRows() << endl;
            break;
        }
        case 4: {
            cout << "\nCantidad de columnas: " << matrix.getColumns() << endl;
            break;
        }
        case 5: {
            int value;
            cout << "\nIngrese el valor para asignar a todas las celdas: ";
            cin >> value;
            matrix.setAll(value);
            cout << "\nTodos los valores asignados correctamente.\n" << endl;
            matrix.printFormatted();
            break;
        }
        case 6: {
            matrix.transpose();
            cout << "\nMatriz transpuesta:\n" << endl;
            matrix.printFormatted();
            break;
        }
        case 7: {
            int value;
            cout << "\nIngrese el valor para la nueva fila: ";
            cin >> value;
            matrix.addRow(value);
            cout << "\nNueva fila agregada correctamente.\n" << endl;
            matrix.printFormatted();
            break;
        }
        case 8: {
            int value;
            cout << "\nIngrese el valor para la nueva columna: ";
            cin >> value;
            matrix.addColumn(value);
            cout << "\nNueva columna agregada correctamente.\n" << endl;
            matrix.printFormatted();
            break;
        }
        case 9: {
            int row;
            cout << "\nIngrese el numero de fila a eliminar: ";
            cin >> row;
            try {
                matrix.removeRow(row);
                cout << "\nFila eliminada correctamente.\n" << endl;
                matrix.printFormatted();
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 10: {
            int col;
            cout << "\nIngrese el numero de columna a eliminar: ";
            cin >> col;
            try {
                matrix.removeColumn(col);
                cout << "\nColumna eliminada correctamente.\n" << endl;
                matrix.printFormatted();
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 11: {
            // Cargar matriz con numeros aleatorios del 0 al 99
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    matrix.setValue(i, j, rand() % 100);
                }
            }
            cout << "\nMatriz cargada con numeros aleatorios del 0 al 99.\n" << endl;
            matrix.printFormatted();
            break;
        }
        case 12: {
            cout << "\nSaliendo del programa..." << endl;
            break;
        }
        default: {
            cout << "\nOpcion invalida. Por favor, seleccione una opcion valida.\n" << endl;
        }
        }
    } while (choice != 12);

    return 0;
}
