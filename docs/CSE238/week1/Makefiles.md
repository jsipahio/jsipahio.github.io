# Multifile Projects and Makefiles
### CSE238 - Data Structures and Algorithms

Up until this point you've primarily written all of your code in a single file. However, as the size of projects grow, this becomes untenable. Projects with thousands to millions of lines of code need to be separated into multiple files, or even into many files in multiple directories. First, we'll look at manually compiling a 3-file C++ project, then look at how a Makefile can streamline the process.

## How to break up a file
Let's look at the example code below. (For brevity, comments explaining the code are excluded.)  
*BankAccountProgram.cpp*
```C++
#include <string>
#include <iostream>

class BankAccount {
public:
    BankAccount();
    BankAccount(double startingBalance, std::string name);

    std::string getAccountHolder() const;
    double getCurrentBalance() const;

    void transferOwnership(std::string name);
    void deposit(double amount);
    bool withdraw(double amount);
private:
    double balance;
    std::string owner;
};

std::ostream& operator<<(std::ostream& out, const BankAccount& account);

int main() {
    BankAccount account(1000, "John Doe");
    std::cout << account << std::endl;

    account.deposit(500);
    std::cout << account << std::endl;

    account.transferOwnership("Jane Doe");
    std::cout << "New owner: " << account.getAccountHolder() << std::endl;

    if (account.withdraw(1000)) {
        std::cout << "Successfully withdrew $1000" << std::endl;
        std::cout << "New balance: $" << account.getCurrentBalance() << std::endl;
    }
    else {
        std::cout << "Insufficient funds to withdraw $1000" << std::endl;
        std::cout << "You are $" <<>> 1000 - account.getCurrentBalance() << " short" << std::endl;
    }

    return 0;
}

BankAccount::BankAccount() {
    balance = 0;
    owner = "";
}

BankAccount::BankAccount(double startingBalance, std::string name) {
    balance = startingBalance;
    owner = name;
}

std::string BankAccount::getAccountHolder() const {
    return owner;
}

double BankAccount::getCurrentBalance() const {
    return balance;
}

void BankAccount::transferOwnership(std::string name) {
    owner = name;
}

void BankAccount::deposit(double amount) {
    if (amount < 0) {
        std::cerr << "Invalid deposit - should not be negative! Abort..." << std::endl;
        exit(1);
    }

    balance += amount;
}

bool BankAccount::withdraw(double amount) {
    if (amount < 0) {
        std::cerr << "Invalid withdrawl - should not be negative! Abort..." << std::endl;
        exit(2);
    }

    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    else return false;
}

std::ostream& operator<<(std::ostream& out, const BankAccount& account) {
    out << "Balance: " << account.getCurrentBalance() << std::endl;
    out << "Owner:  " << account.getAccountHolder() << std::endl;
    return out;
}

```
As you can see, we have a class declaration for `BankAccount` at the top of the file. We also have a free function to overload the insertion operator (for printing). I could have made this a friend, but since I don't need direct access to any private members (I have getters for both of them), I chose to avoid making it a friend. In general, I recommend avoiding friend functions whenever possible. Following this, we have the `main` function, which plays around with a `BankAccount` object called `account`. Then we have the implementation of the `BankAccount` methods.  
In C++, it is an accepted pattern for each class to have its own header and implementation file. The `main` function should also be in its own file. Since the free function for `operator<<` is strongly coupled with the `BankAccount` class, I'll include its declaration and implementation with the class `BankAccount`. This suggests that we need three files for our program: one for the `main` function, one for the declaration of `BankAccount`, and one for the implementation of `BankAccount`. This refactoring is shown below.  
  
*BankAccount.hpp*
```C++
#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <string>
#include <iostream>

#include <string>
#include <iostream>

class BankAccount {
public:
    BankAccount();
    BankAccount(double startingBalance, std::string name);

    std::string getAccountHolder() const;
    double getCurrentBalance() const;

    void transferOwnership(std::string name);
    void deposit(double amount);
    bool withdraw(double amount);
private:
    double balance;
    std::string owner;
};

std::ostream& operator<<(std::ostream& out, const BankAccount& account);

#endif

```
*BankAccount.cpp*
```C++
#include "BankAccount.hpp"

BankAccount::BankAccount() {
    balance = 0;
    owner = "";
}

BankAccount::BankAccount(double startingBalance, std::string name) {
    balance = startingBalance;
    owner = name;
}

std::string BankAccount::getAccountHolder() const {
    return owner;
}

double BankAccount::getCurrentBalance() const {
    return balance;
}

void BankAccount::transferOwnership(std::string name) {
    owner = name;
}

void BankAccount::deposit(double amount) {
    if (amount < 0) {
        std::cerr << "Invalid deposit - should not be negative! Abort..." << std::endl;
        exit(1);
    }

    balance += amount;
}

bool BankAccount::withdraw(double amount) {
    if (amount < 0) {
        std::cerr << "Invalid withdrawl - should not be negative! Abort..." << std::endl;
        exit(2);
    }

    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    else return false;
}

std::ostream& operator<<(std::ostream& out, const BankAccount& account) {
    out << "Balance: " << account.getCurrentBalance() << std::endl;
    out << "Owner:  " << account.getAccountHolder() << std::endl;
    return out;
}

```
*main.cpp*
```C++
#include <iostream>
#include "BankAccount.hpp"

int main() {
    BankAccount account(1000, "John Doe");
    std::cout << account << std::endl;

    account.deposit(500);
    std::cout << account << std::endl;

    account.transferOwnership("Jane Doe");
    std::cout << "New owner: " << account.getAccountHolder() << std::endl;

    if (account.withdraw(1000)) {
        std::cout << "Successfully withdrew $1000" << std::endl;
        std::cout << "New balance: $" << account.getCurrentBalance() << std::endl;
    }
    else {
        std::cout << "Insufficient funds to withdraw $1000" << std::endl;
        std::cout << "You are $" << 1000 - account.getCurrentBalance() << " short" << std::endl;
    }

    return 0;
}

```
The header file was named using the name of the class, `BankAccount`, followed by `.hpp`. Since we are putting one class in each file, it makes sense to name them this way. We have a corresponding implementation file, `BankAccount.cpp`. The `main` function is in a file `main.cpp`. Sometimes, this file may be named after the overall program. Since this is a very basic example program, calling it `main.cpp` or `driver.cpp` is acceptable.  
In the header file, you may notice some lines that are unusual to you. The file begins with `#ifndef BANKACCOUNT_HPP` and `#define BANKACCOUNT_HPP`, and ends with `#endif`. These compiler preprocessor directives are called "include guards". Without getting into details of exactly how these work, they basically tell the compiler to ignore this code if it is already part of the executable it is building. This way, you do not accidentally include the same code more than once.  
  
In the `.cpp` source code files, you will see that we have `#include "BankAccount.hpp"`. Typically, when we have included files, we've used angle brackets `<>`. The angle brackets tell the compiler to search for standard library system headers that were included with the compiler. However, the double quotes tell the compiler to instead search the current directory first to find the included file. Also, note that we only ever include the `.hpp` file. You should never include a `.cpp` file.  
  
Otherwise, we've pretty much just copy-pasted the code for the `BankAccount` class declaration and `operator<<` function declaration into `BankAccount.hpp`. We copied the `main` function into `main.cpp`. And all the other function definitions were copied into `BankAccount.cpp`.

## Compiling our program
Let's turn our attention to compiling this program. We cannot simply compile `main.cpp` into an executable. We now need to individually compile both `.cpp` files into binary code, and then link them into a single executable. We do not need to compile `BankAccount.hpp`, as it is included by the `#include "BankAccount.hpp"` directives. Below are the commands to compile this program:
```Bash
g++ -c BankAccount.cpp -o BankAccount.o
g++ -c main.cpp -o main.o
g++ main.o BankAccount.o -o main
```
The first command compiles `BankAccount.cpp` into an intermediate binary called `BankAccount.o`. The next command does the same for `main.cpp`. We use the `-c` flag for `g++` to tell it that it is building an intermediate binary and not the full executable. This way, it will not panic when it does not find a `main` function in `BankAccount.cpp`, and does not find the function definitions for the `BankAccount` methods in `main.cpp`. The last command is used to link the intermediate binaries into a single executable, which we have called `main`. We do not use `-c` here, as we are now expecting all the required components of our program to be built into the `.o` files.    
  
While this may not be difficult for 3 files, it would be repetitive if we had to do it each time we need to recompile our program. Also, if we wanted to use additional compiler flags, like `-Wall`, or a specific standard, we'd have to remember to include them and spell them right in the command every time. We could write a BASH script to do this, but if we had a very large system, and only change one file, we'd be recompiling the whole system when only one or two files might need to be recompiled. This is the motivation for the `make` command and Makefiles.

## Makefile
Makefiles contain instructions to build executables and/or libraries. In this class, we are focussed on executable programs. Makefiles consist of *targets*, *dependencies*, *variables*, *comments*, *directives*, and *commands*. Makefiles are named `Makefile`. Below is the `Makefile` for the above Bank Account program.
```makefile
CPP=g++

# link main executable
main: main.o BankAccount.o
   $(CPP) main.o BankAccount.o -o main

# compile main.cpp
main.o: main.cpp BankAccount.hpp
    $(CPP) -c main.cpp -o main.o

# compile BankAccount.cpp
BankAccount.o: BankAccount.cpp BankAccount.hpp
    $(CPP) -c BankAccount.cpp -o BankAccount.o

# cleanup binaries
clean:
    rm -rf *.o main
```
The first line of the Makefile declares a **variable** called `CPP`, which we assign the name of our compiler, `g++` to. If we decide later on to use a different compiler, say `clang++`, then we'd only have to change that first line. We access the variable by wrapping it with parenthesis and putting a dollar sign in front of it.  
  
`main`, `main.o`, `BankAccount.o`, and `clean` are all **targets**. Targets always end with a colon, and are not indented. When running the `make` command, you can also provide one of these targets to tell it what to build. If you don't provide a target, it tries to build the first target by default.  
  
Each target is followed by a list of **dependencies** (except clean, which does not have any dependencies). These tell `make` that to build this target, these files have to exist. If the file does not exist, `make` will search for a target to build that file. If a matching target isn't found, `make` will stop and report an error. So, the `main` target requires `main.o` and `BankAccount.o` be built or existent. `main.o` requires `main.cpp` and `BankAccount.hpp`. And `BankAccount.o` is dependent on `BankAccount.cpp` and `BankAccount.hpp`. Note that `BankAccount.hpp` is only required for the `.o` files. Since `BankAccount.hpp` is included in those files, its code will already be built into the `.o` files, and thus is not required anymore to build `main`.  

The **commands** are the shell commands required to run the compiler to build the specified target. Here, we see the compiler commands we ran in the last section, only we've replaced the direct call to `g++` with our variable `$(CPP)`. Otherwise, they are the same commands.   
  
**Comments** in Makefiles start with the pound (#) symbol. The example above has comments above each command explaining their purpose.  
  
The only component we did not include is **directives**. Directives are special commands that `make` uses, and we will not need them in this course. Thus, I will not be covering them here.  
  
An advantage of using the Makefile is that we will not be recompiling `main.cpp` and `BankAccount.cpp` when we make a change to only one file. `make` can automatically detect which file was changed, and only recompile that file. The code for this example is provided in the `BankAccount-Example.zip` file on Brightspace, or you can download the files [BankAccount-Example](here). You can download it, unzip, and build it by running the `make` command. Then, try making a small change to one of the files (something simple, like fixing the typo in the `operator<<` function). Then run `make` again and see what happens.  

## Summary
In this lecture, we covered: refactoring C++ projects that use classes into multiple files, compiling projects that use multiple files, and creating Makefiles. You should now be prepared to tackle this week's lab, where you will be splitting a single file C++ program into multiple files and creating a Makefile to compile it.
