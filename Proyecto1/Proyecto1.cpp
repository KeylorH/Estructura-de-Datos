#include <iostream>
#include <string>
#include "Trie.h"
#include "windows.h"
#include "FileReader.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;


/*	Main programado por : Flora
*	Principalmente funciona con un FileReader;
*	Lanza un programa que analisa y lee archivos 
*	.txt y realiza con ellos diferentes operaciones.
*/


// Enseña el menú de opciones del programa
void menu() {
	cout << "<< Ingrese el número correspondiente a la operación deseada a realizar >>" << endl;
	cout << endl;
	cout << "Menú:" << endl;
	cout << "1. Consultar por prefijo." << endl;
	cout << "2. Buscar palabra." << endl;
	cout << "3. Busqueda por cantidad de letras." << endl;
	cout << "4. Palabras más utilizadas." << endl;
	cout << "5. Cargar otro archivo." << endl;
	cout << "6. Salir." << endl;
	cout << endl;
	cout << "Su eleccion: ";
}	

// Inicia el programa de lectura y análisis de archivos
int main() { 
	setlocale(LC_ALL, "spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	int eleccion = 0;
	
	FileReader analista; // El programa
	
	//Pequeña introducción
	cout << "------------------ Bienvenido al analista de archivos ------------------" << endl;
	cout << "  Este programa está diseñado para analizar sus archivos de texto, " << endl;
	cout << "  realizar consultas y obtener información relevenate." << endl;
	cout << endl;

	// Se pide la ruta del archivo
	string direccion;
	cout << "Por favor, indique la ruta del archivo a analizar: ";
	getline(cin, direccion);

	// Se manda al programa, (Abrió: 0 | No abrió: 6)
	eleccion = analista.reader(direccion,1);

	// Si logró abrirse correctamente, avisa
	cout << endl;
	if (eleccion != 6)
		cout << "--------- Archivo cargado exitosamente ---------" << endl;
	cout << endl;
	
	// Si logró abrirse correctamente, muestra el menú y las opciones
	while (eleccion != 6) {
		menu();
		try {
			// Este método devuelve el número de opción seleccionada
			eleccion = analista.options();
		}catch (const std::exception& e) {
			// Si ocurre un error muestra el error y continúa 
			cout << endl;
			std::cerr << e.what() << endl;
			cout << endl;
		}
	}
	cout << endl;
	// Avisa que el programa finalizó
	cout << "--------- Programa finalizado ---------" << endl;
	return 0;
}
