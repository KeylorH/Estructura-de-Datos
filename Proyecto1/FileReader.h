#pragma once
#include <fstream> //Para leer los archivos
#include <string>
#include <sstream>
#include "ArrayList.h"
#include "DLinkedList.h"
#include "Trie.h"
#include "MaxHeap.h"
#include "KVPair.h"


using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::ifstream;
using std::istringstream;

/*	FileReader programado por : Flora y Carmen
*	Esta clase funciona con dos Tries, un ArrayList y un MaxHeap;
*	se encarga de leer los archivos y realizar diferentes consultas
*	con ellos, como busquedas (prefijo, palabra, etc.) y 
*	algunas estadisticas (Top y usos de palabras).
*/


class FileReader {
private:
	ArrayList<string> lines; // Estructura para almacenar las lineas del txt
	MaxHeap<KVPair<int, string>> heap; // Estructura para sacar el top
	Trie trieAux; // Trie para palabras a ignorar
	Trie mainTrie; // Trie para todo el texto


	// Limpia y corta las palabras y las inserta en el Trie
	void cleaningWord(string& word, int nLine) {
		string clean;
		for (char c : word) {
			if (isalpha(c) || c == 'á' || c == 'é' || c == 'í' || c == 'ó' || c == 'ú' || c == 'ñ' || c == 'ü' ||
				c == 'Á' || c == 'É' || c == 'Í' || c == 'Ó' || c == 'Ú' || c == 'Ñ' || c == 'Ü') {
				if (isupper(c))
					clean += tolower(c);
				else
					clean += c;
			}
			else {
				// Si encuentra algo que no es del alfabeto pero la cadena sigue llena, inserta lo que ya tenía y la vacía
				if (!clean.empty()) {
					mainTrie.insert(clean,nLine);
					clean.clear();
				}
			}
		}
		// Si la cadena seguía llena, inserta lo que ya tenía
		if (!clean.empty())
			mainTrie.insert(clean, nLine);
	}

	//Valida las entradas ingresadas por el usuario
	int niceEntrance(string selectionStr, int maxValue) {
		int eleccion = stoi(selectionStr);
		while (eleccion < 1 || eleccion > maxValue) {
			string eleccionString;
			cout << endl;
			cout << "Por favor ingrese un número valido: ";
			getline(cin, eleccionString);
			eleccion = stoi(eleccionString);
			cout << endl;
		}
		return eleccion;
	}

	// Hace minusculas las palabras
	void toLowercase(string& word) {
		for (char& c : word)
			c = tolower(c);
	}

	// Imprime las palabras a ignorar
	void printIgnoredWords() {
		cout << "Palabras a ignorar:" << endl;
		trieAux.print();
		cout << endl;
	}

	//Genera espacios por temas de estética 
	void jump() {
		for (int i = 0; i < 10; i++)
			cout << endl;
	}

public:

	// Opciones del programa, redirige a los demás métodos
	int options(){
		string eleccionString; // Elección del usuario
		string direccion; // Dirección del nuevo archivo
		string prefix; // Prefijo a buscar
		string word; // Palabra a buscar
		string num; // Cantidad de letras x palabra
		int cant;
		getline(cin, eleccionString);

		// Se revisa que la entrada esté entre las opciónes
		int eleccion = niceEntrance(eleccionString, 6);

		// Según la eleccion se redirige a los métodos
		switch (eleccion) {
		case 1:
			//Consultar por prefijo
			cout << endl;
			cout << "Digite el prefijo que desea buscar: ";
			getline(cin, prefix);
			cout << endl;
			if (prefix != "") {
				toLowercase(prefix);
				prefixMatches(prefix);
			}
			else
				cout << "< No se ha ingresado ningún prefijo >" << endl;
			jump();
			break;
		case 2:
			//Buscar palabra
			cout << endl;
			cout << "Digite la palabra que desea buscar: ";
			getline(cin, word);
			cout << endl;
			if (word != "") {
				toLowercase(word);
				// Método de busqueda
				searchWord(word);
			}
			else // Si no engresa nada, sale
				cout << "< No se ha ingresado ninguna palabra >" << endl;
			jump();
			break;
		case 3:
			//Busqueda por cantidad de letras. (Programado por: Carmen)
			cout << endl;
			cout << "Digite la cantidad de letras por palabra a buscar: ";
			getline(cin, num);
			cout << endl;
			cant = stoi(num);
			while (cant <= 0) {
				cout << endl;
				cout << "Digite un número valido, por favor.";
				getline(cin, num);
				cant = stoi(num);
			}
			// Método de busqueda
			searchByNumberOfLetters(cant);
			jump();
			break;
		case 4:
			//Palabras más utilizadas.
			cout << endl;
			if (heap.isEmpty()) {
				reader("ignorar.txt", 2); //Lee ignorar.txt e inserta en trieAux
				subOptions2(); //Redirige al menú 2
			}
			else {
				printIgnoredWords();
				subOptions2(); //Redirige al menú 2
			}
			jump();
			break;
		case 5: 
			//Cargar otro archivo
			cout << endl;
			cout << "< Borrando archivos anteriores... >" << endl;
			newFile(); // Borra todo lo almacenado
			cout << endl;

			// Pide el nuevo archivo
			cout << "Por favor, indique la ruta del archivo a analizar: ";
			getline(cin, direccion);
			eleccion = reader(direccion, 1);
			cout << endl;
			// Avisa si el archivo fue cargado con éxito
			if (eleccion != 6)
				cout << "--------- Archivo cargado exitosamente ---------" << endl;
			cout << endl;
			break;
		}
		return eleccion;
	}


	// Menú 2 de opciones, para el Top (Opción 4)
	void subOptions2() {
		//Presenta las opciones al usuario
		cout << "Opciones: " << endl;
		cout << "1. Ver top." << endl;
		cout << "2. Regresar." << endl;
		string eleccionString;
		cout << endl;
		cout << "Su elección: ";
		getline(cin, eleccionString);
		// Revisa que su elección sea un número valido
		int eleccion = niceEntrance(eleccionString, 2);

		//Enseña el top n palabras más usadas (opción 1)
		if (eleccion == 1) {
			cout << endl;
			// Pide el top
			cout << "Digite el número de palabras más usadas que desea ver: ";
			int top;
			cin >> top;
			cin.ignore();
			cout << endl;
			cout << "Top " << top << " palabras más usadas:" << endl;
			// Enseña el Top
			List <KVPair<int,string>>* list = heap.removeTop(top);
			for (list->goToStart(); !list->atEnd(); list->next()) {
				KVPair<int, string> pair = list->getElement();
				cout << pair.key << " " << pair.value << endl;
			}
			for (list->goToStart(); !list->atEnd(); list->next()) {
				KVPair<int, string> pair = list->getElement();
				heap.insert(pair);
			}
			cout << endl;
		}
		else { // Avisa que se va asalir del menú (opción 2)
			cout << endl;
			cout << "< Volviendo al menú principal >" << endl;
			cout << endl;
		}
	}


	// Lee el archivo, dependiendo de la ola, inserta en el trieAux o llama a processWord() para el mainTrie
	// Devuelve 6 si no abre el archivo o 0 si lo logró
	int reader(string direccion, int wave){
		ifstream file(direccion);
		cout << endl;
		// Si no se abre, avisa y sale
		if (!file.is_open()) {
			cout << "< No se pudo abrir el archivo. >";
			cout << endl;
			return 6;
		}
		else if (wave == 1 && file.is_open()){ // Avisa que está en proceso de cargar el archivo
			cout << "< Cargando archivo... >" << endl;
		}
		if (wave == 2) // Avisa que la lista se está generando si es ola 2
			cout << "< Generando lista... >" << endl;
		string line;

		bool seguro = (trieAux.getSize() == 0);

		// Por cada línea en el archivo
		while (getline(file, line)) {
			if (wave == 1) { // Si es la ola 1, las añade al ArrayList
				if (!line.empty()) 
					lines.append(line);
			}
			else { // Sino, añade las líneas directamente a trieAux
				if (seguro)
					trieAux.insert(line,0);
			}
		}		
		// Dependiendo de la ola: 1) Llena el mainTrie | 2) Llena el heap
		wave == 1 ? processWord() : topWords();
		return 0;
	}


	// Inserta las palabras en el mainTrie, las limpia antes de insertarlas
	void processWord() {
		string word;
		for (lines.goToStart(); !lines.atEnd(); lines.next()) {
			string line = lines.getElement();
			istringstream cutW(line); //Corta la palabra por espacios

			// Mientras hayan palabras en cutW
			string cleanW;
			while (cutW >> word) {
				cleaningWord(word, lines.getPos());
			}
		}
		lines.goToStart();
	}


	//Busca las palabras por prefijo (opción 1)
	void prefixMatches(string prefix) {
		// Lista de palabras
		List<string>* words = mainTrie.getMatches(prefix); 
		// Si no hubieron coincidencias, sale
		if (words->getSize() == 0) {
			cout << "< No hubieron coincidencias >" << endl;
			delete words;
			return;
		}
		//Lista de listas de punteros con la cantidad de usos de cada palabra
		List<List<int>*>* amount = mainTrie.getAmountOfUsesPrefix(prefix); 
		//Por cada palabra encontrada 
		for (words->goToStart(); !words->atEnd(); words->next()) {
			cout << words->getElement() << ": ";
			List<int>* lines = amount->getElement(); //Lista para leer las listas

			// Sacamos la cantidad de usos de la palabra (size)
			int size = lines->getSize(); 
			if (size == 1)
				cout << "1 uso." << endl;
			else
				cout << size << " usos." << endl;

			// Se imprimen las líneas en las que se usaban las palabra
			int j2 = -1;
			for (lines->goToStart(); !lines->atEnd(); lines->next()) { 
				int j = lines->getElement();
				//Evitar imprimir líneas repetidas por palabra (si se usaba varias veces en una misma línea)
				if (j2 != j) {
					cout << "Línea " << lines->getElement() + 1 << ":" << endl;
					cout << " '";
					this->lines.goToPos(j);
					cout << this->lines.getElement() <<"' " << endl;
				}
				j2 = j;
			}
			cout << endl;
			amount->next();
		}
		//liberamos la memoria
		delete words; 
		delete amount;
	}


	// Busca una palabra (Opcion 2)
	void searchWord(string word) {
		// Si l a palabra no está, sale
		if (!mainTrie.containsWord(word)) {
			cout << "< No hubieron coincidencias >" << endl;
			return;
		}
		else {
			// Mostramos la palabra y las veces que se usó
			cout << word << ": ";
			List<int>* line = mainTrie.getUsesList(word);
			int size = line->getSize();
			if (size == 1)
				cout << "1 uso." << endl;
			else
				cout << size << " usos." << endl;
			// Se imprimen las líneas en las que se usó la palabra
			int j2 = -1; // Variable para no repetir impresión
			for (line->goToStart(); !line->atEnd(); line->next()) {
				int j = line->getElement();
				//Evitar imprimir líneas repetidas por palabra (si se usaba varias veces en una misma línea)
				if (j2 != j) {
					cout << "Línea " << line->getElement() + 1 << ":" << endl;
					cout << " '";
					this->lines.goToPos(j);
					cout << this->lines.getElement() << "' " << endl;
				}
				j2 = j;
			}
			cout << endl;
		}
	}


	// Muestra las palabras con una cantidad de letras específica (opción 3) (Programdo por: Carmen)
	void searchByNumberOfLetters(int cant) {
		// Lista de palabras
		List<string>* words = mainTrie.searchByNumberOfLetters(cant);
		// Si no hubieron coincidencias, se enseña
		if (words->getSize() == 0) {
			cout << "< No hubieron coincidencias >" << endl;
			delete words;
			return;
		}
		//Lista de listas de punteros con la cantidad de usos de cada palabra
		List<List<int>*>* amount = mainTrie.getAOUSbNoL(cant);
		// Por cada palabra encontrada
		for (words->goToStart(); !words->atEnd(); words->next()) {
			cout << words->getElement() << ": ";
			List<int>* lines = amount->getElement(); // Lista para leer las listas

			// Sacamos la cantidad de usos de la palabra (size)
			int size = lines->getSize();
			if (size == 1)
				cout << "1 uso." << endl;
			else
				cout << size << " usos." << endl;

			// Se imprimen las líneas en las que se usaban las palabra
			int j2 = -1; // Variable para no repetir impresión
			for (lines->goToStart(); !lines->atEnd(); lines->next()) {
				int j = lines->getElement();
				//Evitar imprimir líneas repetidas por palabra (si se usaba varias veces en una misma línea)
				if (j2 != j) {
					cout << "Línea " << lines->getElement() + 1 << ":" << endl;
					cout << " '";
					this->lines.goToPos(j);
					cout << this->lines.getElement() << "' " << endl;
				}
				j2 = j;
			}
			cout << endl;
			amount->next();
		}
		//liberamos la memoria
		delete words;
		delete amount;
	}
	

	// Llena el heap para sacar el top (opción 4)
	void topWords() {
		 //Lista de todas las palabras del mainTrie
		List<string>* words = mainTrie.getMatches("");
		// Se inserta la lista en el heap
		words->atStart();
		while (!words->atEnd()) {
			string word = words->getElement();
			// Si no están dentro del trieAux las inserta
			if (!trieAux.containsWord(word)) {
				KVPair<int, string> key = KVPair<int, string>(mainTrie.getUsesNumber(word), word);
				heap.insert(key);
			}
			words->next();
		}
		printIgnoredWords();
		delete words;
	}


	// Vacía el mainTrie, lines, listAux y el Heap para cargar otro archivo (opción 5)
	void newFile() {
		mainTrie.clear();
		trieAux.clear();
		lines.clear();
		heap.clear();
	}
};