
## Iterators
Before discussing the rest of the STL data types, we need to cover iterators. An iterator is a type of pointer that was developed to standardize access to containers. An iterator is basically a pointer to an element of a container, however, there are additionally operations that can be performed on iterators to make traversing a container consistent no matter which type of container is being accessed. Below is a quick example of a vector being created, and an iterator being used to access its members:
```C++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // the begin() member function returns an iterator to the first
    // element of a collection 
    std::vector<int>::iterator it = values.begin();

    // we often use the "auto" type for iterators rather than writing it out
    // the end() member function returns the "past-the-end" iterator
    // of a collection. this iterator points to the location immediately
    // after the end of a collection
    auto end = values.end();

    // the end iterator is not referenceable, it is just a sentinel
    // value that marks the end of the container
    while (it != end) {
        // accessing the data an iterator is pointing to requires it 
        // to be dereferenced using *, just like a pointer
        std::cout << *it << std::endl;
        // ++ is used to move the iterator to point at the next element
        ++it;
    }
    return 0;
}
```

### Range-based for-Loops
One consequence of iterators is the ability to implement range-based for-loops. If you are familiar with for loops in Python or the `foreach` loop in C#, this concept should be familiar to you. The syntax for a range-based for-loop is below:
```C++
for (Typename x : container) {

}
```
Below shows a traditional for-loop and a range-based for loop that performs the same operation:
```C++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // tradition for loop
    for (int i = 0; i < values.size(); ++i) {
        std::cout << values[i] << std::endl;
    }

    // range-based for loop
    for (int x: values) {
        std::cout << x << std::endl;
    }

    return 0;
}
```
