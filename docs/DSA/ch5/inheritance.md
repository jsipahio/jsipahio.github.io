# Inheritance
Inheritance is the mechanism used to enable runtime polymorphism in C++. When a class inherits from another class, the data and methods of the class being inherited from automatically become members of the derived class. This allows classes to extend or implement the behavior of other classes. Inheritance is not a super important topic for this class, so we will only cover it briefly. We will get more mileage out of templates and generic types, which are compile-time polymorphism.

## Terminology
- Base Class - The class being inherited from. Also called super class or parent class.
- Derived Class - The class doing the inheriting. Also called subclass or child class.

## Basic Example
```cpp
class Pet {
public:
    // Default constructor
    Pet(): name{}, age{}, isVaccinated(false), isSpayed(false) {}
    // Constructor
    Pet(const std::string& n, int a, bool v, bool s):
        name(n), age(a), isVaccinated(v), isSpayed(s) {}
    // no dynamic memory, don't need big 3
    // however, it is smart to always make a virtual destructor
    // for classes that may be inherited from
    virtual ~Pet() = default;

    // getters/setters
    std::string getName() const { return name; }
    int getAge() const { return age; }
    bool getVaccinationStatus const { return isVaccinated; }
    bool getSpayedStatus const { return isSpayed; }
    void setName(const std::string& value) { name = value; }
    void setAge(int value) { age = value; }
    void setVaccinationStatus(bool value) { isVaccinated = value; }
    void setSpayedStatus(bool value) { isSpayed = value; }

    // other methods
    virtual void makeSound() const { 
        std::cout << "sound;\n";
    }

protected:
    std::string name;
    int age;
    bool isVaccinated;
    bool isSpayed;
};

class Dog: public Pet {
public:
    // Default constructor
    Dog(): Pet() {}
    Dog(const std::string& n, int a, bool v, bool s) : Pet(n, a, v, s) {}
    void makeSound() const override {
        std::cout << "woof\n";
    }
};

class Cat: public Pet {
public:
    // Default constructor
    Cat(): Pet() {}
    Cat(const std::string& n, int a, bool v, bool s) : 
        Pet(n, a, v, s), isDeclawed(false) {}
    Cat(const std::string& n, int a, bool v, bool s, bool d) : 
        Pet(n, a, v, s), isDeclawed(d) {}

    bool getDeclawStatus() const { return isDeclawed; }
    void setDeclawStatus(bool value) { isDeclawed = value; }

    void makeSound() const override {
        std::cout << "meow\n";
    }
private:
    bool isDeclawed;
};

int main() {
    Pet pet("Rick", 3, true, true);
    // prints: sound
    pet.makeSound();
    
    Dog dog("Fido", 6, true, true);
    // prints: woof
    dog.makeSound();
    // dog can access methods of base class Pet
    std::string dogName = dog.getName();

    Cat cat("Whiskers", 2, true, true, false);
    // prints: meow
    cat.makeSound();
    // cat has additional methods added to it
    bool isCatDeclawed = cat.getDeclawStatus();

    return 0;
}
```
There are a few things that are new in here:   
- The `Pet` class is using initializer lists for its constructors. You have likely seen these before, but in case you haven't, initializer lists are used to set the fields of a class. `name(n)` is the same as putting `name = n;` in the body of the constructor
- The `name{}`, `age{}`, etc. syntax tells the compiler to initialize these fields with their default values. For integers, it is 0. For a string, it is the empty string value
- The getters and setters are all normal, but we now have a destructor and member function marked as `virtual`. This tells the compiler that derived classes can implement this function for the base class. We'll discuss what this means in a later section.
- The member variables of the class `Pet` are `protected`. The `protected` visibility means that derived classes are able to directly access these members, but they cannot be accessed outside the class (like `private`). Members that are `private` in a base class are never visible in child classes.
- The `Dog` and `Cat` class inherit from the `Pet` class via the `: public Pet` after their names. We'll discuss why `Pet` is public in the next section.
- The `Dog` and `Cat` class mark the `makeSound()` function as `override`. This tells the compiler to make sure a corresponding `virtual` method exists in the base class being inherited from. 
- The `Cat` class adds additional data and methods for if the cat is declawed.

## Access Specifiers
We've seen that classes in C++ have access regions like `public:` and `private:`, as well as now `protected:`. To review, `public:` members are accessible internally to the class, by subclasses, and by objects of the class declared outside the class. `private:` members are only visible inside the class they are declared in. Objects cannot access them, and neither can subclasses. The `protected:` region sits in-between, where objects outside the class still cannot access these members, but subclasses can.  
  
On top of the access regions, C++ adds another layer of visibility modification. When inheriting from a class, the access can be marked as `public`, `protected`, or `private`. `public` inheritance is what you would be used to if you know inheritance in Java or C#, the public members of the base class are still public in the derived class. The `protected` modifier makes public members of the base class protected in the derived class. Therefore, derived class objects can no longer call public member functions or access public fields of the base class. The `private` specifier makes everything in the base class private to the subclass, regardless of whether it is public or protected. Below is a table showing the relationship between the access specifiers.  
  

<table>
    <thead>
        <tr>
            <th rowspan=2>Visibility Region</th>
            <th colspan=3>Inheritance Spcifier</th>
        </tr>
        <tr>
            <th>private</th>
            <th>protected</th>
            <th>public</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th>private</th>
            <td>Inaccesible</td>
            <td>Inaccesible</td>
            <td>Inaccesible</td>
        </tr>
        <tr>
            <th>protected</th>
            <td>Inaccesible</td>
            <td>Protected</td>
            <td>Protected</td>
        </tr>
        <tr>
            <th>public</th>
            <td>Inaccesible</td>
            <td>Protected</td>
            <td>Public</td>
        </tr>
    </tbody>
</table>

## Virtual Methods
The main reason to use inheritance, outside potentially saving some lines of code, is to enable runtime polymorphism. But how does C++ actually handle this? C++, along with most languages that support inheritance, use a virtual method table (VMT) to track which methods in a class are virtual. Then, when it finds a reference to a class that is derived from, it checks which version of the virtual method to call. Assume the `Pet`, `Dog`, and `Cat` classes are visible in this code snippet:
```cpp
int main() {
    // runtime polymorphism is achieved with pointers
    // and pass-by-reference parameters
    Pet *pet;
    // to make pet behave like a dog, we create a 
    // Dog object using the Pet type pointer
    pet = new Dog("Fido", 6, true, true);
    // since pet's base type is Pet*, the VMT needs
    // to be checked to see if there is an overload
    // of the makeSound() function to be used instead
    pet->makeSound();
    // this prints: woof
    // this is since the VMT sees that pet is assinged to
    // a Dog object, and Dog overrides the virtual method makeSound

    delete pet;
    return 0;
}
```
If we had not declared `makeSound()` as a virtual method, when calling `pet->makeSound()`, `sound` would have been printed. Unlike Java, where all methods are virtual by default, in C++ you have to explicitly tell the compiler you want the method to be virtual by using the `virtual` specifier.  

## Pure Virtual, Abstract Classes, and Interfaces
In the `Pet` class, we added an implementation to the `makeSound()` virtual method. However, since we have no knowledge of what sound the pet might make, it just prints `sound`. We could also have left the body empty and had a function that does nothing. However, in some cases we may want to force subclasses to implement a method. In that case, we can make the function pure virtual. To do so, instead of providing a body, we set the function equal to 0:
```cpp
class Pet {
public:
    // ...
    virtual void makeSound() = 0;
protected:
    // ...
};
```
This automatically makes `Pet` an "abstract class". We can no longer directly create an object of the class Pet, because it has an unimplemented function. We can still use `Pet` to create pointers that we assign references of subclass objects that implement `makeSound()`. We can also have pass-by-reference parameters of type `Pet&`.
```cpp
// this is okay, it is a reference
void printPet(const Pet& pet) {
    // ...
}

int main() {
    // this is not allowed, Pet is abstract
    // Pet pet1;
    // this is allowed, it is a pointer
    Pet *pet2;
    // this is not allowed, we are setting 
    // pet2 to an instance of Pet
    // pet2 = new Pet{};
    // this is allowed, Dog implements makeSound()
    Pet *pet3 = new Dog{};
    // this is allowed, Cat implemnets makeSound()
    Pet *pet4 = new Cat{};
    // we can still create subclass objects:
    Dog dog;
    Cat cat;
    // and pass them to functions that expect
    // a reference to a Pet object
    printPet(dog);
    printPet(cat);

    delete pet3;
    delete pet4;
    return 0;
}
```

## Conclusion
There is a lot more that can be said about inheritance in C++, but that is not a topic for this course. This is just a basic overview of what inheritance is and how you can use it.
