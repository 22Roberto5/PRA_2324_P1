#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <iostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;  // Puntero al primer nodo
    int n;           // Número de elementos

public:
    // Constructor
    ListLinked() {
        first = nullptr;
        n = 0;
    }

    // Destructor
    ~ListLinked() {
        Node<T>* aux = first;
        while (aux != nullptr) {
            Node<T>* next = aux->next;
            delete aux;
            aux = next;
        }
    }

    // Inserta un elemento en la posición pos
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n)
            throw std::out_of_range("Posición inválida en insert()");

        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; i++)
                prev = prev->next;
            prev->next = new Node<T>(e, prev->next);
        }
        n++;
    }

    // Añade al final
    void append(T e) override {
        insert(n, e);
    }

    // Añade al principio
    void prepend(T e) override {
        insert(0, e);
    }

    // Elimina y devuelve el elemento en pos
    T remove(int pos) override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida en remove()");

        Node<T>* target;
        T elem;

        if (pos == 0) {
            target = first;
            elem = target->data;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; i++)
                prev = prev->next;
            target = prev->next;
            elem = target->data;
            prev->next = target->next;
        }

        delete target;
        n--;
        return elem;
    }

    // Devuelve el elemento en pos
    T get(int pos) const override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida en get()");

        Node<T>* curr = first;
        for (int i = 0; i < pos; i++)
            curr = curr->next;

        return curr->data;
    }

    // Busca el elemento y devuelve su posición
    int search(T e) const override {
        Node<T>* curr = first;
        int i = 0;
        while (curr != nullptr) {
            if (curr->data == e)
                return i;
            curr = curr->next;
            i++;
        }
        return -1;
    }

    // Indica si está vacía
    bool empty() const override {
        return n == 0;
    }

    // Devuelve el tamaño
    int size() const override {
        return n;
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        return get(pos);
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "[";
        Node<T>* curr = list.first;
        while (curr != nullptr) {
            out << curr->data;
            if (curr->next != nullptr)
                out << ", ";
            curr = curr->next;
        }
        out << "]";
        return out;
    }
};

#endif

