#include <iostream>
#include "Node.h"

int main() {
    std::cout << "==== Test de la clase Node<char> ====" << std::endl;

    // Crear nodos individuales
    Node<char> n3('C');
    Node<char> n2('B', &n3);
    Node<char> n1('A', &n2);

    // Imprimir datos individuales
    std::cout << "n1: " << n1 << std::endl;
    std::cout << "n2: " << n2 << std::endl;
    std::cout << "n3: " << n3 << std::endl;

    // Recorrer la secuencia de nodos
    std::cout << "Recorriendo la lista enlazada: ";
    Node<char>* ptr = &n1;
    while (ptr != nullptr) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;

    std::cout << "==== Fin del test ====" << std::endl;
    return 0;
}

