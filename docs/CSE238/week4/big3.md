# C++ Big 3 Semantic
Unlike many other modern programming languages (C#, Java, Python), C++ allows for direct access to memory locations via pointers. When pointers are members of classes, it can create problems when allowing the compiler to automatically implement copy constructors, destructors, and assignment operators for a class. Recall this fact about pointers:
```C++
int main() {
    // declare an integer pointer
    int *ptr;
    // ptr is a reference to a single integer
    ptr = new int;
    delete ptr;
    // ptr is now a reference to a dynamic array
    ptr = new int[10];
    delete[] ptr;
    return 0;
}
```
As you can see, `ptr` can either be a reference to a single integer in memory, or an array of integers. This directly impacts which version of `delete` must be used to clean up the memory allocated for `ptr` in the heap. The compiler has no way to determine which version of `delete` to call in a destructor, making it impossible to effectively clean up an object that contains dynamic fields. Thus, implementing a destructor is required for any class that contains dynamic fields.  
Copying also presents a challenge. Consider the following example:  
```C++
int main() {
    int a = 4;
    int *x = &a;
    int *y = x;
    *y = 6;
    // now, a == 6
    // *x == 6
    // and *y == 6
    *x = 3;
    // now a == 3
    // *x == 3
    // and *y == 3
    return 0;
}
```
This example illustrates that pointers are references to a memory address. When we assign a pointer to another pointer, both pointers have ownership over that memory address. 