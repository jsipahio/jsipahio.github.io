#include "example.hpp"
#include <iostream>

int main() {
    unsigned examples = 0;
    std::cout << "How many examples do you want to see?\n";
    std::cin >> examples;
    for (unsigned i = 0; i < examples; ++i) printExample();

    return 0;
}
