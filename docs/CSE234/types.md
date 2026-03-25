# CSE234 - STL Data Types

The Standard Template Library (STL) provides implementations of most common data structures. These include arrays, vectors, lists, sets, maps, stacks, and queues. All of these have dynamically changing size, except for array, whose size must be known and specified at compile-time. Below is a brief overview of each:
- **Array** - A fixed-size collection of elements that preserves order and allows random access (index)
- **Vector** - An automatically resizing collection that preserves order and allows random access (index)
- **List** - A collection that does not support random access but does preserve order
- **Set** - A collection that does not support random access. Elements of a set are unique
- **Multiset** - A set where items are not unique, but there is a count of how many times an element occurs
- **Map** - A collection of (key, value) pairs with unique keys
- **Multimap** - A collection of (key, value) pairs where the keys are not unique
- **Stack** - A container where items can only be accessed in last-in, first-out (LIFO) order (like a stack of dishes, the last dish put on the top of the stack is the first one to be removed)
- **Queue** - A container where items can only be accessed in first-in, first-out (FIFO) order (like a line (queue) waiting to check out at a store)

We'll discuss `std::vector<T>` first, then describe iterators and the methods defined across almost all STL containers. 

## Vector
The STL Vector is an automatically resizing dynamic array wrapper. When the vector runs out of space to hold new elements, it automatically resizes itself to be twice the size of its previous capacity. Items can be inserted into the beginning or middle of a vector while preserving order. To do so, all elements that come after the inserted element must be shifted. This happens automatically, as well. 
### Construction/Initialization
Vectors, like arrays, must have the type of data it is storing specified. Vectors do not require a size as one of its template arguments, however. An initial size can be provided to the constructor, however. Vectors support copying and assignment, like all STL containers.
### Adding Elements
The main way to add new elements to the end of a vector is via the `push_back` functions. 
### Accessing Elements
### Resizing

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


## Common Methods
STL data types share the names and operations for many of their methods. For example, all collections provide `begin()` and `end()` to access the start and end iterators of the collection. Below is a table of common method names, the parameters expected, and a column for STL collections that do not implement that method, if applicable.
| Method | Parameters | Behavior | Exceptions |
|--------|------------|----------|------------|
| begin() | | Returns an iterator to the first element of the container | |
| end() | | Returns an iterator to the "past-the-end" iterator of the container | |
| front() | | Returns the first element of the collection | |
| back() | | Returns the last element of the collection | |
| empty() | | Returns `true` if the container is empty | | 
| size() | | Returns the number of elements stored in the container | | 
| clear() | | Deletes every element of the container, but not the container itself | `array` |
| insert() | iterator to insertion point, value to be inserted | Inserts a new element immediately before the location pointed to by the iterator | `array` |
| erase() | iterator to element to be deleted | deletes element from collection | `array` |
| emplace() | iterator to insertion point, arguments to element's constructor | calls elements constructor with provided arguments, inserts immediately before the iterator that is passed | `array` |
| swap() | another collection | swaps the calling collection with its argument | |

### insert() vs emplace()
At first, `insert()` and `emplace()` seem very similar, as they both add new elements to a collection at a provided insertion point. However, `insert()` requires the new value to already be constructed. `emplace()` instead takes the arguments to the data type's constructor, calls the constructor to create a new element, and inserts the newly created element. Below is an example that illustrates this difference.

```C++
#include <vector>

struct Date {
    Date(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }
private:
    int day;
    int month;
    int year;
};

int main() {
    std::vector<Date> dates = {
        { 2, 11, 2025 },
        { 2, 12, 2026 },
        { 2, 13, 2026 },
        { 2, 14, 2026 }
    };
    // create a new Date object and insert it
    Date date(2, 10, 2026);
    dates.insert(dates.begin(), date);

    // implicitly call the constructor to insert one
    dates.insert(dates.begin(), Date(2, 9, 2026));

    // pass arguments to constructor to emplace to create new Date
    dates.emplace(dates.begin(), 2, 8, 2026);

    return 0;
}
```

### Comparison Operators
All STL containers provide comparison operators (==, <=, >=, <, >, !=) to compare two containers. 

## Array
The STL Array class is a template class that wraps a normal C array. It has the same constraint as a C array, in that the size of the array must be known at compile time. However, it provides protections against out-of-range access via its `at` member function, provides iterators, and has member functions to return the size of the container.

### Unique Operations
Like a C array, STL arrays support random access via the subscript operator (i.e., using an index). They also provide an `at()` member function that raises an exception when an invalid index is provided. 

## List (and Forward List)
The STL List class is used to create a linked list. Similar to an array/vector, lists store a collection of elements while preserving their order. Linked lists are different from arrays/vectors in that the elements can no longer be accessed by an index and are not stored contiguously in memory. This can be an advantage or disadvantage depending on the usage. Below is a table that compares lists and vectors.
| Scenario | Array | Vector | List |
| -------- | ----- | ------ | ---- |
| Insertion at End | Impossible | May be instant, unless vector must be resized | Fast |
| Insertion at Middle | Impossible | Requires shifting all elements that follow the insertion point, Slow | Fast |
| Insertion at Front | Impossible | Requires shifting all elements, Slow | Fast |
| Deletion | Impossible | Requires shifting of elements, Slow | Fast, and preserves iterators |
| Random Access (index) | Fast | Fast | Impossible |
| Space | Must be known at compile time - empty indices are wasted space | Does not need to be known at compile time, but resizing is expensive and can result in massive amounts of wasted space | Does not need to be known at compile time, and there is never wasted space | 

### Unique Operations
`std::list` provides `push_front()` to add elements to the front of the list, and `push_back()` to add elements to the end of the list. Similarly, it offers `pop_front()` and `pop_back()` to remove elements from the front and end of the list, respectively. The `std::forward_list` class only supports `push_front()` and `pop_front()`.  
Lists provide a few unique member functions for common list operations. First is `splice()`, which provides 

## Set (and Unordered Set)
The STL set is used store a collection of unique values. The multiset is used to collection of values that are not unique, but do not need to be kept in order. 

## Map (and Unordered Map)
STL Maps are used to store (key, value) pairs. There are four variations of map: `std::map`, `std::multimap`, `std::unordered_map` and `std::unordered_multimap`. If the keys in the map must be unique, `std::map` or `std::unordered_map` can be used. If there can be duplicate keys, then `std::multimap` and `std::unordered_multimap` must be used. The `std::map` and `std::multimap` collections preserve the insertion order of elements. If this is not required, using the `unordered` variants can provide a large performance boost.

## Deque
A deque is a doubly-ended queue, which allows for quick access to elements at the beginning and end of the collection. The cost of random access is also fast. Like a vector, insertions and removals in the middle of the collection are slower since they require shifting elements. Expanding a deque is faster than a vector, since it does not require copying the collection, but deques use more space on average.

## Stack

## Queue

## Comparison of Container Uses
So, the question that arises at this point is when to use which container. It's easy to decide if a map is needed, since it is the only container that supports key-value pairs. For set and map, unless insertion order needs to be preserved, it is always better to use the "unordered" variants. Vectors offer balanced performance for many applications, but can use excessive space and can be slowed down if many insertions have to occur at the beginning or middle of the vector. If many of these types of insertion must be made, a list may make more sense. If the order of elements needs to be preserved, and the number of elements is known ahead of time, an array may be sufficient. Sets provide quick access to unique elements, while a multiset provides quick access to the counts of a specific element in the collection. 
