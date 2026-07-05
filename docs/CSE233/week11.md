# CSE233 Week 11: User Defined Data Types (Enums, Structs, and Classes)
Throughout the course we have been using the predefined data types provided by C++, such as int, double, and std::string. This week, we will discuss the mechanisms provided by C++ for creating our own data types. First, we'll discuss enums, which provide a way to group global constant values. In the past couple weeks we've used arrays, which allow you to create collections of the same data type. Structs and classes allow you to create your own data types with different underlying data types.

## Enums
Enums assign human-readable names to integral constants. C++ has two types of enum, the classical C enum, and the more modern enum class. First, let's look at a C enum:
```cpp
enum Day { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
```
Under the hood, the value 0 is assigned to SUNDAY, 1 is assigned to MONDAY, 2 to TUESDAY, and so on. The same code is roughly equivalent:
```cpp
const int SUNDAY = 0;
const int MONDAY = 1;
const int TUESDAY = 2;
const int WEDNESDAY = 3;
const int THURSDAY = 4;
const int FRIDAY = 5;
const int SATURDAY = 6;
```
Enums provide a convenient way to create named constants to represent a group of related values. 

## Structs
A struct (short for structure) is a composite data type. A struct consists of member variables, called fields, that are stored within each instance of the struct. Below is an example struct:
```cpp
struct RGBColor {
    int red;
    int green;
    int blue;
};
```
A struct declaration consists of the `struct` keyword, followed by the name of the struct and a block. The block contains the struct's fields. The struct ends with a semicolon. The above struct has three fields, which are all integers. RGB (red, green blue) color is the predominant way of storing colors in digital formats, with values between 0 and 255 assigned to each color channel to form a single pixel. However, the fields of a struct do not have to have the same data type:
```cpp
struct Student {
    std::string firstName;
    std::string lastName;
    int creditHours;
    double gpa;
};
```
The student struct consists of two strings for a student's first and last name, an int for the number of credit hours completed, and a double for the student's GPA. To declare a struct variable, we use the name of the struct as any other data type:
```cpp
Student student;
```
We can access the fields of the struct using the dot operator:
```cpp
Student student;
student.firstName = "John";
student.lastName = "Doe";
student.creditHours = 60;
student.gpa = 3.1;
```
When creating the struct, we can also use an initializer list to provide initial values to the struct variable's fields. The initializer list is a set of curly braces with values separated by commas. The values passed to the initializer list are assigned to the struct's fields in the order they appear in the struct declaration. 
```cpp
// legal, firstName is "John", the rest are unassigned
Student student1 = {"John"};
// legal, firstName is "John" and lastName is "Doe"
Student student2 = {"John", "Doe"};
// legal, firstName is "John", lastName is "Doe", creditHours is 60
Student student3 = {"John", "Doe", 60};
// legal, firstName is "John", lastName is "Doe", creditHours is 60, gpa is 3.1
Student student4 = {"John", "Doe", 60, 3.1};
// illegal, will try to store 3.1 in an int (creditHours), which can't be done
Student student5 = {"John", "Doe", 3.1};
```
For the most part, structs can be used like any other primitive type. They can be used as both return types and parameters to functions. You can also create arrays of structs:
```cpp
#include <iostream>

struct Student {
    std::string firstName;
    std::string lastName;
    int creditHours;
    double gpa;
};

void printStudent(const Student &student) {
    std::cout << "Name:    " << student.firstName 
        << " " << student.lastName << "\n";

    std::cout << "Credits: " << student.creditHours << "\n";
    std::cout << "GPA:     " << student.gpa << "\n";
}

int main() {
    Student students[10];

    std::cout << "Enter student information: \n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "Enter first name: ";
        std::cin >> student[i].firstName;
        std::cout << "Enter last name: ";
        std::cin >> student[i].lastName;
        std::cout << "Enter credit hours: ";
        std::cin >> student[i].creditHours;
        std::cout << "Enter GPA: ";
        std::cin >> student[i].gpa;
    }

    std::cout << "You entered\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "\nStudent " << i + 1 << " -----------\n"
        printStudent(students[i]);
        std::cout << "---------------------\n";
    }

    return 0;
}
```
The only thing we can't do with structs is use operators like +, -, ==, <, >, etc. on them, or directly print them using `std::cout <<` or similar. Next week, we will discuss operator overloading, which will allow us to use these operators for structs. 

## Classes
A class is very similar to a struct (in C++, they are basically the same, but programmers use them differently). The main difference is how they are used. Structs are used to store simple data with few or no operations. All data in a struct is public, by default. In a class, data and member functions are private, by default. The `public:` region specifier must be used to make fields and member functions usable outside the class. Below is a basic class:
```c++
class Student {
public:
    std::string firstName;
    std::string lastName;
    int creditHours;
    double gpa;
};
```
In this case, we've made all the fields public, so this class is basically the same as a struct. 

### Constructors
A constructor is special function that classes have to create new objects. Constructors are member functions with no return type and the same name as the class. The constructor is called whenever an object is created.

### Accessors
An accessor is a function used to access the values of a class's fields. The 

## Comparing Structs and Classes
Technically speaking, there is almost no difference between a struct and class in C++. The main difference to most programmers is that everything is public by default in a struct, while everything is private by default in a class. There are some low-level differences when dealing with backwards compatibility with C code, but for the sake of this course a struct and class can do the same things. Despite this, C++ programmers generally use structs and classes in different ways. When a programmer-defined data type is only being used to store simple data with few or no operations, structs are typically used. When the inner data is more complex or has more complex relations (where private visibility is needed), classes are preferred. Classes are also used when a type has many operations defined for it. 

## Conclusion
