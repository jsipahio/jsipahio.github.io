# Source Code Style and Identifier Naming
### CSE238 - Data Structures and Algorithms

## Introduction
In this lecture we'll discuss source code style and naming. Program comprehension comprises 50-70% of software maintenance time [1]. I often say that "source code is for the humans". The compiler can handle making the binary executable neat and tidy for the computer. Your goal when writing code is to make it as understandable as possible. That's why we're going to discuss consistent styling rules, and especially naming. Studies have show that good identifier names can improve code comprehension drastically [2][3].  
These are the style rules you should adhere to in this class. When writing code for yourself, you can make your own rules. However, when contributing to a codebase, you are typically expected to adhere to the existing style. Many open source projects have part of their "Contributing" instructions dedicated to acceptable code style.  

## Indentation
An indentation of 4 spaces should be used for each level of nesting. All text editors let you configure how many spaces your Tab key will insert. In VS Code, it is in the bottom right corner of the window. Anywhere you put a curly brace (with an exception) starts a new level of nesting. The indentation should be removed when reaching the close curly brace.  
**Examples:**
```C++
// top level statement, no indentation
int main() {
    // all statements in the function should be indented by 4 spaces
    std::string name;
    std::getline(std::cout, name);
    std::cout << "Hello, " << name << "!" << std::endl;
    if (name == "World") {
        // the if statement creates a new nesting level
        // indent 4 more spaces
        std::cout << "Wait a minute..." << std::endl;
    }
    // return to old level of indentation
    return 0;
}
```
The exception is with class access regions. Typically, these are not indented (but the statements after them are). See below:
```C++
class Example {
// public is at the same level of indentation as "class"
public:
    // the members are indented as normal
    Example();
private:
    int data;
};
```

## Blank Lines
Blank lines should be inserted between logical subtasks. If a statement is a sentence in C++, a subtask is like a paragraph. How many lines comprise a subtask varies based on the complexity of the task. Below are some examples:
```C++
```

## Comments
There are two main purposes of comments. To explain usage (documentary) or to explain intent. All functions and classes should have documentary comments explaining what they do, and in the case of functions what the parameters are for and what it returns. Anywhere you do something unusual, non-standard, or complicated, include a comment explaining your intent. Perhaps the weird way you wrote code is to improve time or memory performance. This provides justification to anyone reading the code later on as to what you did and why you chose to do it that way.
```C++
/**
*   Reverses contents of array in place
*   @param arr - array to be reversed
*   @param size - the number of elements in the array
*   @result the state of the parameter `arr` is modified to be in reverse order
*/
void reverse(int arr[], int size) {
    // successively swapping front and back of array until reaching middle
    // making a duplicate and copying back-to-front would be simpler
    // conceptually, but this uses less memory and 1/4 the operations
    for (int i = 0; i < size / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}
```
Before the function, I put a documentation comment. I used the format for a tool called Doxygen. Doxygen goes through code and finds all these comments, which it can then use to generate documents about the code. You don't have to use this style, but it's pretty much the standard for C++. It also makes the tooltip you get when you hover over a function nicer. The important thing to note is that your documentary comment should have a summary of the method, a description of each of its parameters, and a statement describing the return value or side-effect of the function.  
Inside the function `reverse`, I put some normal line comments, the ones that start with the double forward slash, that describe how I implemented the function. Conceptually, it's much easier to reverse an array by creating a duplicate array, then copying the duplicate array over the old array backwards. However, this requires two copying operations and the extra memory to create a copy of the original array. If you swap the first and last element, then the second and second-to-last element, third and third-to-last element, etc. until you reach the middle, this will reverse the array contents too. And notice that I only have to loop through half the array to do so, rather than looping through the whole array twice. Finally, I'm only creating one extra integer, rather than a whole new array, which is a significant reduction in memory used. So, the comment I put in the code justifies why I used a less obvious solution, and what solution I went with.  
Documentary comments are meant for people using the function. To understand how to use a function and what it does, someone should only have to read the documentary comment. They should not have to look at the source code. The inline intent comments are meant more for people modifying the code who need to understand exactly how the function works.  
Comments for classes are simpler. Primarily, you are trying to explain what the class is and what its role in the system is.  
Note: I cannot stand trailing comments and will mark off points if I see them. Comments should go on their own line.

## Braces
The preferred style for curly braces is to place the opening brace on the same line as the statement that it is associated with. A study has shown that placing the opening brace on the same line reduces cognitive load [4]. The closing brace should be on a line by itself.
```C++
// opening brace on same line as int main()
int main() { 
    std::cout << "Hello World!" << std::endl;
    return 0;
}
// closing brace on its own line
```

## Declarations
Each variable should be declared on its own line. Avoid statements like `int x, y;`. I don't have much else to say about this other than the language shouldn't even support it as a feature.

## Naming
Naming is one of, if not the most, important parts of writing high quality source code. Therefore, we will spend a significant amount of time discussing identifier naming. A survey of 1162 professional software developers [5] demonstrated the community interest in the issue of naming (1162 is a very high response rate for a survey) and determined the importance of name styling rules for methods. Many of these rules are generalizable to other source code identifiers, as well. 

#### Naming Style
The naming style (camelCase, PascalCase, snake_case) should follow the language standard and be consistent throughout the project. In most C++ projects, functions, fields, parameters, and local variables use the camelCase style. User-defined types (classes, structs, enums, etc.) should use PascalCase. Global constants should use SCREAMING_SNAKE_CASE (local constants should still use camelCase).

#### Dictionary Terms
Identifier names should consist of dictionary terms, and avoid abbreviations (unless the abbreviation is extremely common and well known, such as IP for Internet Protocol). By extension, slang terms and idioms should be avoided. Single letters should be avoided, except in the case of loop counter variables, such as `int i`. When we get to generic functions and classes, single letters are also acceptable for template parameters: `template <typename T>`.

#### Prefix/Suffix
Names should avoid prefixes and suffixes. Legacy C-systems often used prefixes, since C did not have namespaces or classes. Since C++ supports these, prefixes are not longer needed.  
Note: An old standard in C/C++ was to use a trailing underscore for struct (and later class) fields, such as `const char *text_;`. I cannot stand this and will definitely mark off points for it if I see it in your code.  

#### Length
Names should be long enough to describe what the identifier's purpose is, but not too long to overwhelm short term memory. Generally, all identifiers should be shorter than 7 words. User defined type names should be even shorter, 3-4 words at most.  
Note: Functions used for testing code (testing will be covered next week) can break this rule. Test code is not part of the system, and follows different standards. Test code should prioritize descriptiveness over memorability.

#### Grammar
Source code grammar is different from English prose. Identifiers should follow English grammar patterns, but not strictly. For example, `bool isVowel(char letter);` is an acceptable function name. It follows the typical question grammar of a verb followed by a noun. However, it is not a valid English sentence, since it missing a subject and articles. To be strictly correct, the name would be `isItAVowel` or `isThisLetterAVowel`, however, this is more verbose than what is needed to be understandable as a source code entity. On the other hand, totally breaking grammar patterns can make the name unreadable, such as `vowelIs`. This name makes no sense.  
In addition to following grammar patterns, certain categories of names should follow specific grammar patterns. Functions and methods are expected to be verbs or verb phrases. User defined type names, fields, parameters, constants, and local variables should be nouns or noun phrases.  
There are a couple of exceptions. Boolean variables can be verb phrases, since they are often asking a question: `bool isOpen = connection.connect();`. Getter methods, sometimes called properties, may be nouns or noun phrases. For example, `std::string` has a member function `length()` that returns the string's length. Note that it is just called `length()` rather than `getLength()`. For simple accessors and mutators, the verbs `get` or `set` may be redundant and can be dropped. This is seen with many Standard Template Library data types. For example, `std::string` does not have a function called `getLength()`, it is just called `length()`.

