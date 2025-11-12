#ifndef LISTARRAY_H
#define LISTARRAY_H

#include "List.h"
#include <stdexcept>

template <typename T>
class ListArray : public List<T> {
private:
    T* arr;                      // Array dinámico
    int max;                     // Capacidad actual
    int n;                       // Número de elementos reales
    static const int MINSIZE = 2; // Capacidad mínima

    // Redimensiona el array
    void resize(int newSize) {
        if (newSize < MINSIZE) newSize = MINSIZE;
        T* newArr = new T[newSize];
        for (int i = 0; i < n; ++i)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        max = newSize;
    }

public:
    // Constructor
    ListArray() {
        arr = new T[MINSIZE];
        max = MINSIZE;
        n = 0;
    }

    // Destructor
    ~ListArray() { delete[] arr; }

    // Inserta un elemento en una posición
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n)
            throw std::out_of_range("Posición inválida");
        if (n == max)
            resize(max * 2);

        for (int i = n; i > pos; --i)
            arr[i] = arr[i - 1];

        arr[pos] = e;
        n++;
    }

    // Añade al final (usa insert)
    void append(T e) override { insert(n, e); }

    // Añade al principio (usa insert)
    void prepend(T e) override { insert(0, e); }

    // Elimina y devuelve el elemento de una posición
    T remove(int pos) override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida");

        T elem = arr[pos];
        for (int i = pos; i < n - 1; ++i)
            arr[i] = arr[i + 1];
        n--;

        // Si queda poca ocupación, reducimos tamaño
        if (n < max / 4)
            resize(max / 2);

        return elem;
    }

    // Devuelve el elemento en una posición
    T get(int pos) const override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida");
        return arr[pos];
    }

    // Busca un elemento (devuelve índice o -1)
    int search(T e) const override {
        for (int i = 0; i < n; ++i)
            if (arr[i] == e)
                return i;
        return -1;
    }

    // Indica si está vacía
    bool empty() const override { return n == 0; }

    // Devuelve número de elementos
    int size() const override { return n; }
};

#endif
