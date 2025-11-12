#ifndef LISTARRAY_H
#define LISTARRAY_H

#include "List.h"
#include <stdexcept>
#include <ostream>  // Para std::ostream en operator<<

template <typename T>
class ListArray : public List<T> {
private:
    T* arr;                      // Puntero al array
    int max;                     // Capacidad actual del array
    int n;                       // Número de elementos almacenados
    static const int MINSIZE = 2; // Capacidad mínima

    // Redimensiona el array al nuevo tamaño
    void resize(int new_size) {
        if (new_size < MINSIZE)
            new_size = MINSIZE;

        T* new_arr = new T[new_size];
        for (int i = 0; i < n; ++i)
            new_arr[i] = arr[i];

        delete[] arr;
        arr = new_arr;
        max = new_size;
    }

public:
    // Constructor por defecto
    ListArray() {
        arr = new T[MINSIZE];
        max = MINSIZE;
        n = 0;
    }

    // Destructor
    ~ListArray() {
        delete[] arr;
    }

    // Inserta un elemento en una posición específica
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n)
            throw std::out_of_range("Posición inválida en insert()");
        if (n == max)
            resize(max * 2); // Duplicar capacidad si está lleno

        for (int i = n; i > pos; --i)
            arr[i] = arr[i - 1];

        arr[pos] = e;
        n++;
    }

    // Añade un elemento al final
    void append(T e) override {
        insert(n, e);
    }

    // Añade un elemento al principio
    void prepend(T e) override {
        insert(0, e);
    }

    // Elimina y devuelve el elemento de una posición
    T remove(int pos) override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida en remove()");

        T elem = arr[pos];
        for (int i = pos; i < n - 1; ++i)
            arr[i] = arr[i + 1];

        n--;

        // Reducir tamaño si está muy vacío
        if (n < max / 4)
            resize(max / 2);

        return elem;
    }

    // Devuelve el elemento en una posición
    T get(int pos) const override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida en get()");
        return arr[pos];
    }

    // Busca un elemento, devuelve índice o -1
    int search(T e) const override {
        for (int i = 0; i < n; ++i)
            if (arr[i] == e)
                return i;
        return -1;
    }

    // Indica si está vacía
    bool empty() const override {
        return n == 0;
    }

    // Devuelve el número de elementos
    int size() const override {
        return n;
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida en operator[]");
        return arr[pos];
    }

    // Sobrecarga global del operador <<
    friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list) {
        out << "[";
        for (int i = 0; i < list.n; ++i) {
            out << list.arr[i];
            if (i < list.n - 1)
                out << ", ";
        }
        out << "]";
        return out;
    }
};

#endif

