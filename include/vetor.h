#ifndef VETOR_H
#define VETOR_H

#include <iostream>

template<typename T>
class Vetor {
public:
    Vetor();
    Vetor(int initialSize);
    ~Vetor();
    Vetor(const Vetor& other); // Copy constructor
    Vetor& operator=(const Vetor& other); // Copy assignment
    Vetor(Vetor&& other) noexcept; // Move constructor
    Vetor& operator=(Vetor&& other) noexcept; // Move assignment

    void push_back(const T& value);
    T& operator[](int index);
    int getSize() const;

private:
    T* data;
    int size;
    int capacity;
    void resize(int newCapacity);
};

template<typename T>
Vetor<T>::Vetor() : data(new T[2]), size(0), capacity(2) {
   // std::cout << "Vetor inicializado com capacidade " << capacity << ".\n";
}

template<typename T>
Vetor<T>::Vetor(int initialSize) : data(new T[initialSize > 2 ? initialSize : 2]), size(0), capacity(initialSize > 2 ? initialSize : 2) {
    //std::cout << "Vetor inicializado com capacidade " << capacity << ".\n";
}

template<typename T>
Vetor<T>::~Vetor() {
//    std::cout << "Destruindo vetor de capacidade " << capacity << " e tamanho " << size << ".\n";
    delete[] data;
}

template<typename T>
Vetor<T>::Vetor(const Vetor& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
  //  std::cout << "Copiando vetor de capacidade " << capacity << " e tamanho " << size << ".\n";
}

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
    //    std::cout << "Atribuindo vetor de capacidade " << capacity << " e tamanho " << size << ".\n";
    }
    return *this;
}

template<typename T>
Vetor<T>::Vetor(Vetor&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
//    std::cout << "Movendo vetor de capacidade " << capacity << " e tamanho " << size << ".\n";
}

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
  //      std::cout << "Movendo atribuição de vetor de capacidade " << capacity << " e tamanho " << size << ".\n";
    }
    return *this;
}

template<typename T>
void Vetor<T>::push_back(const T& value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
    //std::cout << "Elemento adicionado, novo tamanho: " << size << ".\n";
}

template<typename T>
T& Vetor<T>::operator[](int index) {
//    std::cout << "Acessando elemento no índice " << index << ".\n";
    return data[index];
}

template<typename T>
int Vetor<T>::getSize() const {
  //  std::cout << "Obtendo tamanho do vetor: " << size << ".\n";
    return size;
}

template<typename T>
void Vetor<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
    //std::cout << "Vetor redimensionado para capacidade " << capacity << ".\n";
}

#endif // VETOR_H
