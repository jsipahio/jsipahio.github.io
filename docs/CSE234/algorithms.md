# CSE234 - STL Algorithm

The `algorithm` header provides a set of common computer science algorithms that operate primarily on containers. `algorithm` was added in C++11. To use it, `#include <algorithm>`. All functions are provided in `algorithm` are in the `std` namespace. All algorithms have the option to provide an "execution policy", but these will not be discussed in this course.  

## Function Pointers, Functors, and Lambda Expressions
Like with iterators for STL containers, we first need to cover function pointers, functors, and lambdas to understand how to use the STL algorithms. Any of these options can be used with the STL algorithms.  

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
The first algorithm we will look at is `std::for_each`. This function has three parameters: the starting iterator of a collection, the ending iterator of a collection, and a function object that takes an element of the collection as a parameter. As promised in the comments of the above examples, let's use `for_each` to compute the average:
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

// this is the same functor as in the first functor example
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

As you can see, I had to do quite a lot of coercing with the function pointer to make it work for this example. The sum and count had to be declared as static locals in the function, and the average needed to be declared globally. In cases where state is important, function pointers are best to be avoided. With the lambda we were able to keep everything local to the main function, which is preferable, and the functor kept all data and operations local. Notice that when we use `for_each` with a functor, it returns an object of that functor.
  
The start and end iterator do not need to be the start and end of the collection (although the start must come before the end, of course). If we wanted to exclude the start and end of the range, we could do so as follows:
```C++
Average<int> average = std::for_each(values.begin() + 1, values.start() + values.size() - 2, Average<int>());
```

Another version of `for_each`, `for_each_n` (C++17), also exists. This takes three arguments as well: the start iterator of the collection, the number of elements to operate on, and the function object. This makes the syntax for operating on partial ranges more concise. For example, if we wanted to average the first three elements of `values`:
```C++
// with for_each
Average<int> average = std::for_each(values.begin(), values.start() + 3, Average<int>());
// with for_each_n
Average<int> average_n = std::for_each_n(values.begin(), 3, Average<int>());
```

## Searching
There are many algorithms provided for searching through a collection, as searching is a common task in computer programs.

### Any, All, and None
The first three searching algorithms we'll discuss return `bool`. The first function, `std::any_of`, returns true if **at least one** element in the collection meet the search criteria. `std::all_of` returns true if **all** items in the collection meet the search criteria. Finally, `std::none_of` returns true if **no** elements meet the criteria. All three functions have three arguments: the starting iterator, the ending iterator, and a predicate (a function object that returns a boolean). Below are some examples of each function's usage:
```C++
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = { 1, -2, 5, 34, 2, 90, 365, -67 };

    // this will return true since there is 
    // at least one negative value in the vector
    if (std::any_of(values.begin(), values.end(), [](int x) { return x < 0; }))
        std::cout << "values contains a negative number" << std::endl;
    else
        std::cout << "values contains no negatives" << std::endl;

    // this will be false since there are even numbers in values
    if (std::all_of(vales.begin(), values.end(), [](int x) { return x % 2; }))
        std::cout << "All values are odd" << std::endl;
    else
        std::cout << "Some values are even" << std::endl;
    
    // this will be true since there are no 0s in values
    if (std::none_of(values.begin(), values.end(), [](int x) { return x == 0; })) 
        std::cout << "There are no 0s in values" << std::endl;
    else 
        std::cout << "There is at least one 0 in values" << std::endl;

    return 0;
}
```

To be more concrete with our definitions, `any_of` returns true iff (if and only if) the predicate returns true at least once. `all_of` returns true iff the predicate returns false zero times. `none_of` returns true iff the predicate returns true zero times.  

### Find, Find If, and Find If Not
If you want to find a certain element, or if a certain element matches (or doesn't match) a criterion, then `std::find`, `std::find_if`, and `std::find_if_not` can be used. `std::find` takes a starting and ending iterator as its first two parameters, and the value to search for as its third parameter. If you are not looking for a specific value, but if a value in the collection meets a certain condition, `std::find_if` can be used. `find_if` also takes a start and end iterator as its first two parameters, but instead of a value it expects a predicate as the third argument. If you want to find an element that does not match a condition, `std::find_if_not` is used the same way. All three functions return an iterator to the found element, or an iterator to the end of the collection if no match is found. If there are multiple matches, only the first match's iterator is returned. 

```C++ 
// add code example
```

### Find First Of
The `std::find_first_of` is similar to `std::string::find_first_of`. Its parameters are the start and end iterators of the collection to search, along with the start and end iterators of the collection of search targets. If any of the elements in the second collection are found in the first, an iterator to that element is returned.

```C++
// add code example
```

### Find End
`std::find_end` finds the last occurrence of a collection within another. 

### Count and Count If
To determine how many times an element appears in a collection, `std::count` can be used. `std::count` expects a starting iterator, ending iterator, and an element to search for and count as parameters. It returns the number of instances of the provided element in the collection as a `size_t` value. To count the number of elements that match a certain criterion, use `std::count_if`. Again, `std::count_if` expects the start and end iterator, but instead of a specific element it instead takes a predicate, and will count all elements for which that predicate returns true.

```C++
// add code example
```

### Search
The `std::search` function takes two ranges as input. It searches for the first occurrence of the second range within the first, and returns an iterator to the result of the search. For example:
```C++
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> values = { 1, 2, 3, 1, 2, 6, 3, 1, 2 };
    std::vector<int> target = { 1, 2, 6 };
    // pass the beginning and end of the range to search
    // and the beginning and end of the range we want to find
    auto it = std::search(values.begin(), values.end(), target.begin(), target.end());
    // the iterator returned should point to the 4th element of the vector
    assert(*it == values[3]);
    assert(*(it + 1) == values[4]);
    assert(*(it + 2) == values[5]);
    target = { 1, 2, 5};
    // since target is not in the range we are searching, we expect not to find it
    it = std::search(values.begin(), values.end(), target.begin(), target.end());
    // when the target is not found it returns the second argument,
    // i.e., the end of the search range
    assert(it == values.end());
    return 0;
}
```

### Search N
Unlike `for_each_n`, which was basically the same as `for_each`, `search_n` is pretty different from search. Rather than taking a range to search for, `search_n` looks for consecutive occurrences of a single value. The parameters are the start and end iterators of a collection to search in, the number of times the target should appear consecutively, and the target to search for. Example:
```C++
#include <algorithm>
#include <cassert>
#include <vector>

int main() {
    std::vector<int> values = { 1, 1, 2, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 2 };
    auto it2 = std::search_n(values.begin(), values.end(), 2, 1);
    auto it3 = std::search_n(values.begin(), values.end(), 3, 1);
    auto it4 = std::search_n(values.begin(), values.end(), 4, 1);
    auto it5 = std::search_n(values.begin(), values.end(), 5, 1);
    auto it6 = std::search_n(values.begin(), values.end(), 6, 1);
    assert(it2 == values.begin());
    assert(it3 == values.begin() + 3);
    assert(it4 == values.begin() + 8);
    assert(it5 == values.begin() + 8);
    assert(it6 == values.end());
    return 0;
}
```

## Copying
`std::copy` takes the start and end iterators of the collection being copied, along with the start iterator of the destination collection. `std::copy_if` takes an additional parameter, a predicate, that should return true if the element should be copied and false if it should not. `std::copy_n` takes the starting iterator of the collection being copied from, the number of items to copy, and the starting iterator of the destination collection. `std::copy_backward` takes the start and end iterator of the collection to be copied, and the end iterator of the destination collection. The elements are copied in order, but placed at the end of the destination collection.
```C++
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> values = { 1, 2, 3, 4, 5, 6, 7, 8 };
    // the destination needs to be large enough to hold the result
    std::vector<int> valuesCopy(values.size());
    std::vector<int> evenValues(values.size());
    std::vector<int> firstHalf(values.size() / 2);
    std::vector<int> twoCopies(values.size() * 2);
    // pass the beginning and end of the range to be copied,
    // and the start iterator of the destination to copy it to
    // valuesCopy == { 1, 2, 3, 4, 5, 6, 7, 8 }
    std::copy(values.begin(), values.end(), valuesCopy.begin());
    // pass the beginning and end of the range to be copied from,
    // an iterator to the start of the destination range,
    // and a predicate that returns true if the element should 
    // be copied, and false if it should not be copied
    // evenValues == { 2, 4, 6, 8, ?, ?, ?, ? }
    std::copy_if(values.begin(), values.end(), evenValues.begin(), [](int x) {
        return !(x % 2);
    });
    // pass the beginning iterator of the range to be copied from,
    // the number of elements to copy, and the start iterator of
    // the range to copy the elements to
    // firstHalf == { 1, 2, 3, 4 }
    std::copy_n(values.begin(), values.size() / 2, firstHalf.begin());
    // copy values into first half of twoCopies
    std::copy(values.begin(), values.end(), twoCopies.begin());
    // now, use copy_backward to put second copy of values at the end
    // twoCopies == { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 }
    std::copy_backward(values.begin(), values.end(), twoCopies.end());
    return 0;
}
```
We'll talk about `std::remove` in the next section, but the functions `std::remove_copy` and `std::remove_copy_if` will be discussed here, since they are still copying a collection rather than directly modifying it. These functions will copy a collection to a new collection, but omit elements that meet the specified criteria. Both have the same first three arguments as `std::copy`, the start and end iterator of the collection being copied and the start iterator of the target collection. The fourth argument of `std::remove_copy` is the value that will be omitted when performing the copy. The fourth argument of `std::remove_copy_if` is a predicate that returns true if an element will be omitted, and false if it will be copied.
```C++
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> values = { 0, 1, 3, -6, 1, 0, -5, 6, -2, 0 };
    std::vector<int> noZeros(values.size());
    std::vector<int> noNegativeValues(values.size());
    // copy values into noZeros, excluding elements that are 0
    // after operation:
    // values == { 0, 1, 3, -6, 1, 0, -5, 6, -2, 0 }
    // noZeros == { 1, 3, -6, 1, -5, 6, -2, ?, ?, ? }
    std::remove_copy(values.begin(), values.end(), noZeros.begin(), 0);
    // copy values into noNegativeValues, excluding elements that are less than 0
    // after operation: 
    // values = { 0, 1, 3, -6, 1, 0, -5, 6, -2, 0 }
    // noNegativeValues = { 0, 1, 3, 1, 0, 6, 0, ?, ?, ? }
    std::remove_copy_if(values.begin(), values.end(), noNegativeValues.begin(), [](int x) {
        // predicate returns true if element is ignored
        return x < 0;
    });
    return 0;
}
```
There are also `std::replace_copy` and `std::replace_copy_if` which work exactly the same as the remove variants, but rather than omitting the element they instead take an additional fifth argument, which is a value to replace the target with. See the later section on `std::replace` and `std::replace_if` for an example of replacement.

## Modifying
These algorithms modify the state of a collection, including removing, transforming, and moving items.

### Removal
`std::remove` and `std::remove_if` remove items from a collection. Both take the start and end iterators of the collection. `std::remove` expects a possible element of the collection to be removed. `std::remove_if` expects a predicate that returns true if the element needs to be removed.
```C++
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> values = { 0, 1, 3, -6, 1, 0, -5, 6, -2, 0 };
    // remove 0s from values
    // after operation:
    // values == { 1, 3, -6, 1, -5, 6, -2, ?, ?, ? }
    std::remove_copy(values.begin(), values.end(), 0);
    // remove negatives from values
    // values = { 1, 3, 1, 6, ?, ?, ?, ?, ?, ? }
    std::remove_copy_if(values.begin(), values.end(), [](int x) {
        // predicate returns true if element is ignored
        return x < 0;
    });
    return 0;
}
```

### Move
`std::move` *moves* elements from one collection to another. Its parameters are the same as those of `std::copy`: the start and end iterator of the collection being copied and the start iterator of the destination (there is also a `std::move_backward` that follows the same logic as `std::copy_backward`). The result on the destination collection is the same. However, the source collection cannot be guaranteed to have the same elements as before the move. The source collection's memory is still valid and allocated, and it will have valid elements, just not the same elements. There are some data types that cannot be copied, and therefore to put them in another collection they must be moved. An example would be `std::jthread` objects.  
  
**Note:** There is another `std::move` defined in the "utility" header. This deals with C++ move semantics, which are not a topic of discussion in this class.

### Swap
`std::swap` takes two elements and swaps their values:
```C++
#include <algorithm>

int main() {
    int x = 5;
    int y = 3;
    std::swap(x, y);
    // x == 3
    // y == 5
    return 0;
}
```
`std::iter_swap` swaps two elements of a collection using their iterators:
```C++
#include <algorithm>
#include <list>
#include <string>

int main() {
    std::list<std::string> todoList = {
        "mow grass",
        "water plants",
        "buy groceries",
        "pay bills"
    }; 
    // this swaps the order of "water plants" and "buy groceries"
    // in the list
    std::iter_swap(todoList.begin() + 1, todoList.begin() + 2);
    return 0;
}
```
There is also `std::swap_ranges`, which takes the start and end iterator of a range of a collection, and the start iterator of the range it is being swapped with. 
```C++
#include <algorithm>
#include <string>

int main() {
    std::string str = "world hello";
    std::swap_ranges(str.begin(), str.begin() + 5, str.begin() + 6);
    // str == "hello world"
    return 0;
}
```

### Replace
`std::replace` operates similarly to `std::remove`, but rather than deleting the element from the collection, it replaces it with another. Similarly, `std::replace_if` replaces all elements that meet the provided criteria with another element.
```C++
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> values = { 0, 4, 1, 6, 2, 5, 2, 5, 6 };
    // replaces all instances of 2 with -2
    // values == { 0, 4, 1, 6, -2, 5, -2, 5, 6 }
    std::replace(values.begin(), values.end(), 2, -2);
    // replaces all numbers greater than 3 with 3
    // values == { 0, 3, 1, 3, -2, 3, -2, 3, 3 }
    std::replace(values.begin(), values.end(), [](int x) { return x > 3; }, 3);
    return 0;
}
```

### Transform
`std::transform` has two variants. The first takes the start and end iterator of a collection, and a function object/pointer/lambda to apply to each element of the collection. The function object should return the modified element.
```C++
#include <algorithm>
#include <string>

int main() {
    std::string str = "hello world";
    std::transform(str.begin(), str.end(), [](const char& c) {
        return toupper(c);
    });
    // str == "HELLO WORLD"
    return 0;
}
```
For the next version, I'll provide an example first and then explain:
```C++
#include <algorithm>
#include <cmath>
#include <vector>

// this will calculate the hypotenuses of triangles using std::transform
int main() {
    std::vector<int> bases = { 1, 2, 3, 4, 5, 6, 7, 8 };
    std::vector<int> heights = { 2, 3, 4, 5, 12, 13, 24, 15 };
    std::vector<double> hypotenuses(bases.size());
    // I typically hate comments on the same line as code, but
    // in this case I'll do it to explain each parameter
    std::transform(
        bases.begin(), // the start iterator of the first range
        bases.end(), // the end iterator of the first range
        heights.begin(), // the start iterator of the second range
        hypotenuses.begin(), // the start iterator of the destination range
        [](int a, int b) { // a will be an element of the first range, b is from the second
            return  pow(pow(a, 2) + pow(b, 2), 0.5); // return value is stored in the destination range
        }
    );
    // hypotenuses == { 2.23607, 3.60555, 5, 6.40312, 13, 14.3178, 25, 17 }
    return 0;
}
```
This version of transform is basically used to combine elements of two ranges. If you view the example on C++ Reference (https://en.cppreference.com/w/cpp/algorithm/transform.html) you can see that this could be used to edit a single collection as well. The first two parameters are the start and end of the first range. The third parameter is the start of the second range (the end is deduced based on the distance between the start and end of the first range). The fourth parameter is the start iterator of the destination range. The last parameter is a function object that has two parameters, one from each input range. Its return value will be stored in the destination range.

### Unique
The `std::unique` function will remove consecutive, duplicate elements from a range. The function takes iterators to the start and end of the range to remove duplicate elements from. Optionally, you can provide a predicate that returns true if the two elements are the same. Otherwise, the algorithm uses `operator==` to compare elements. An iterator to the new last element of the range is returned. 
```C++
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> values = {  };
    std::vector<int> uniqueValues(values);
    std::unique(uniqueValues.begin(), uniqueValues.end());
}
```
