#ifndef QUEUE_H
#define QUEUE_H

#include "vetor.h"
#include <stdexcept>
/* Esse arquivo nao esta modularizado por conta do uso de template,quando tentei passar ele pra .cpp ou .tpp
a compilacao nao rodou, e depois de uma consultas vi que o compilador nao consegue entender os arquivos separadamente
justamente por conta do template.
*/
// Classe template PriorityQueue para armazenar elementos com prioridades associadas
template<typename T, typename Priority>
class PriorityQueue {
public:
    PriorityQueue(); // Construtor padrão
    void push(const T& value, Priority priority, int portaisUsados, int maxPortais); // Adiciona um elemento com prioridade
    T pop(); // Remove e retorna o elemento com a menor prioridade
    bool isEmpty() const; // Verifica se a fila está vazia
    void decreaseKey(const T& value, Priority newPriority); // Diminui a prioridade de um elemento

private:
    // Estrutura Element para armazenar um valor e sua prioridade
    struct Element {
        T value;
        Priority priority;
        int portaisUsados;
    };

    Vetor<Element> data; // Vetor para armazenar os elementos
    int findElementIndex(const T& value) const; // Encontra o índice de um elemento
    void heapifyUp(int index); // Reorganiza a heap para cima
    void heapifyDown(int index); // Reorganiza a heap para baixo
};

// Implementações dos métodos

// Construtor padrão: inicializa a fila de prioridade
template<typename T, typename Priority>
PriorityQueue<T, Priority>::PriorityQueue() : data() {}

// Adiciona um elemento com prioridade na fila e reorganiza a heap
template<typename T, typename Priority>
void PriorityQueue<T, Priority>::push(const T& value, Priority priority, int portaisUsados, int maxPortais) {
    if (portaisUsados > maxPortais) {
        return; // Não adiciona o elemento se o número de portais usados for maior que o máximo permitido
    }
    Element element = {value, priority, portaisUsados};
    data.push_back(element);
    heapifyUp(data.getSize() - 1);
}

// Remove e retorna o elemento com a menor prioridade da fila
template<typename T, typename Priority>
T PriorityQueue<T, Priority>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("A fila de prioridade está vazia");
    }
    T minValue = data[0].value;
    data[0] = data[data.getSize() - 1];
    data.pop_back();
    heapifyDown(0);
    return minValue;
}

// Verifica se a fila está vazia
template<typename T, typename Priority>
bool PriorityQueue<T, Priority>::isEmpty() const {
    return data.getSize() == 0;
}

// Diminui a prioridade de um elemento e reorganiza a heap
template<typename T, typename Priority>
void PriorityQueue<T, Priority>::decreaseKey(const T& value, Priority newPriority) {
    int index = findElementIndex(value);
    if (index == -1) {
        throw std::runtime_error("Elemento não encontrado na fila de prioridade");
    }
    if (newPriority > data[index].priority) {
        throw std::runtime_error("A nova prioridade é maior que a prioridade atual");
    }
    data[index].priority = newPriority;
    heapifyUp(index);
}

// Encontra o índice de um elemento na fila
template<typename T, typename Priority>
int PriorityQueue<T, Priority>::findElementIndex(const T& value) const {
    for (int i = 0; i < data.getSize(); ++i) {
        if (data[i].value == value) {
            return i;
        }
    }
    return -1;
}

// Reorganiza a heap para cima a partir do índice dado
template<typename T, typename Priority>
void PriorityQueue<T, Priority>::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (data[index].priority >= data[parentIndex].priority) {
            break;
        }
        std::swap(data[index], data[parentIndex]);
        index = parentIndex;
    }
}

// Reorganiza a heap para baixo a partir do índice dado
template<typename T, typename Priority>
void PriorityQueue<T, Priority>::heapifyDown(int index) {
    int size = data.getSize();
    while (index < size) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallestIndex = index;

        if (leftChildIndex < size && data[leftChildIndex].priority < data[smallestIndex].priority) {
            smallestIndex = leftChildIndex;
        }
        if (rightChildIndex < size && data[rightChildIndex].priority < data[smallestIndex].priority) {
            smallestIndex = rightChildIndex;
        }
        if (smallestIndex == index) {
            break;
        }
        std::swap(data[index], data[smallestIndex]);
        index = smallestIndex;
    }
}

#endif // QUEUE_H
