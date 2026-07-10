# CSE234 Week 14: Inheritance 
Inheritance allows classes to, for lack of a better term, inherit data and operations from other classes. Inheritance also allows for C++ to implement run-time polymorphism. Inheritance is weird in C++ compared to pure object oriented languages like Java or C#. 

## Basic Inheritance
The basic syntax for C++ inheritance is to put a colon after the name of class doing the inheriting followed by the name of the class it inherits from. 
```cpp
class Base {};
class Derived : Base {};
```
Unlike most other languages, C++ has inheritance visibility specifiers. Classes can have `public`, `protected`, or `private` inheritance. By default, a class applies the `private` specifier. A struct will apply the `public` specifier. 

## Object Slicing
A problem in C++ inheritance, especially for programmers who are used to Java or C#, is object slicing. In C++, parameters are pass-by-value by default. If a pointer or reference needs to be passed, it must be done explicitly. C# and Java always pass class objects by reference. When a derived class object is passed when a base class parameter is expected, the additional properties and methods will be "sliced" off the object.
```cpp
class Animal {
public:
    Animal(std::string n) : name(n) {}
    virtual void makeSound() const {
        std::cout << "sound\n";
    }
    virtual std::string getType() const {
        return "Animal";
    }
private:
    std::string name;
};

class Cat: public Animal {
public:
    Cat(std::string n) : Animal(n) {}
    void makeSound() const override {
        std::cout << "meow\n";
    }
    void std::string getType() const override {
        return "Cat";
    }
}

void printAnimal(Animal animal) {
    std::cout << "Type: " << animal.getType() << "\n";
    animal.makeSound();
}

int main() {
    Cat cat("Whiskers");
    printAnimal(cat);

    return 0;
}
```
The output of this program would be:
```
Type: Animal
sound
```
