#include "stack.hpp"

template <typename T>
Stack<T>::Stack() : 
    maxSize(DEFAULT_MAX_STACK), 
    tos(0), 
    data(new T[DEFAULT_MAX_STACK]) {}

template <typename T>
Stack<T>::Stack(size_t max) :
    maxSize(max),
    tos(0),
    data(new T[max]) {}

template <typename T>
Stack<T>::Stack(const Stack<T> &other) :
    maxSize(other.maxSize),
    tos(other.tos),
    data(new T[other.maxSize]) 
{
    for (size_t i = 0; i < other.tos; ++i) {
        data = other.data[i];
    }
}

template <typename T>
Stack<T>::~Stack() {
    delete[] data;
    maxSize = 0;
    tos = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> rhs) {
    swap(rhs);
}

template <typename T>
void Stack<T>::swap(Stack<T> &other) {
    size_t tempMax = maxSize;
    size_t tempTos = tos;
    T *tempData = data;

    maxSize = other.maxSize;
    other.maxSize = tempMax;

    tos = other.tos;
    other.tos = tempTos;

    data = other.data;
    other.data = tempData;
}

template <typename T>
void Stack<T>::push(const T& element) {
    if (tos + 1 > maxSize) {
        throw FullStackAccess;
    }

    data[tos++] = element;
}

template <typename T>
T& Stack<T>::top() const {
    if (tos == 0) {
        throw EmptyStackAccess();
    }
    return data[tos - 1];
}

template <typename T>
void Stack<T>::pop() {
    if (tos == 0) {
        throw EmptyStackAccess();
    }
    --tos;
}

template <typename T>
void Stack<T>::resize(size_t newSize) {
    // don't resize if new size is same as old max
    if (newSize == maxSize) return;
    // if the new size is smaller than top,
    // adjust the top of the stack
    if (newSize <= tos) tos = newSize;
    // create a temp array to store copy of elements
    T *tempData = new T[newSize];
    // copy over elements
    for (size_t i = 0; i < tos; ++i) {
        tempData[i] = data[i];
    }
    // delete old data
    delete[] data;
    // assign data to new array
    data = tempData;
}

template <typename T>
size_t Stack<T>::capacity() const {
    return maxSize;
}

template <typename T>
size_t Stack<T>::size() const {
    return tos;
}

template <typename T>
bool Stack<T>::full() const {
    return tos + 1 == maxSize;
}

template <typename T>
bool Stack<T>::empty() const {
    return tos < 0;
}

template <typename T>
bool Stack<T>::operator==(const Stack& rhs) const {
    // if the tops are different, the two stacks are different
    if (tos != rhs.tos) return false;

    // compare elements pairwise
    // if they are different, immediately return false
    for (size_t i = 0; i < tos; ++i) {
        if (data[i] != rhs.data[i]) return false;
    }
    // at this point every element of the two stacks is the same
    // so the two stacks must be equal
    return true;
}
