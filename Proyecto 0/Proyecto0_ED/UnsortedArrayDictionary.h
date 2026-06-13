#ifndef UNSORTEDARRAYDICTIONARY_H
#define UNSORTEDARRAYDICTIONARY_H

#include <stdexcept>
#include "ArrayList.h"
#include "DLinkedList.h"
#include "KVPair.h"
#include "Dictionary.h"

using std::runtime_error;

template <typename K, typename V>
class UnsortedArrayDictionary : public Dictionary<K, V> {
private:
    ArrayList<KVPair<K, V>> *pairs;

    void checkNotExisting(K key) {
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            if (key == p.key)
                throw runtime_error("Duplicated key.");
        }
    }
    // no sólo revisa que exista, también deja la posición
    // actual apuntando al valor buscado
    void checkExisting(K key) {
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            if (key == p.key)
                return;
        }
        throw runtime_error("Key not found.");
    }

public:
    UnsortedArrayDictionary(int max = DEFAULT_MAX_SIZE) {
        pairs = new ArrayList<KVPair<K, V>>(max);
    }
    ~UnsortedArrayDictionary() {
        delete pairs;
    }
    void insert(K key, V value) {
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        pairs->append(p);
    }
    V remove(K key) {
        checkExisting(key);
        KVPair<K, V> p = pairs->remove();
        return p.value;
    }
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = pairs->getElement();
        return p.value;
    }
    void setValue(K key, V value) {
        checkExisting(key);
        KVPair<K, V> p(key, value);
        pairs->set(p);        
    }
    bool contains(K key) {
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            if (key == p.key)
                return true;
        }
        return false;
    }
    List<K>* getKeys() {
        List<K> *keys = new DLinkedList<K>();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            keys->append(p.key);
        }
        return keys;
    }
    List<V>* getValues() {
        List<V> *values = new DLinkedList<V>();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            values->append(p.value);
        }
        return values;
    }
    int getSize() {
        return pairs->getSize();
    }
    void print() {
        pairs->print();
    }
};

#endif // UNSORTEDARRAYDICTIONARY_H
