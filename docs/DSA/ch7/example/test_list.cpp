#include <iostream>
#include "list.hpp"

int main() {
    List<int> list;

    for (int i = 0; i < 10; ++i) {
        list.insertBack(i);
    }

    for (int& x: list) {
        x *= 2;
    }

    for (int x: list) {
        std::cout << x << std::endl;
    }

    return 0;
}