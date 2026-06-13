#pragma once
#include "ArrayList.h"
#include "AVLDictionary.h"

/*	TrieNode modificado por : Flora
*	Funciona como almacén para los elementos del trie.
*	Utiliza un AVLDictionary y se agregó una lista
*	para almacenar indices, además de dos méodos adicionales.
*/

class TrieNode {
private:
	bool isFinal; //Si el nodo es final de palabra
	int prefixCount; //Cuenta de prefijos
	ArrayList<int>* countUses; //Lista con indices
	Dictionary<char, TrieNode*>* children; //Hijos del nodo
public:
	// Constructor de la clase
	TrieNode() {
		isFinal = false;
		prefixCount = 0;
		countUses = nullptr;
		children = new AVLDictionary<char, TrieNode*>();
	}
	// Destructor de la clase
	~TrieNode() {
		if (countUses != nullptr)
			delete countUses;
		delete children;
	}
	// Revisa si el elemento es hijo del nodo
	bool containsChild(char c) {
		return children->contains(c);
	}
	// Devuelve el nodo hijo especificado
	TrieNode* getChild(char c) {
		return children->getValue(c);
	}
	// Inserta un hijo para el nodo
	void addChild(char c) {
		children->insert(c, new TrieNode());
	}
	// Elimina un hijo en específico
	void removeChild(char c) {
		children->remove(c);
	}
	// Devuelve una lista con los hijos del nodo
	List<char>* getChildren() {
		return children->getKeys();
	}
	//Añade el n° de línea a la lista (indices)
	void append(int line) { 
		this->countUses->append(line);
	}
	// Devuelve el estado de isFinal
	bool getFinal() {
		return isFinal;
	}
	// Cambia el estado de isFinal
	void setIsFinal(bool isFinal) {
		countUses = new ArrayList<int>();
		this->isFinal = isFinal;
	}
	// Devuelve la cuenta de prefijos
	int getPrefixCount() {
		return prefixCount;
	}
	// Cambia la cuenta de prefijos
	void setPrefixCount(int prefixCount) {
		this->prefixCount = prefixCount;
	}
	// Incrementa en 1 la cuenta de prefijos
	void increaseCount() {
		prefixCount++;
	}
	// Resta en 1 la cuenta de prefijos
	void decreaseCount() {
		prefixCount--;
	}
	// Devuelve el tamaño de countUses
	int getSizeCountUses() {
		return this->countUses->getSize();
	}
	// Devuelve la lista con los indices
	List<int>* getCountUses() {
		return this->countUses;
	}
};