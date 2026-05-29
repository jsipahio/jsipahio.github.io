# Templates and Generic Types

Many modern programming languages implement generic types in one way or another. Generic types allow functions and/or classes to be defined once for any type. This, along with function overloading and inheritance, is one of the ways modern languages implement polymorphism. In C++, generic functions and classes are defined using template parameter lists. For the basic syntax, we'll look at a short generic function that adds two values.
```C++
// generic functions and types have a template parameter
// list first that lists the alias for the generic type(s)
template <typename T>
// we then use T as our type alias
T add(const T &a, const T &b) {
    return a + b;
}
```
This function can be used to add together two members of the same type, provided they have `operator+` defined for them. At the end of this section we will briefly introduce concepts, which provide a mechanism for stating that the type `T` must have `operator +` defined.  

## Polymorphism
Polymorphism (derived from Greek, roughly means "many forms") in programming are mechanisms that allow the 

## Template Parameter Lists
When writing a generic function or data type, the signature must be preceded by the template parameter list. The template parameter list is started by the keyword `template`, followed by a list of template parameters in angle brackets. The parameter list can hold two constructs: template type aliases and non-type template parameters. First, let's discuss template type aliases. These are the most common use for templates, where you wish to define a single function or data type to operate on a variety of types. Template types in the parameter list have a "type" of either `typename` or `class`, although in modern C++ `typename` is preferred. The type alias can be any name (provided it's not a keyword or pre-existing name). When the type aliases have no semantic meaning, single, uppercase letters starting at `T` are used to name them. If the type alias has meaning, then you may name it something more expressive. Here is an example of a template parameter list with two template parameters: `template <typename T, typename U>`. Alternatively, `class` could be used in place of `typename` (again, this is not used as commonly now, especially post C++17): `template <class T, class U>`.
  
The next category of template parameters are non-type template parameters. Rather than aliasing a type, these parameters expect a value of a specific type. Additionally, the value passed for this parameter must be known at compile-time. An example of a template being used in this manner is the `std::array` data type. The `std::array` type expects two template parameters, one for the data type the array stores, and another for the size of the array. `std::array` is a wrapper around static, stack allocated arrays, so the size of the array must be known at compile time. This makes passing the array as a parameter to the constructor insufficient, as there is no way to force a parameter to the constructor to be a compile-time constant. When using a template parameter, the compiler will fail to compile the program if a compile-time constant is not provided for the size of the array. Here is an example of how the template parameter list for `std::array` would look: `template <typename T, size_t SIZE>`.  

## Declaring, Defining, and Using Generic Functions
To declare a generic function, the template parameter list is provided before the function signature:
```C++
template <typename T>
void printValue(T val);
// putting the template parameter list on a separate line
// is more readable but not required
template <typename T> void printValues(T val1, T val2);
```
The template parameter list makes `T` available as a type name in the function that follows it. When defining the function, the template parameter list must be included again:
```C++
template <typename T>
void printValue(T val) {
    std::cout << val << std::endl;
}

template <typename T> void printValues(T val1, T val2) {
    std::cout << "Value 1: " << val1 << std::endl;
    std::cout << "Value 2: " << val2 << std::endl; 
} 
```
When calling the function, the type of the argument must be provided (C++17 adds the ability for the compiler to try to deduce the type of the argument, but it is still good practice to explicitly state the intended type):
```C++
int main() {
    // actual type of argument goes angle
    // brackets after the function's name
    printValue<int>(2);
    printValues<const char*>("hello", "world");
    return 0;
}
```

## Declaring, Defining, and Using Generic Data Types
Declaring a generic class requires placing the template parameter list before the `class` keyword (structs can also be generic). The template parameters declared before the class can be used anywhere within the class: as a data member's type, the return type of a function, the type of a parameter, etc. The one exception is for friends. In general, friend functions should be avoided as much as possible. Template friends, especially `operator<<` and `operator>>` are usually easier to defined inline within the class declaration, rather than outside the class, as is common in C++. However, in the next section we will see that this does not matter very much.
```C++
#include <iostream>
#include <stdexcept>

// declare a template parameter for the data type being stored
// and a non-type paramter for the size
template <typename T, size_t SIZE>
class StaticArray {
public:
    // constructor only has to set the size field
    // so we can define it in the class
    StaticArray() : size(SIZE) {}
    // returns the size of the array
    size_t getSize() const;
    // returns an array element (getter)
    // rather than having a separate function called at() like std::array
    // this will throw an out of range exception for invalid indices
    T operator[](size_t) const;
    // provides a reference to an array element (setter)
    // throws out of range exception for out of range access attempts
    T& operator[](size_t);
    // overloaded operator << to print the array
    // writing the definition of function outside of the class
    // declaration is very finicky
    friend std::ostream& operator<<(
        std::ostream& out, 
        const StaticArray<T, SIZE>& arr
    ) {
        bool printComma = false;
        for (size_t i = 0; i < size; ++i) {
            if (printComma) std::cout << ", ";
            std::cout << data[i];
            printComma = true;
        }
    }
private:
    size_t size;
    // since size must be a compile-time constant we can do this
    T data[SIZE];
};
```
Like with the free functions, when defining the declared functions out of the class, we need to provide the template parameter list before each function. Additionally, when scoping the function to the class, the declared type alias must be passed to the class type. It will be easier to see what is meant by looking at the example.
```C++
// need to provide the template again
template <typename T, size_t SIZE>
// and pass to the class name before ::
size_t StaticArray<T, SIZE>::getSize() const {
    return size;
}

template <typename T, size_t SIZE>
T StaticArray<T, SIZE>::operator[](size_t index) const {
    if (index > size || index < 0) {
        throw std::out_of_range();
    }
    return data[index];
}

template <typename T, size_t SIZE>
T& StaticArray<T, SIZE>::operator[](size_t index) {
    if (index > size || index < 0) {
        throw std::out_of_range();
    }
    return data[index];
}
```
As can be seen in the example, each function needs to have the template parameter listed. This is needed to pass the declared template parameters to the template argument list of the class. In the next section, the compilation mechanisms of templates will be discussed.

## Compiling Generics in C++ 
Earlier, we discussed that typically functions and classes are declared in a header file and implemented in a separate source file. This makes it possible to make changes to definitions without needed to recompile every file in the project. However, this is not possible with templates. Each time a generic type is created, or function is called, the compiler needs to generate a new version of the type/function's definition that replaces the template type alias with the actual type. Therefore, templates must be defined within a header file. It is possible to manually implement a template for a concrete type. This can be done in a source file. 

## Concepts
C++ 20 introduced *concepts*, which provide a syntax to express the required behavior of a generic type. A concept is a named  
