
#include <iostream>
#include <sys/types.h>

int factorial(int x) {
    int value = x <= 0 ? 1 : x;
    for (int i = x - 1; i > 0; --i) {
        value *= i;
    }
    return value;
} 

int factorialRecursive(int x) {
    if (x <= 1) return 1;
    else return x * factorialRecursive(x - 1);
}

int main(int argc, char **argv) {
    std::cout << factorialRecursive(atoi(argv[1])) << std::endl;
    return 0;
}
