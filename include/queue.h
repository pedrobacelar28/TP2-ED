#ifndef QUEUE_H
#define QUEUE_H

#include "vetor.h"
#include <stdexcept>

template<typename T, typename Priority>
class PriorityQueue {
public:
    PriorityQueue();
    void push(const T& value, Priority priority);
    T pop();
    bool isEmpty() const;
    void decreaseKey(const T& value, Priority newPriority);

private:
    struct Element {
        T value;
        Priority priority;
    };

    Vetor<Element> data;
    int findElementIndex(const T& value) const;
    void heapifyUp(int index);
    void heapifyDown(int index);
};

template<typename T, typename Priority>
PriorityQueue<T, Priority>::PriorityQueue() : data() {}

template<typename T, typename Priority>
void PriorityQueue<T, Priority>::push(const T& value, Priority priority) {
    Element element = {value, priority};
    data.push_back(element);
    heapifyUp(data.getSize() - 1);
}

template<typename T, typename Priority>
T PriorityQueue<T, Priority>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    T minValue = data[0].value;
    data[0] = data[data.getSize() - 1];
    data.pop_back();
    heapifyDown(0);
    return minValue;
}

template<typename T, typename Priority>
bool PriorityQueue<T, Priority>::isEmpty() const {
    return data.getSize() == 0;
}

template<typename T, typename Priority>
void PriorityQueue<T, Priority>::decreaseKey(const T& value, Priority newPriority) {
    int index = findElementIndex(value);
    if (index == -1) {
        throw std::runtime_error("Element not found in the priority queue");
    }
    if (newPriority > data[index].priority) {
        throw std::runtime_error("New priority is greater than current priority");
    }
    data[index].priority = newPriority;
    heapifyUp(index);
}

template<typename T, typename Priority>
int PriorityQueue<T, Priority>::findElementIndex(const T& value) const {
    for (int i = 0; i < data.getSize(); ++i) {
        if (data[i].value == value) {
            return i;
        }
    }
    return -1;
}

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
