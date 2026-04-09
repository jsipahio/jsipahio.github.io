# Glossary
### CSE238 - Data Structures and Algorithm
An updated version of this glossary will be included with each week to reflect new terms I introduce. If I say or write something during a lecture, and you don't know what it means, try checking here first.

- **Build** - A combination of dependency management, compilation, and linking required to produce the desired program or library.
- **Compile** - The process of converting source code to machine executable code (binary).
- **Compiler** - A computer program that takes source code as input, and generates binary machine code as output.
- **Directory** - Another term for folder in a file system. Usually, when talking about terminal environments, the word directory is preferred to folder.
- **Executable** - A computer program. When we compile code into an executable, we intend for a user to run the program and use it.
- **git** - A distributed version control system that is the dominant version control system in modern software development.
- **GitHub** - A frontend and host for git repositories. GitHub is not git, it uses git as a version control system. Additionally, it provides added features like access control, bug tracking, issue tracking, etc. 
- **Identifier** - An identifier refers to a name in a software system. The names you give functions, variables, and classes are all identifiers.
- **Library** - A collection of binary code to be used in other programs. Libraries do not have `main` functions, and cannot be "run" like an executable. They are precompiled code that we can link into other programs or libraries later.
- **Linking** - In programs with multiple source code files, each file must be compiled to binary individually. Then, these files are *linked* into the target output, either an executable or library.
- **Preprocessor** - C/C++ compilers use a preprocessor as part of the build process. An example preprocessor directive is `#include`. When the compiler encounters `#include <some_library>`, it searches for the code for that library and copies it into the source code file. Then, it compiles the source code of both the included header and source code into one file.
- **Refactoring** - The process of modifying the structure of source code in a way that does not impact functionallity. Typically, refactorings are done to improve the quality and/or readability of the code without impacting its use.
- **Side Effect** - A function may cause a change of state of the system by modifying the value of one of its parameters, the object that is calling it, or by modifying a global variable. These changes are called the "side effects" of a function. Some programming paradigms, such a Functional Programming, make it a rule to avoid side effects altogether. 
