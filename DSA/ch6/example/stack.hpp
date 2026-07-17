
#ifndef STACK_HPP
#define STACK_HPP

#include <sys/types.h>

constexpr size_t DEFAULT_MAX_STACK = 256;

/** Exception class for accessing an empty Stack */
class EmptyStackAccess {
public:
    EmptyStackAccess() {}
    const char* what() {
        return "Attempted to access empty stack";
    }
};

/** Exception class for overflowing a full Stack */
class FullStackAccess {
public:
    FullStackAccess() {}
    const char* what() {
        return "Attempted to overflow full stack";
    }
};

/**
 * class Stack
 * Uses a dynamic array to represent a
 * Stack (LIFO container) data structure
 */
template <typename T>
class Stack {
public:
    /** @defgroup Creational Methods
     @{*/
    /**
     * Default Constructor
     * Sets max stack size to DEFAULT_MAX_STACK
     */
    Stack();
    /**
     * Constructor 
     * 
     * Creates stack with maximum size of max
     */
    Stack(size_t max);
    /**
     * Copy Constructor
     * 
     * Performs deep copy of stacks
     * 
     * @param other - const reference to another Stack
     */
    Stack(const Stack& other);
    /**
     * Destructor
     * 
     * Deletes dynamically allocated memory
     */
    ~Stack();
    /**
     * Overloaded Assignment Operator
     * 
     * @param rhs - Stack that is being copied to this
     */
    Stack& operator=(Stack rhs);
    /**@}*/

    /** @defgroup Stack Methods
     @{*/
    /**
     * push - add element to stack
     * 
     * @param element - Element to add to stack
     * @pre Stack is not full
     * @post element is added to stack
     * @throws FullStackException
     */
    void push(const T& element);
    /**
     * top - return top of stack
     * 
     * @pre Stack is not empty
     * @throws EmptyStackException
     * @returns Element at top of the stack
     */
    T& top() const;
    /**
     * pop - remove element from top of stack
     * 
     * @pre Stack is not empty
     * @post Top element of stack is removed
     * @throws EmptyStackException
     */
    void pop();
    /**@}*/


    /** @defgroup Accessor and Boolean Methods
     @{*/
    /**
     * capacity - max elements the stack can hold
     * 
     * @returns maximum capacity of the stack
     */
    size_t capacity() const;
    /**
     * size - current number of elements in the stack
     * 
     * @returns number of elements in the stack
     */
    size_t size() const;
    /**
     * full - check if stack is full
     * 
     * @return true - stack is full
     * @return false - stack is not full
     */
    bool full() const;
    /**
     * empty - check if stack is empty
     * 
     * @return true - stack is empty
     * @return false - stack is not empty
     */
    bool empty() const;
    /**
     * operator ==
     * Stacks are checked for equality pairwise
     * Stacks with different capacities are still equal
     * as long as they have the same elements in the same order
     * 
     * @param other - Stack to compare to
     * @return true - stack elements match pairwise
     * @return false - any mismatch found between pairs of elements
     */
    bool operator==(const Stack &other) const;
    /**@}*/


    /** @defgroup Modifier methods
     @{*/
    /**
     * swap - constant time swap of two stacks
     * 
     * @post "this" stack is swapped with other
     */
    void swap(Stack& other);
    /**
     * resize - allocates new memory to change size of the stack
     * 
     * @param newSize - size to change stack to
     * @post the max size of "this" is changed to new size.\
             if the new size is less than the old top index,\
             top is adjusted to be max index of new size
     */
    void resize(size_t newSize);
    /** @} */
private:
    // the maximum size of the stack
    size_t maxSize;
    // "top of stack" - index of current top
    size_t tos;
    // array to store stack elements
    T *data;
};

#include "stack.tpp"
#endif 