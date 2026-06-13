#pragma once
#include <iomanip>
#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;
using std::setw; 

template <typename E>
class Matrix
{
private:
    int rows;
    int columns;
    E** matrix;

public:
    Matrix(int rows, int columns) {
        if (rows <= 0 || columns <= 0)
            throw runtime_error("El numero de filas y columnas debe ser mayor que cero");
        this->rows = rows;
        this->columns = columns;
        matrix = new E * [rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new E[columns](); // Inicializar todos los elementos con el valor cero
        }
    }
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    E getValue(int row, int column) {
        if (row < 0 || row >= rows)
            throw runtime_error("Fila invalida");
        if (column < 0 || column >= columns)
            throw runtime_error("Columna invalida");
        return matrix[row][column];
    }
    void setValue(int row, int column, E value) {
        if (row < 0 || row >= rows)
            throw runtime_error("Fila invalida");
        if (column < 0 || column >= columns)
            throw runtime_error("Columna invalida");
        matrix[row][column] = value;
    }
    int getRows() {
        return rows;
    }
    int getColumns() {
        return columns;
    }

    void setAll(E value) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = value;
            }
        }
    }

    void transpose() {
        // Create a new matrix with transposed dimensions
        E** transposedMatrix = new E * [columns];
        for (int i = 0; i < columns; ++i) {
            transposedMatrix[i] = new E[rows];
        }
        // Fill the transposed matrix with values from the original matrix
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                transposedMatrix[j][i] = matrix[i][j];
            }
        }
        // Delete the original matrix
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        // Update rows and columns
        std::swap(rows, columns);
        // Update the matrix pointer to the transposed matrix
        matrix = transposedMatrix;
    }

    void addRow(E value) {
        // Create a new matrix with one additional row
        E** newMatrix = new E * [rows + 1];
        for (int i = 0; i < rows + 1; ++i) {
            newMatrix[i] = new E[columns];
        }
        // Copy existing data to the new matrix
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                newMatrix[i][j] = matrix[i][j];
            }
        }
        // Fill the new row with the specified value
        for (int j = 0; j < columns; ++j) {
            newMatrix[rows][j] = value;
        }
        // Delete the original matrix
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        // Update rows and matrix pointer
        ++rows;
        matrix = newMatrix;
    }

    void addColumn(E value) {
        // Transpose the matrix, add a row, then transpose back
        transpose();
        addRow(value);
        transpose();
    }

    void removeRow(int row) {
        if (row < 0 || row >= rows)
            throw runtime_error("Fila invalida");
        // Create a new matrix with one fewer row
        E** newMatrix = new E * [rows - 1];
        for (int i = 0; i < rows - 1; ++i) {
            newMatrix[i] = new E[columns];
        }
        // Copy existing data to the new matrix, skipping the specified row
        int newRow = 0;
        for (int i = 0; i < rows; ++i) {
            if (i != row) {
                for (int j = 0; j < columns; ++j) {
                    newMatrix[newRow][j] = matrix[i][j];
                }
                ++newRow;
            }
        }
        // Delete the original matrix
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        // Update rows and matrix pointer
        --rows;
        matrix = newMatrix;
    }

    void removeColumn(int col) {
        // Transpose the matrix, remove a row, then transpose back
        transpose();
        removeRow(col);
        transpose();
    }

    void print() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    // Imprime la matriz de forma mas ordenada entre columnas ( no hace falta para las filas, sin esto se veria fea la matriz :c )
    void printFormatted() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << setw(3) << matrix[i][j]; 
            }
            cout << endl;
        }
    }
};
