#include "stack.hpp"

// assign fields to default values
template <typename T>
Stack<T>::Stack() : 
    maxSize(DEFAULT_MAX_STACK), 
    tos(0), 
    data(new T[DEFAULT_MAX_STACK]) {}

// create dynamic array of size "max"
template <typename T>
Stack<T>::Stack(size_t max) :
    maxSize(max),
    tos(0),
    data(new T[max]) {}

// copy fields and init array
template <typename T>
Stack<T>::Stack(const Stack<T> &other) :
    maxSize(other.maxSize),
    tos(other.tos),
    data(new T[other.maxSize]) 
{
    // copy data
    for (size_t i = 0; i < other.tos; ++i) {
        data[i] = other.data[i];
    }
}

// destructor
template <typename T>
Stack<T>::~Stack() {
    // delete dynamic array
    delete[] data;
    // set fields to 0
    maxSize = 0;
    tos = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> rhs) {
    // C++ copy/swap idiom
    swap(rhs);
    return *this;
}

template <typename T>
void Stack<T>::swap(Stack<T> &other) {
    // temp variables
    size_t tempMax = maxSize;
    size_t tempTos = tos;
    T *tempData = data;

    // swap max sizes
    maxSize = other.maxSize;
    other.maxSize = tempMax;

    // swap tops of stack
    tos = other.tos;
    other.tos = tempTos;

    // swap data pointers
    data = other.data;
    other.data = tempData;
}

template <typename T>
void Stack<T>::push(const T& element) {
    // check if the stack is full
    if (tos + 1 > maxSize) {
        throw FullStackAccess();
    }

    // add new element
    data[tos++] = element;
}

template <typename T>
T& Stack<T>::top() const {
    // check if the stack is empty
    if (tos == 0) {
        throw EmptyStackAccess();
    }
    // return data on the top of the stack
    return data[tos - 1];
}

template <typename T>
void Stack<T>::pop() {
    // check if the stack is empyt
    if (tos == 0) {
        throw EmptyStackAccess();
    }
    // decrement tos, don't actually need to delete anything
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
    // update maxSize
    maxSize = newSize;
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
    return tos + 1 >= maxSize;
}

template <typename T>
bool Stack<T>::empty() const {
    return tos == 0;
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
