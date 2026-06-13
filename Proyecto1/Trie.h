#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "TrieNode.h"
#include "DLinkedList.h"

using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

/*	Trie modificado por : Flora y Carmen
*	Funciona como un gran árbol que almacena TrieNodes;
*	Se usa AVLDictionary como diccionario, por ser eficiente
*	en la busqueda de elementos, se agregaron varios métodos.
*/

class Trie {
private:
	TrieNode* root; //Raíz del trie

	// Devuelve el último nodo de una palabra
	TrieNode* findNode(string word) {
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			if (!current->containsChild(word[i]))
				return nullptr;
			current = current->getChild(word[i]);
		}
		return current;
	}
	// Elimina todos los nodos usados en el Trie
	void clearAux(TrieNode* current) {
		List<char>* children = current->getChildren();
		children->goToStart();
		while (!children->atEnd()) {
			char c = children->getElement();
			TrieNode* child = current->getChild(c);
			clearAux(child);
			children->next();
		}
		delete children;
		delete current;
	}
	// Añade las palabras que coincidan con el prefijo
	// a la lista enviada 
	void getMatchesAux(TrieNode* current, string prefix, List<string>* words) {
		if (current->getFinal())
			words->append(prefix);
		List<char>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			char c = children->getElement();
			getMatchesAux(current->getChild(c), prefix + c, words);
		}
		delete children;
	}
	// Añade las listas de indices de las palabras en la lista
	// enviada
	void getAOUAux(TrieNode* current, List<List<int>*>* amount) {
		if (current->getFinal()) {
			List<int>* nLines = current->getCountUses();
			amount->append(nLines);
		}
		List<char>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			char c = children->getElement();
			getAOUAux(current->getChild(c), amount);
		}
		delete children;
	}
	// Añade las palabras que cumplan con el número de letras solicitado
	// a la lista enviada
	void auxSearchByNumberOfLetters(TrieNode* current, int n, List<string>* words, string word) {
		if (!current->getFinal() && n == 0) {
			return;
		}
		if (current->getFinal() && n == 0) {
			words->append(word);
			return;
		}
		List<char>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			char c = children->getElement();
			auxSearchByNumberOfLetters(current->getChild(c), n - 1, words, word + c);
		}
		delete children;
	}
	// Añade las listas de indices de las palabras en la lista
	// enviada
	void getAOUSbNoLAux(TrieNode* current, int n, List<List<int>*>* amount) {
		if (!current->getFinal() && n == 0) {
			return;
		}
		if (current->getFinal() && n == 0) {
			List<int>* nLines = current->getCountUses();
			amount->append(nLines);
			return;
		}
		List<char>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			char c = children->getElement();
			getAOUSbNoLAux(current->getChild(c), n - 1, amount);
		}
		delete children;
	}

public:
	// Constructor de la clase
	Trie() {
		root = new TrieNode();
	}
	// Destructor de la clase
	~Trie() {
		clear();
		delete root;
	}
	// Inserta un elemento en el Trie
	void insert(string word , int nline) {
		TrieNode* current = root;
		if (containsWord(word)) {
			current = findNode(word);
			current->append(nline);
			return;
		}
		for (unsigned int i = 0; i < word.size(); i++) {
			current->increaseCount();
			if (!current->containsChild(word[i]))
				current->addChild(word[i]);
			current = current->getChild(word[i]);
		}
		current->increaseCount();
		current->setIsFinal(true);
		current->append(nline);
	}
	// Revisa que la palabra emviada exista
	// en el Trie
	bool containsWord(string word) {
		TrieNode* current = findNode(word);
		if (current == nullptr) return false;
		return current->getFinal();
	}
	// Revisa que el prefijo enviado exista
	// en el Trie
	bool containsPrefix(string prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return false;
		return true;
	}
	// Devuelve la cantidad de usos de un prefijo
	int prefixCount(string prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return 0;
		return current->getPrefixCount();
	}
	// Elimina una palabra del Trie
	void remove(string word) {
		if (!containsWord(word))
			throw runtime_error("Word not found.");
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			current->decreaseCount();
			TrieNode* child = current->getChild(word[i]);
			if (child->getPrefixCount() == 1)
				current->removeChild(word[i]);
			if (current->getPrefixCount() == 0)
				delete current;
			current = child;
		}
		current->decreaseCount();
		current->setIsFinal(false);
		if (current->getPrefixCount() == 0)
			delete current;
	}
	// Limpia el Trie
	void clear() {
		clearAux(root);
		root = new TrieNode();
	}
	// Devuelve un puntero a una lista con palabras que
	// coincidieron con el prefijo enviado
	List<string>* getMatches(string prefix) {
		DLinkedList<string>* words = new DLinkedList<string>();
		TrieNode* current = findNode(prefix);
		if (current != nullptr)
			getMatchesAux(current, prefix, words);
		return words;
	}
	// Obtiene la lista de palabras con el # de letras especificado [Carmen]
	List<string>* searchByNumberOfLetters(int n) {
		List<string>* words = new DLinkedList<string>();
		TrieNode* current = root;
		string word = "";
		if (current != nullptr)
			auxSearchByNumberOfLetters(current, n, words, word);
		return words;
	}
	// Devuelve un puntero, de una lista de punteros, que apuntan
	// a las listas de indices de las palabras
	List<List<int>*>* getAOUSbNoL(int n) {
		List<List<int>*>* amount = new DLinkedList<List<int>*>();
		TrieNode* current = root;
		if (current != nullptr)
			getAOUSbNoLAux(current, n, amount);
		return amount;
	}
	// Devuelve un puntero, de una lista de punteros, que apuntan
	// a las listas de indices de las palabras que contengan el prefijo
	List<List<int>*>* getAmountOfUsesPrefix(string prefix) {
		List<List<int>*>* amount = new DLinkedList<List<int>*>();
		TrieNode* current = findNode(prefix);
		if (current != nullptr)
			getAOUAux(current, amount);
		return amount;
	}
	// Devuelve la lista de indices de una palabra
	List<int>* getUsesList(string word) {
		TrieNode* current = findNode(word);
		List<int>* uses = current->getCountUses();
		return uses;
	}
	// Devuelve la cantidad de usos de una palabra
	int getUsesNumber(string word) {
		TrieNode* current = findNode(word);
		return current->getSizeCountUses();
	}
	// Devuelve el tamaño del Trie
	int getSize() {
		return root->getPrefixCount();
	}
	// Imprime las palabras del Trie
	void print() {
		List<string>* words = new DLinkedList<string>();
		words = getMatches("");
		words->print();
		delete words;
	}
};

