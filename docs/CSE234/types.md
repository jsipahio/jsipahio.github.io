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

### Common Applications
`std::vector` is the standard container used in C++ for storing collections of data. If you aren't sure which of the other containers to use for an application, that typically means a vector will work fine. Vectors offer balanced performance for most applications.

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
The STL Array class is a template class that wraps a normal C array. It has the same constraint as a C array, in that the size of the array must be known at compile time. However, it provides protections against out-of-range access via its `at` member function, provides iterators, and has member functions to return the size of the container, unlike standard C arrays where the size of the array is tracked by the programmer.

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
Lists provide a few unique member functions for common list operations. First is `splice()`, which expects an iterator and 

## Set (and Unordered Set)
The STL set is used store a collection of unique values. The multiset is used to collection of values that are not unique, but do not need to be kept in order. The multiset tracks the number of times a duplicate element has been "inserted". There are unordered variants of both the set and multiset. Most applications where sets are used do not need to preserve order, so `std::unordered_set` and `std::unordered_multiset` are typically preferred. 

### Example Applications
Sets can be used anytime you want to create a collection of unique items. Sets offer faster retrieval of items than a list, with the penalty of slower insertion and deletion than list. Since vectors have random access, they offer faster retrieval of items (although searching is slower), but inserting items that are not at the end of the vector is slower than inserting an item to a set.  
Unordered sets are faster than list and vector in almost all cases, but do not preserve order. If you need to store a collection of items where order is not needed, unordered sets are best.  
### Example
This example shows how an unordered set can be used to count the number of unique words in a text file:
```C++
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

std::unordered_set<std::string> readUniqueWords(std::ifstream &fin) {
    std::string word;
    std::unordered_set<std::string> uniqueWords;
    while (fin >> word) {
        uniqueWords.insert(word);
    }
    return uniqueWords;
}

void printReport(const std::unordered_set<std::string> &words) {
    for (const auto& word: words) {
        std::cout << word << ": " << words.count(word) << "\n";
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Not enough arguments provided. Expected 1, got 0\n";
        std::cerr << "Usage: \n";
        std::cerr << "\t./count_words [filename]\n";
        return 0;
    }

    std::ifstream fin(argv[1]);
    if (fin.fail()) {
        std::cerr << "Could not open file " << argv[1] << "\n";
        return 1;
    }

    std::unordered_set<std::string> uniqueWords = readUniqueWords(fin);
    fin.close();
    printReport(uniqueWords);

    return 0;
}
```

## Map (and Unordered Map)
STL Maps are used to store (key, value) pairs. There are four variations of map: `std::map`, `std::multimap`, `std::unordered_map` and `std::unordered_multimap`. If the keys in the map must be unique, `std::map` or `std::unordered_map` can be used. If there can be duplicate keys, then `std::multimap` and `std::unordered_multimap` must be used. The `std::map` and `std::multimap` collections preserve the insertion order of elements. If this is not required, using the `unordered` variants can provide a large performance boost.

### Unique Methods 
Maps support random access using the subscript `operator[]`, passing a key as the index. 

### Example Applications

### Example
Here, 

## Deque
A deque is a doubly-ended queue, which allows for quick access to elements at the beginning and end of the collection. The cost of random access is also fast. Like a vector, insertions and removals in the middle of the collection are slower since they require shifting elements. Expanding a deque is faster than a vector, since it does not require copying the collection, but deques use more space on average.

## Stack
The STL stack is actually a container adapter, meaning it is used to limit the access to a container. By default, it uses a deque, but it can use any sequential container (vector and list) to store the data. Stacks provide access to data in a last-in, first-out (LIFO) ordering. To enforce this, stack limits access to the container via the `push()`, `pop()`, and `top()` methods. The `push()` method inserts an element to the end of the container. The `pop()` method removes the last element from the container. The `top()` method returns the value of the last item in the container. Stacks are often used for compiler implementation, parsing, and backtracking. Below is a (very simplified) implementation of a back and forward button (such as for a browser) using stacks.
```C++
#include <assert.h>
#include <string>

// class to maintain state of stacks
class History {
private:
    // store the previously visited pages
    std::stack<std::string> previousPages;
    // store the pages after the user hits the back button
    // these get cleared after the user moves forward to a unique page
    std::stack<std::string> forwardPages;
public:
    History() {}
    // add a page to the previously visited pages
    void addPage(const std::string& page) {
        // push the page to the top of the history
        previousPages.push(page);
        // wipe any forward pages
        forwardPages.clear();
    }
    // return false and empty string if there is no previous page
    // return true and the url if there is a previous page
    // add page to forwardPages so the forward arrow can access it
    std::pair<bool, std::string> getPreviousPage() {
        // check if there is not a page to return 
        if (previousPages.empty()) {
            return std::make_pair(false, "");
        }
        else {
            // save the top of the previousPages stack
            std::pair returnValue = std::make_pair(true, previousPages.top());
            // remove the page from the previousPages stack
            previousPages.pop();
            // add to the forward pages
            forwardPages.push(returnValue.second);
            return returnValue;
        }
    }
    // return false and empty string if there is no forward page
    // return true and the url if there is a forward page
    // add the page back to the previous pages
    std::pair<bool, std::string> getForwardPage() {
        // check if there is not a forward page
        if (forwardPages.empty()) {
            return std::make_pair(false, "");
        }
        else {
            // save the top of the forwardPages stack
            std::pair returnValue = std::make_pair(true, forwardPages.top());
            // remove the page from the forwardPages stack
            forwardPages.pop();
            // add page back to the previousPages
            previousPages.push(returnValue.second);
            return returnValue;
        }
    }
};

int main() {
    // create history object
    History history;
    // add a couple pages to the history
    history.addPage("https://www.google.com");
    history.addPage("https://www.cppreference.com");

    // move back to the previous page
    auto previousPage = history.getPreviousPage();
    // check if there was a previous page (we expect this to be true)
    if (previousPage.first) {
        assert(previousPage.second == "https://www.google.com");
    }

    // move to the page we just went back from
    auto forwardPage = history.getForwardPage();
    // check if there was a forward page (we expect this will be true)
    if (forwardPage.first) { 
        assert(forwardPage.second == "https://www.cppreference.com");
    }

    // move back a page, then forward to a new page
    if (history.getPreviousPage().first) {
        history.addPage("https://www.cplusplus.com");
    }
    // we expect that there are no longer any previous 
    // pages since we added a new page to the history stack
    assert(history.getForwardPage() == std::make_pair(false, ""));

    return 0;
}

```
## Queue
Like stack the STL queue is also a container adapter. The queue data structure limits access to data so that it is accessed in first-in, first-out (FIFO) order. To do so, it limits users to the `push()`, `front()`, `back()`, and `pop()` methods. The `push()` method adds an element to the back of the queue. `front()` and `back()` return the values at the front and end of the queue, respectively. The `pop()` method removes the first element of the queue. Queues are used for buffers, such as process wait lists in operating systems, ordering the processing of network requests, and some graph traversal implementations. There is a specialized version of queue, `std::priority_queue`, which orders elements by both insertion order and a "priority" level, so that elements with more priority end up at the front of the queue, even if they are inserted after lower priority elements.

### Example Applications
Queues are used to implement process queues (i.e., waitlist), any kind of waitlist in general. 

### Example
Below is an example of a first-come, first-serve process queue:
```C++ 
#include <iostream>
#include <string>
#include <queue>

int main() {
    std::queue<std::string> processQueue;
    // use push to add elements to back of queue
    processQueue.push("process 1029");
    processQueue.push("process 1192");
    processQueue.push("process 399");
    processQueue.push("process 1922");
    processQueue.push("process 245");

    // while the queue is not empty
    while (!processQueue.empty()) {
        // print the element at the front of queue
        std::cout << processQueue.front() << "\n";
        // remove the element from the front of the queue
        processQueue.pop();
    }
    
    return 0;
}
```
Example Output:
```
process 1029
process 1192
process 399
process 1922
process 245
```

Here is an example using `priority_queue` for a simple CPU SJF (shortest job first) task scheduler:
```C++
#include <iostream>
#include <string>
#include <queue>

// create a struct to hold (very simple) process info
struct Process {
    std::string name;
    unsigned int estimatedDuration;
    Process(std::string n, unsigned int duration) {
        name = n;
        estimatedDuration = duration;
    }
    // need to implement < for priority_queue
    bool operator<(const Process& other) const {
        return estimatedDuration > other.estimatedDuration;
    }
};

int main() {
    // declaring 5 processes with various estimated durations
    Process p1 = { "process 1", 1000 };
    Process p2 = { "process 2", 100 };
    Process p3 = { "process 3", 500 };
    Process p4 = { "process 4", 400 };
    Process p5 = { "process 5", 50 };

    // add the processes the queue
    std::priority_queue<Process> sjfQueue;
    sjfQueue.push(p1);
    sjfQueue.push(p2);
    sjfQueue.push(p3);
    sjfQueue.push(p4);
    sjfQueue.push(p5);

    // while the queue is not empty
    while (!sjfQueue.empty()) {
        // use top() to access the highest priority item
        std::cout << sjfQueue.top().name << "\n";
        // remove the highest priority item
        sjfQueue.pop();
    }

    return 0;
}
```
Example Output:
```
process 5
process 2
process 4
process 3
process 1
```

## Comparison of Container Uses
So, the question that arises at this point is when to use which container. It's easy to decide if a map is needed, since it is the only container that supports key-value pairs. For set and map, unless insertion order needs to be preserved, it is always better to use the "unordered" variants. Vectors offer balanced performance for many applications, but can use excessive space and can be slowed down if many insertions have to occur at the beginning or middle of the vector. If many of these types of insertion must be made, a list may make more sense. If the order of elements needs to be preserved, and the number of elements is known ahead of time, an array may be sufficient. Sets provide quick access to unique elements, while a multiset provides quick access to the counts of a specific element in the collection. 
