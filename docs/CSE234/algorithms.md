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
A functor is a class/struct that overloads the function call operator, i.e., it implements `operator ()`. Typically, functors only implement this function, and maybe a constructor, although this is not a requirement. The advantage of functors is that they can maintain state via their member variables. The below example implements a functor to computer the average of values in an array:
```C++
#include <iostream>
#include <array>

// Average is a functor since it implements the call operator
template <typename T>
struct Average {
    // Constructor to init fields to 0
    Average() {
        sum = 0;
        count = 0;
    }

    // operator() adds the value passed to it to the sum,
    // and increments the count
    void operator()(T value) {
        sum += value;
        ++count;
    }

    // property to return computed average
    double average() const {
        if (count == 0) return 0;
        else return static_cast<double>(sum) / count;
    }
private:
    T sum;
    unsigned count;
};

int main() {
    std::array<int, 7> values = { 2, 6, 24, 76, 3, 67, 5 };
    // IMPORTANT: declare an instance of functor
    Average<int> average;

    // later we will see how to do this using the algorith header
    for (int x: values) {
        // overloading operator() allows us to use the object
        // like it was a function by calling it
        average(x);
    }

    std::cout << "Average = " << average.average() << std::endl;

    return 0;
}
```

### Lambda Expressions
Also called "lambdas" or "anonymous functions", lambda expressions allow you to put a function anywhere you would put an expression, such as the right-hand side of an equals sign or as an argument to a function. Lambdas consist of three parts: a capture, a parameter list, and a body. The capture is denoted with square brackets, and allows you to pass local variables to the lambda's scope. If the lambda needs to modify a variable it captures, the variable must be passed by reference using the ampersand (&). The parameter list is like a typical parameter list for a normal function. It has the types and names of the expected arguments to the lambda. Finally, the body contains the expressions that will be executed when the lambda is called. The body has its own local scope like any other block would. Remember that the body of the lambda cannot access any local variables from the block it is called in unless they are passed via the capture. Below is an example of using a lambda to compute the average of the same array from the functor example:
```C++
#include <iostream>
#include <array>

int main() {
    std::array<int, 7> values = { 2, 6, 24, 76, 3, 67, 5 };

    // we need to declare variables for the sum and count locally now
    int count = 0;
    int sum = 0;

    // we can either use auto type or std::function<> to declare a 
    // lambda "variable"
    // to allow the lambda to modify the values of count and sum,
    // they must be passed by reference
    auto average = [&count, &sum] (int value) mutable {
        sum += value;
        ++count;
    }; // since this is an expression, the body must be ended with a semicolon

    // later we will see how to do this using the algorith header
    for (int x: values) {
        average(x);
    }

    std::cout << "Average = " << static_cast<double>(sum) / count << std::endl;

    return 0;
}
```

## For Each
The first algorithm we will look at is `std::for_each`. This function has three parameters: the starting iterator of a collection, the ending iterator of a collection, and a function that will take an element of the collection as a parameter. As promised in the comments of the above examples, let's use `for_each` to compute the average:
```C++
// must include algorithm
#include <algorithm>
#include <iostream>
#include <array>

// declaring a global variable to track the current average
// computed by the updateAverage function
static double currentAverage = 0;

template <typename T>
void updateAverage(const T& value) {
    // declaring count and sum as static variables means
    // they will only be instatiated and initialized the
    // first time the function is called
    static int count = 0;
    static T sum = 0;

    sum += value;
    ++count;
    // currentAverage has to be updated each time the 
    // function is called to keep it up to date
    currentAverage = static_cast<double>(sum) / count;
}

// this is the same functor as in the example
template <typename T>
struct Average {
    Average() {
        sum = 0;
        count = 0;
    }

    void operator()(const T& value) {
        sum += value;
        ++count;
    }

    double average() const {
        if (count == 0) return 0;
        else return static_cast<double>(sum) / count;
    }
private:
    T sum;
    unsigned count;
};

int main() {
    int sum = 0;
    int count = 0;

    std::array<int, 7> values = { 2, 6, 24, 76, 3, 67, 5 };

    // use for_each with function pointer
    std::for_each(values.begin(), values.end(), &updateAverage<int>);

    // use for_each with functor
    Average<int> average = std::for_each(values.begin(), values.end(), Average<int>());

    // use for_each with lambda. 
    // this is the same lambda as we used in the lambda example
    std::for_each(values.begin(), values.end(), [&sum, &count](int x) {
        sum += x;
        ++count;
    });

    std::cout << "Average from function pointer: " << currentAverage << std::endl;
    std::cout << "Average from functor: " << average.average() << std::endl;
    std::cout << "Average from lambda: " 
        << static_cast<double>(sum) / count << std::endl;

    return 0;
}
```

As you can see, I had to do quite a lot of coercing with the function pointer to make it work for this example. The sum and count had to be declared as static locals, and the average needed to be declared globally. In cases where state is important, function pointers are best to be avoided. With the lambda we were able to keep everything local to the main function, which is preferable, and the functor kept all data and operations local. Notice that when we use `for_each` with a functor it returns an object of that functor. 
