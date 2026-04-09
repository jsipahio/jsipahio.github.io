# Pointers and Memory Allocation
Put simply, a pointer is a variable that holds a memory address instead of a value. 

## The Memory Model of a Program
A computer program consists of five main areas in memory: text, data, heap, stack, and unmanaged. The text area contains the actual program instructions that need to be read and executed, along with constant values (constants are actually replaced by their actual, literal values by the compiler when the program is compiled). The data area contains static and global variables. The heap is used to store values that are dynamically allocated at runtime.
The stack contains the values of local variables and the call stack. The unmanaged area is used for environment variables and command-line arguments.

### Text Area
The text area contains the compiled instructions that describe what the program actual does. At this point, constants have been replaced by literal values and variables are replaced with their memory addresses. This is why declaring any value that could be constant as `const` is a performance optimization. The value becomes part of the program text, rather than needing to be read from memory anytime it is needed.

### Data Area
The data area is separated into two regions for initialized and uninitialized values. The data area stores static and global variables. Statics and globals that are provided initial values are stored in the initialized data area. The uninitialized values are stored in what is commonly called the BSS (block start symbol) area. The initialized values area of the data area contains the variable offsets and values in the compiled executable file, whereas the BSS contains the amount of space required to hold the uninitialized variables. The variable are then allocated in the BSS when the program is executed.

### Stack
The typical program diagram has the stack above the heap, but it makes more sense to explain the stack first to better differentiate the heap. This is not the same as the stack ADT we will discuss later in the course, but it does follow the same principle of last-in, first-out access. Each time a function is called, its local variables are added to the top of the stack. When the function is done executing, all the variables allocated for that function are popped from the stack. This makes cleaning up the memory used by a function easy, since calling functions' data will still be on the stack when control is returned to that function. Consider this simple program below:
```C++
void foo() {
    int a = 5;
}
void bar() {
    int a = 4;
    foo();
}
int main() {
    int a = 7;
    bar();
}
```
When the program is loaded, the stack will be empty (the real stack is of course using binary, but for the example we'll use decimal numbers):
```
1012    0000    XXXX
1008    0000    XXXX
1004    0000    XXXX
1000    0000    XXXX
```
When the program begins execution, the main function's data is added to the stack since it is the entry point of a C++ program:
```
1012    0000    XXXX
1008    0000    XXXX
1004    0000    XXXX
1000    0007    main::a
```
The main function calls "bar()", so bar's data is loaded onto the stack next:
```
1012    0000    XXXX
1008    0000    XXXX
1004    0004    bar::a
1000    0007    main::a
```
bar calls the function "foo()", so foo's data is added to the stack:
```
1012    0000    XXXX
1008    0005    foo::a
1004    0004    bar::a
1000    0007    main::a
```
As you can see, the stack maintains the data for main and bar, even though foo is the "active" function. Once foo is done executing, all data associated with foo is removed from the stack:
```
1012    0000    XXXX
1008    0005    XXXX
1004    0004    bar::a
1000    0007    main::a
```
While memory address 1008 is no longer associated with foo::a, the data is not zeroed out. bar is the next function to end, so its data will be popped off the stack next:
```
1012    0000    XXXX
1008    0005    XXXX
1004    0004    XXXX
1000    0007    main::a
```
The only function left is main, at which point the program is done executing, and all data associated with the program is deallocated.  
  
While the stack offers fast access and manages memory usage for the programmer, it is limited in size, and less flexible when allocating large amounts of memory due to access to the stack being in a specific order. Additionally, there may be instances where data needs to last longer than the lifetime of the function that creates it, but does not need to last the lifetime of the program (i.e., the variable is a poor candidate to be global or static).

### Heap
To overcome the shortcomings of the stack, the heap is used. The heap is the largest area of memory allocated for a computer program (theoretically it could be the size of RAM minus what is needed for the stack, data, and text areas). While conceptually heap is often shown as growing from the bottom to the top of its "container", heap can actually allocate space anywhere, at any time. This makes it a much more flexible storage area than the stack. However, it also makes it slower to access, as the heap must be searched for an area large enough to hold the amount of data being requested. However, the heap makes runtime allocation of data possible, such as for dynamic arrays.  
  
## Pointers
A pointer, as stated in the introduction, is a variable that holds a memory address. The pointer variable is allocated on the stack, and is the widest (i.e., most bits possible) unsigned integer. The actual width varies based on the system, but most modern systems use x64 architecture and can support 8-byte (64-bit) integer types. You can use pointers in two ways: to references an existing variable on the stack or to create new data on the heap. We'll discuss the mechanisms for both in the coming subsections.

### Pointers to Stack Allocated Variables
Sometimes it may be necessary to reference a local variable in another location of the program, such as in another function (note that pass-by-reference has eliminated many of the use cases for pointers to local variables). Since the local variable's lifetime is managed by the call stack, pointers to variables cannot be deleted (this will result in a runtime error). Below is an example of using pointers to access local variables.
```C++
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = *temp;
}

int main() {
    int x = 5;
    int y = 2;
    // we use the & to access the variable's memory address
    int *a = &x;
    int *b = &y;
    swap(a, b);
    // we could also pass the memory addresses directly
    swap(&x, &y);
    return 0;
}
```
Let's look at the call stack for this program.  When the program starts execution, the main function's local variables are pushed onto the stack:
```
1020    --------    ----
1016    main::*b    1004
1012    --------    ----    # remember that our pointers are using 8 bytes of memory
1008    main::*a    1000    # *a contains x's memory address
1004    main::y     2
1000    main::x     5
```
Next, when `swap()` is called, its parameters are pushed onto the stack:
```
1036    --------    ----
1032    swap::*b    1004    # value of main::*b is copied to swap::*b
1028    --------    ----
1024    swap::*a    1000    # value of main::*a is copied to swap::*a
1020    --------    ----
1016    main::*b    1004
1012    --------    ----
1008    main::*a    1000
1004    main::b     2
1000    main::a     5
```
Next, a local variable `int temp` is created in `swap()`. It is assigned the value `*a`, which means that the pointer `a` is being dereferenced. Rather than assigning the memory address that a holds (1000) to `temp`, the value at memory address 1000 is saved in temp, which is 5.
```
1040    swap::temp  5       # temp holds the value saved at address 1000
1036    --------    ----
1032    swap::*b    1004
1028    --------    ----
1024    swap::*a    1000
1020    --------    ----
1016    main::*b    1004
1012    --------    ----
1008    main::*a    1000
1004    main::b     2
1000    main::a     5
```
Next, the statement `*a = *b` saves the value saved at address 1004 into the memory at 1000:
```
1040    swap::temp  5      
1036    --------    ----
1032    swap::*b    1004
1028    --------    ----
1024    swap::*a    1000
1020    --------    ----
1016    main::*b    1004
1012    --------    ----
1008    main::*a    1000
1004    main::b     2       
1000    main::a     2       # the value at address 1004 is saved in address 1000
```
Then, the value of `temp` is saved at address 1004:
```
1040    swap::temp  5      
1036    --------    ----
1032    swap::*b    1004
1028    --------    ----
1024    swap::*a    1000
1020    --------    ----
1016    main::*b    1004
1012    --------    ----
1008    main::*a    1000
1004    main::b     5       # the value of temp is saved in address 1004
1000    main::a     2       
```
Now, the `swap()` function has completed, and its local variables are popped off the stack:
```
1040    xxxxxxxx      5      
1036    xxxxxxxx    ----
1032    xxxxxxxx    1004
1028    xxxxxxxx    ----
1024    xxxxxxxx    1000
1020    --------    ----
1016    main::*b    1004
1012    --------    ----
1008    main::*a    1000
1004    main::b     5       # the value of temp is saved in address 1004
1000    main::a     2       
```

### Raw Pointers
A pointer that creates new memory on the heap is often called a "raw pointer". Memory for the pointer must be allocated using the `new` operator. Anytime memory is allocated using `new`, it must be freed using `delete`. Below is a basic example of creating a raw pointer:
```C++
int main() {
    // use the new keyword, followed by the type
    // to allocate memory
    int* ptr = new int;
    // assigning the value 5 to the memory location
    // referenced by ptr
    *ptr = 5;
    // freeing the memory used by ptr
    delete ptr;
    return 0;
}
```
Let's look at the memory usage by this example. Now, we need to track the usage on the stack and heap:
```
Heap
2000    XXXX    0000

Stack
1004    -----       ----- 
1000    main::*ptr  2000
```
First, the pointer is allocated on the stack. It then takes the first available memory address in the heap. In this example, we'll say that 2000 is the first available location that can hold an `int` in the heap.
```
Heap
2000    XXXX        0005

Stack
1004    -----       ----- 
1000    main::*ptr  2000
```
Next, the value at address 2000 is updated to store the value 5. 
```
Heap
2000    XXXX        0005

Stack
1004    -----       ----- 
1000    main::*ptr  0005
```

## Dynamic Arrays
A dynamic array uses a pointer to allocate an array on the heap. Static arrays are reserved on the stack by the compiler. This is why the size of a static array must be known at compile time; the compiler must approximate the maximum amount of memory to reserve for the program's stack. Since the heap does not have limited size (except for the literal constraint of how much memory the computer has available), dynamic arrays are the only way to create an array when the size is not known at compile time.  
  
Arrays are created using the syntax `DataType *arr = new DataType[size];`, where `size` is the number of elements the array needs to hold. To free the memory used by the array, the `delete[]` operator must be used. You cannot free the memory of an array using `delete`. Conversely, the `delete[]` operator cannot be used to free a pointer to a single element. Below is an example of creating and using a dynamic array.
```C++
#include <iostream>

int main() {
    double *scores;
    int size;
    std::cout << "Enter number of scores: ";
    std::cin >> size;
    scores = new double[size];
    for (int i = 0; i < size; ++i) {
        std::cout << "Enter score " << i + 1 << ": ";
        std::cin >> scores[i];
    }
    delete[] scores;
    return 0;
}
```

## Common Memory Errors
There are several runtime errors that you may encounter when working with dynamic memory allocation in C++. In this section we'll describe the common causes of these errors, so you know what to look out for when trying to fix them.

- **Segmentation fault (core dumped)**: This is one of the most common errors encountered in C/C++ programming. Segmentation faults (often abbreviated to segfaults) occur when a program makes a request to memory that it does not hold. A segfault can be trivially created by trying to assign a value to raw pointer without using `new` first.

- **free(): invalid pointer**: This error is caused when a pointer that has not been allocated by `new` is deleted. Verify that any pointer that you call `delete` for has been allocated using `new` first.

- **free(): double free detected in tcache n**: This error occurs when a pointer that has already been freed has `delete` invoked on it a second time.

- **munmap_chunk(): invalid pointer**: This occurs when you try to `delete` a pointer to a variable on the stack. Since this memory is not supposed to be managed by the programmer, trying to free memory allocated on the stack is illegal and will create a program crash.

- 
