# STL Vector and I/O Streams

The C++ Standard Template Library contains implementations of most common data structures and algorithms. In this class, the only STL data structure we will use is the `std::vector` class. Additionally, we will discuss the standard library I/O streams in more detail.

## Vector
A vector is an automatically resizing array. The `std::vector` class is a template class (we'll discuss templates in more detail in Week 5), which means a vector can be used to hold any data type. To specify the type of data the vector holds, we put the target data type in angle brackets after the name vector: `std::vector<int>` is a vector of `int`, `std::vector<std::string>` is a vector of strings, etc. Vectors are useful when we don't know how many data elements we need to store, such as reading values from a file. While we read the file, count the number of values we need to store, then read the values into a dynamic array that we create, this is not optimal, as reading files is one of the more computationally expensive operations we can perform.  

### Adding Values
Provided the values are being inserted to the vector in order, or the order is insignificant, the safest way to add elements with the `push_back()` function. Values can be inserted using the subscript operator `[]`, however, there is no guarantee that the vector will automatically resize if you attempt to access an index that the vector does not have capacity for. 
  
### Vector Resizing
A vector automatically resizes itself by doubling its capacity each time it runs out of space. 

## I/O Streams
At this point, you are likely used to automatically adding `#include <iostream>` to the top of all your program. Now, we are going to discuss I/O streams in more detail.

### Console I/O
The `<iostream>` header provides access to the `std::cin`, `std::cout`, and `std::cerr` streams to access the console. You should be aware that `std::cin` is used to read input data from the console, and `std::cout` is used to write data to the console. You may not be as familiar with `std::cerr`. Terminals have two output streams, one for standard output and one for error output. The `std::cerr` object writes to the error stream rather than the standard output. Therefore, when printing an error message, it is better to use `std::cerr`, so the end user can separate error messages from normal output if they wish.  
  
#### Reading Data
`std::cin` can be used to read data from the console. You are already familiar with using the extraction operator `>>` to read data. The extraction operator delineates input elements based on whitespace characters, so if you type "a b c" into the console, a single read with `>>` will only read "a". The other two letters will remain in the input stream, waiting for the next read operation. This may lead to unexpected results, if the input stream is not flushed. The example below will demonstrate this behavior:
```C++
#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;

    std::cout << "Enter your name." << std::endl;
    std::cout << "$ ";
    std::cin >> str;

    std::cout << "Enter your age (in years)." << std::endl;
    std::cout << "$ ";
    std::cin >> age;

    std::cout << "Hello, " << name 
        << ". You are " << age << "years old." << std::endl;

    return 0;
}
```
Example I/O:
```
Enter your name.
$ John S
Enter your age (in years).
$ Hello, John, you are 0 years old
```
When entering the "John S" as the name, only "John" is read into the string variable `name`. This is because `>>` splits input on whitespace characters. However, the "S" is not flushed from the input buffer. Therefore, after printing the next message, rather than allowing the user to enter the value for `age`, the next item in the input buffer is immediately read in. Depending on the compiler and platform, what the program does when trying to read the "S" into an integer may vary. On my system, it skipped trying to parse it as an integer and printed 0 for the value of age. Other systems may parse "S" as a character and cast it as an integer, or there may be some garbage value that gets printed instead of 0. The behavior is undefined.  
  
If we want to avoid these situations, we should clear the input buffer after each read attempt. Since `std::cin` stops reading after a new line, we can implement a function `clearInput()` to reset the input buffer:
```C++
#include <iostream>
#include <string>

void clearInput() {
    // this flushes any error locks,
    // such as if you try to read incompatable data types
    std::cin.clear();
    // this reads data until a new line is reached
    while (std::cin.get() != '\n' && std::cin) ;
}

int main() {
    std::string name;
    int age;

    std::cout << "Enter your name." << std::endl;
    std::cout << "$ ";
    std::cin >> str;
    clearInput();

    std::cout << "Enter your age (in years)." << std::endl;
    std::cout << "$ ";
    std::cin >> age;
    clearInput();

    std::cout << "Hello, " << name 
        << ". You are " << age << "years old." << std::endl;

    return 0;
}
```
Example I/O:
```
Enter your name.
$ 
Enter your age (in years).
$ 
Hello, , you are  years old
```

There are other mechanisms for reading input as well, however. In the `clearInput()` function, we used `std::cin.get()`. This function reads a single character at a time, including whitespace. This can be useful if we need to read input into a buffer, or are expecting input to be separated by non-whitespace characters. The `<string>` header provides a function, `getline()`, that can be used to read input into a string until a new line character is reached. 