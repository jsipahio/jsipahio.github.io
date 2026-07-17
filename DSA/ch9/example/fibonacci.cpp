#include <iostream>
#include <sys/types.h>

int fibonacci(int x) {
    int value = 0;
    int prevValue = 1;
    int prevPrevValue = 0;
    for (int i = 1; i <= x; ++i) {
        value = prevValue + prevPrevValue;
        prevPrevValue = prevValue;
        prevValue = value;
    }
    return value;
}

int fibonacciRecursive(int x) {
    if (x <= 1) return 1;
    else return fibonacciRecursive(x - 1) + fibonacciRecursive(x - 2);
}

int main(int argc, char **argv) {
    std::cout << fibonacciRecursive(atoi(argv[1])) << std::endl;
    return 0;
}