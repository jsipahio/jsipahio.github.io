#include "example.hpp"

Example::Example() {
    data = 0;
}

Example::Example(int d) {
    data = d;
}

void Example::setData(int d) {
    data = d;
}

int Example::getData() const {
    return data;
}
