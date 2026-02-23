# CSE234 - STL Algorithm

The `algorithm` header provides a set of common computer science algorithms that operate primarily on containers. `algorithm` was added in C++11. To use it, `#include <algorithm>`. All functions are provided in `algorithm` are in the `std` namespace. 

## Function Pointers, Functors, and Lambda Expressions
Like with iterators for STL containers, we first need to cover function pointers, functors, and lambdas for algorithm. For the sake of algorithm, these can be used interchangeably.  

### Function Pointers
There are two ways to use function pointers: pass the address of a function using the ampersand (&) as an argument, or write the function as a pointer. Below is an example of both.
```C++
// addOrSubtract takes two integers, x and y, that should be
// added or subtracted, and a function pointer, operation
// that performs the operation
int addOrSubtract(int x, int y, int *operation) {
    return operation(x, y);
}

// add is a normal function
int add(int x, int y) {
    return x + y;
}

// subtract is a function pointer
int subtract(int x, int y) {
    return x - y;
}

int main() {
    // to use add, we need to use an ampersand
    // on add's name to pass its address
    int additionResult = addOrSubtract(2, 2, &add);
    assert(additionResult == 4);
    // to use subtract, we just pass it since it is already a pointer
    int subtractionResult = addOrSubtract(3, 1, subtract);
    assert(subtractionResult == 1);
}
```

### Functors
A functor is a class/struct that overloads the function call operator, i.e., it implements `operator ()`. Typically, functors only implement this function, and maybe a constructor. The advantage of functors is that they can maintain state via their member variables. 
