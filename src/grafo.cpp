#include "grafo.h"

double euclidean_distance(const Clareira& a, const Clareira& b) {
    return sqrt((a.x - b.x) * (a.y - b.y));
}

template<typename T>
Vetor<T>::Vetor() : size(0), capacity(2) {
    data = new T[capacity];
}

template<typename T>
Vetor<T>::~Vetor() {
    delete[] data;
}

template<typename T>
void Vetor<T>::push_back(const T& value) {
    if (size == capacity) {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[size++] = value;
}

template<typename T>
T& Vetor<T>::operator[](int index) {
    return data[index];
}

template<typename T>
int Vetor<T>::getSize() const {
    return size;
}

Grafo::Grafo(int n) : n(n), clareiras(), trilhas(), portais() {
    for (int i = 0; i < n; ++i) {
        trilhas.push_back(Vetor<Caminho>());
        portais.push_back(Vetor<Caminho>());
    }
}

void Grafo::adicionar_clareira(double x, double y) {
    Clareira clareira = {x, y};
    clareiras.push_back(clareira);
}

void Grafo::adicionar_trilha(int u, int v) {
    double weight = euclidean_distance(clareiras[u], clareiras[v]);
    trilhas[u].push_back({v, weight});
}

void Grafo::adicionar_portal(int u, int v) {
    portais[u].push_back({v, 0});
}

Vetor<Clareira>& Grafo::get_clareiras() {
    return clareiras;
}

Vetor<Vetor<Caminho>>& Grafo::get_trilhas() {
    return trilhas;
}

Vetor<Vetor<Caminho>>& Grafo::get_portais() {
    return portais;
}

// Explicitly instantiate templates for the types used in the project
template class Vetor<Clareira>;
template class Vetor<Caminho>;
template class Vetor<Vetor<Caminho>>;
