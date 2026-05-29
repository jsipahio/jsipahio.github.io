# Iterators

In the past, if we want to inspect the contents of an array, we'd use a for-loop to iterate over each index. However, you cannot do this for a list. Data is not stored contiguously like in an array; lists are a collection of nodes that reference the next (and sometimes previous) element. So, how can we step through the elements of a container whose underlying implementation is list-based? Iterators are an abstraction that allows for lists to be iterated through. Iterators can also be defined for array-based containers, allowing for a unified method of traversal for all containers. The standard template library defines iterators for all container types. 

## Basic Concept/Structure
An iterator is essentially a pointer to an element in a container. However, iterators also define operations that allow them to move to the next item in the container. For some container types, such as a doubly linked list, bidirectional iterators that allow the iterator to move backwards through the container can also be defined. In C++, an iterator should define the following methods:  
- `operator++()`: The `++` operator allows the iterator to move forward in the container
- `operator*()`: In this case, `*` is pointer dereferencing, not multiplication. This allows the user to access the value pointed to by the iterator.
- `operator->()`: This allows the pointer to an object to access its members without needing to be dereferenced.
- `operator==()`: This is used to compare iterators. While not directly useful to the iterator itself, it is needed to check when the end of the container has been reached.
If we want to implement a bidirectional iterator, then `--` must also be implemented:  
- `operator--()`: This allows the iterator to access the previous element in the container.

Iterators are somewhat odd in that they handle very little logic on their own. It is the role of the data structure using the iterator to guarantee the proper behavior of the iterator. Containers that provide access via iterators need to define the following members:
- `begin()`: This member function returns an iterator that points to the first element in the collection.
- `end()`: This member function returns an iterator to a location that is "just past the end" of the container. In an array, it would be equivalent to a pointer to the element at `array[SIZE]`, i.e., the location where the next element would be. For some list-based containers, this may be `nullptr`. For others, there may be a sentinel node that marks the end of the container, but does not store data.

Bidirectional iterators can also provide the following members to allow containers to be accessed in reverse order:
- `rbegin()`: This member function returns an iterator that points to the last element of the container. Unlike `end()`, this should point to the last element that actually stores data.
- `rend()`: Like `end()`, this returns an iterator to "just before the front" of the container. If it were an array, this would be like returning the -1 index of the array. This may be implemented by either using `nullptr`, or a sentinel node before the front of the container.

## How to Define an Iterator
There are a few ways to define an iterator, depending on how specialized it is to the class it is being implemented for. One option is to implement iterators as a nested class. This is the approach taken by C++'s standard library. This allows the iterators to access private implementation details of the class while making clear that they are coupled to the class. Another option for if the iterator needs access to the class's private members is to make the iterator a friend class. In this case, the iterator is forward declared as a friend within the body of class it is being defined for, and then defined elsewhere. If the iterator does not need access to the private members, it is possible to define the iterator as a totally separate class. Since the C++ standard library uses nested classes for its iterators, that is the approach we will use here. Below is an example of an iterator defined for the doubly-linked list we created in the last section. The parts of the list that have been defined already are truncated from this example, but the full code can be viewed in the examples provided with this chapter.
```C++
```

## Example Usage
Iterators can be used to loop through a container. To begin with, we can define a basic for loop using the iterator:
```C++
#include <iostream>
#include "list.hpp"

int main() {
    List<int> list;

    for (int i = 0; i < 10; ++i) {
        list.insertBack(i);
    }

    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << std::endl;
    }

    return 0;
}
```
However, we can do better. Provided you have implemented the functions listed earlier for you iterator and class, you can use a range-based for loop to iterate through the container instead:
```C++
#include <iostream>
#include "list.hpp"

int main() {
    List<int> list;

    for (int i = 0; i < 10; ++i) {
        list.insertBack(i);
    }

    for (int x: list) {
        std::cout << x << std::endl;
    }

    return 0;
}
```
The iterator we defined is not constant, so we can also modify data elements while we iterate. Note that when using a range-based for loop, we need to add the ampersand to note that `x` should be a reference and not a copy.
```C++
#include <iostream>
#include "list.hpp"

int main() {
    List<int> list;

    for (int i = 0; i < 10; ++i) {
        list.insertBack(i);
    }

    for (int& x: list) {
        x *= 2;
    }

    for (int x: list) {
        std::cout << x << std::endl;
    }

    return 0;
}
```
There are times when you may need to guarantee that an iterator will not modify elements of the container. In that case, you need to define a separate `ConstIterator` that returns `const` references to the container's elements. Additionally, you'll have to define separate `cbegin()` and `cend()` members that return the constant iterator. 
