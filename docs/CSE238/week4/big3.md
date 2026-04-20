# C++ Big 3 Semantic
Unlike many other modern programming languages (C#, Java, Python), C++ allows for direct access to memory locations via pointers. When pointers are members of classes, it can create problems when allowing the compiler to automatically implement copy constructors, destructors, and assignment operators for a class.  
## Destructor
Recall this fact about pointers:
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
## Copy Constructor
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
This example illustrates that pointers are references to a memory address. When we assign a pointer to another pointer, both pointers have ownership over that memory address. This creates a problem when copying class fields that are pointers. The compiler's default implementation of a copy constructor is to blindly copy all the fields in the class. This is fine if none of the fields are pointers, since they are all copied by value. However, when copying a pointer by value, the new object will be created with a copy of the *memory address* the pointer is referencing, not a copy of the data the pointer is referencing. Below is an example of a (not so) smart pointer wrapper class that does not implement a copy constructor, and an example of what will happen when copying an object of the class:
```C++
#include <assert.h>
// the SmartPointer class is meant to handle automatic
// allocation and deletion of a raw pointer so users do not
// have to remember to call new and delete
class SmartPointer {
public:
    // default constructor allocates memory for the pointer
    SmartPointer() {
        ptr = new int;
    }
    // allocate memory and assign value
    SmartPointer(int val) {
        ptr = new int;
        *ptr = val;
    }
    // delete the pointer when the object goes out of scope
    ~SmartPointer() {
        delete ptr;
    }
    // allow accessing data with the * operator
    int operator*() const {
        return *ptr;
    }
    // allow assigning an int value to the pointer with =
    SmartPointer& operator=(int val) {
        *ptr = val;
    }
    // do not allow the object to be assigned to a raw pointer
    SmartPointer& operator=(int *other) = delete;
private:
    int *ptr;
};

int main() {
    // declare a smart pointer object
    SmartPointer ptr;
    // assign its value to 34
    ptr = 34;
    // create a copy of ptr
    SmartPointer copy(ptr);
    // assign copy's value to 56
    copy = 56;
    // the value of ptr is now 56 since
    // copy is a duplicate of the actual pointer
    // not the value
    assert(*ptr == *copy);
    return 0;
}
```

The implementation for the copy constructor provided by the compiler looks something like this:
```C++
SmartPointer::SmartPointer(const SmartPointer& other) {
    ptr = other.ptr;
}
```
In reality, when we create a *new* smart pointer object via copying, we are probably expecting just the value to be copied, and for the two pointer objects to be independent entities. Even worse, when both objects go out of scope and the destructor is call, delete will be called on the same pointer twice. This will create a program crash due to a double free. Therefore, we must implement the copy constructor ourselves to avoid multiple objects from referencing the same memory location:
```C++
SmartPointer::SmartPointer(const SmartPointer& other) {
    ptr = new int;
    *ptr = *other;
}
```
In this implementation, the copy constructor allocates memory for the pointer using `new`, and then assigns the pointer the value being held by the other pointer, rather than copying the pointer itself.   

## Assignment Operator
Next, we need to consider the assignment operator, `operator =`. We cannot simply copy the fields of the object on the right-hand side of the equal sign over to the left-hand object. When the class is using dynamically allocated memory, we need to ensure that the left-hand object's memory is freed before copying over data from the right-hand object.

### Copy and Swap Idiom
Defining an overloaded assignment operator the correct way allows the compiler to make several optimizations. The best way to overload `operator=` is to first create a separate member function that swaps two objects in constant time. Then, pass the right-hand object by value to `operator=`. This will invoke the copy constructor to create a copy of the right-hand object. Then, call the swap function inside `operator=`. This will swap the copy into the left-hand object, and whatever data was in the left-hand object into the parameter. Then, when the function ends, the destructor will be called on the parameter, which cleans up any old data in the left-hand object. Below is the `operator=` for the `SmartPointer` class.  
```C++
// first define a constant time swap
void SmartPointer::swap(SmartPointer &other) {
    // vacuously a constant time swap of pointers
    // if these were dynamic arrays swapping the pointers
    //  would save a lot of time
    int *temp = ptr;
    ptr = other.ptr;
    other.ptr = temp;
}
// you also need to return a reference to an object
// this way you can chain assignments: obj1 = obj2 = obj3;
SmartPointer& SmartPointer::operator=(SmartPointer rhs) {
    swap(rhs);
    return *this;
}
```
## Conclusion 
The data structures we implement going forward in this class will all be using dynamic memory, so you will need to implement the Big 3 for all of them.
