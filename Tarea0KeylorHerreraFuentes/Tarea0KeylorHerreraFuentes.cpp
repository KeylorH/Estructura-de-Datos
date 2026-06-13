#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include "ArrayStack.h"
#include "LinkedStack.h"

using namespace std;
// Función para obtener la precedencia de un operador
int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0; // Para cualquier otro carácter
}
// Función para evaluar expresiones matemáticas en notación infija
double evaluateInfixExpression(const string& infixExpression, Stack<double>& numbers, Stack<char>& operators) {
    for (size_t i = 0; i < infixExpression.length(); ++i) {
        if (isdigit(infixExpression[i])) {
            // Token es un número, leer el número completo
            string numberString;
            while (i < infixExpression.length() && (isdigit(infixExpression[i]) || infixExpression[i] == '.')) {
                numberString += infixExpression[i];
                ++i;
            }
            --i; // Retroceder para no saltarse el próximo carácter
            numbers.push(stod(numberString));
        }else if (infixExpression[i] == '(') {
            operators.push('(');
        }else if (infixExpression[i] == ')') {
            // Procesar operadores hasta encontrar un paréntesis izquierdo
            while (!operators.isEmpty() && operators.topValue() != '(') {
                char op = operators.pop();
                double b = numbers.pop();
                double a = numbers.pop();
                double result = 0.0;
                switch (op) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                case '^':
                    result = pow(a, b);
                    break;
                }
                numbers.push(result);
            }
            operators.pop(); // Eliminar el paréntesis izquierdo
        }else if (infixExpression[i] == '+' || infixExpression[i] == '-' || infixExpression[i] == '*' || infixExpression[i] == '/' || infixExpression[i] == '^') {
            // Token es un operador
            while (!operators.isEmpty() && precedence(operators.topValue()) >= precedence(infixExpression[i])) {
                char op = operators.pop();
                double b = numbers.pop();
                double a = numbers.pop();
                double result = 0.0;
                switch (op) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                case '^':
                    result = pow(a, b);
                    break;
                }
                numbers.push(result);
            }
            operators.push(infixExpression[i]);
        }
    }
    // Procesar los operadores restantes en la pila
    while (!operators.isEmpty()) {
        char op = operators.pop();
        double b = numbers.pop();
        double a = numbers.pop();
        double result = 0.0;
        switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '^':
            result = pow(a, b);
            break;
        }
        numbers.push(result);
    }
    // El resultado final debe estar en la cima de la pila de números
    return numbers.pop();
}

int main() {
    Stack<double>* numbers = nullptr;   // Puntero a la pila para almacenar números
    Stack<char>* operators = nullptr;   // Puntero a la pila para almacenar operadores

    int opcion;
    cout << "Seleccione el tipo de pila (1 para ArrayStack, 2 para LinkedStack): ";
    cin >> opcion;

    if (opcion == 1) {
        numbers = new ArrayStack<double>();
        operators = new ArrayStack<char>();
    }else if (opcion == 2) {
        numbers = new LinkedStack<double>();
        operators = new LinkedStack<char>();
    }else {
        cout << "Opcion no valida. Saliendo del programa." << endl;
        return 1;
    }
    cin.ignore();  // Limpiar el buffer del teclado

    string infixExpression;
    cout << "Ingrese la expresion matematica en notacion infija: ";
    getline(cin, infixExpression);

    try {
        double result = evaluateInfixExpression(infixExpression, *numbers, *operators);
        cout << "El resultado de la expresion es: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    // Liberar la memoria de las pilas
    delete numbers;
    delete operators;
    return 0;
}