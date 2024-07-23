#ifndef VETOR_H
#define VETOR_H

#include <iostream>
// Classe template PriorityQueue para armazenar elementos com prioridades associadas
/* Esse arquivo nao esta modularizado por conta do uso de template,quando tentei passar ele pra .cpp ou .tpp
a compilacao nao rodou, e depois de uma consultas vi que o compilador nao consegue entender os arquivos separadamente
justamente por conta do template.
*/
// Classe template Vetor para armazenar elementos de qualquer tipo T
template<typename T>
class Vetor {
public:
    // Construtores e destrutores
    Vetor(); // Construtor padrão
    Vetor(int initialSize); // Construtor com tamanho inicial
    Vetor(int initialSize, const T& defaultValue); // Construtor com tamanho inicial e valor padrão
    ~Vetor(); // Destrutor
    Vetor(const Vetor& other); // Construtor de cópia
    Vetor& operator=(const Vetor& other); // Operador de atribuição por cópia
    Vetor(Vetor&& other) noexcept; // Construtor de movimentação
    Vetor& operator=(Vetor&& other) noexcept; // Operador de atribuição por movimentação

    // Métodos para manipulação do vetor
    void push_back(const T& value); // Adiciona um elemento no final
    void pop_back(); // Remove o último elemento
    T& operator[](int index); // Acesso ao elemento por índice (não constante)
    const T& operator[](int index) const; // Acesso ao elemento por índice (constante)
    int getSize() const; // Retorna o tamanho atual do vetor

private:
    T* data; // Ponteiro para os dados armazenados
    int size; // Tamanho atual do vetor
    int capacity; // Capacidade máxima do vetor
    void resize(int newCapacity); // Redimensiona a capacidade do vetor
};

// Implementações dos métodos

// Construtor padrão: inicializa o vetor com capacidade 2 e tamanho 0
template<typename T>
Vetor<T>::Vetor() : data(new T[2]), size(0), capacity(2) {
}

// Construtor com tamanho inicial: inicializa o vetor com a capacidade especificada ou 2, o que for maior
template<typename T>
Vetor<T>::Vetor(int initialSize) 
    : data(new T[initialSize > 2 ? initialSize : 2]), 
      size(0), 
      capacity(initialSize > 2 ? initialSize : 2) {
}

// Construtor com tamanho inicial e valor padrão: inicializa o vetor e preenche com o valor padrão
template<typename T>
Vetor<T>::Vetor(int initialSize, const T& defaultValue) 
    : data(new T[initialSize]), 
      size(initialSize), 
      capacity(initialSize) {
    for (int i = 0; i < size; ++i) {
        data[i] = defaultValue;
    }
}

// Destrutor: libera a memória alocada
template<typename T>
Vetor<T>::~Vetor() {
    delete[] data;
}

// Construtor de cópia: copia os dados de outro vetor
template<typename T>
Vetor<T>::Vetor(const Vetor& other) 
    : data(new T[other.capacity]), 
      size(other.size), 
      capacity(other.capacity) {
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// Operador de atribuição por cópia: copia os dados de outro vetor
template<typename T>
Vetor<T>& Vetor<T>::operator=(const Vetor& other) {
    if (this != &other) {
        delete[] data;
        data = new T[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Construtor de movimentação: transfere os dados de outro vetor
template<typename T>
Vetor<T>::Vetor(Vetor&& other) noexcept 
    : data(other.data), 
      size(other.size), 
      capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// Operador de atribuição por movimentação: transfere os dados de outro vetor
template<typename T>
Vetor<T>& Vetor<T>::operator=(Vetor&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

// Adiciona um elemento no final do vetor, redimensionando se necessário
template<typename T>
void Vetor<T>::push_back(const T& value) {
    if (size == capacity) {
        resize(2 * capacity);
    }
    data[size++] = value;
}

// Remove o último elemento do vetor, se houver elementos
template<typename T>
void Vetor<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

// Acesso ao elemento por índice (não constante)
template<typename T>
T& Vetor<T>::operator[](int index) {
    return data[index];
}

// Acesso ao elemento por índice (constante)
template<typename T>
const T& Vetor<T>::operator[](int index) const {
    return data[index];
}

// Retorna o tamanho atual do vetor
template<typename T>
int Vetor<T>::getSize() const {
    return size;
}

// Redimensiona a capacidade do vetor
template<typename T>
void Vetor<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

#endif // VETOR_H
