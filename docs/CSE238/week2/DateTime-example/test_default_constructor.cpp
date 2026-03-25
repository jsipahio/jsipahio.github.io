#include "DateTime.hpp"
#include <cassert>
#include <iostream>

void test_default_constructor() {
    DateTime dateTime;
    assert(dateTime.year() == 1970);
    assert(dateTime.month() == 0);
    assert(dateTime.day() == 1);
    assert(dateTime.hour() == 0);
    assert(dateTime.minute() == 0);
    assert(dateTime.second() == 0);
}

int main() {
    std::cout << "Testing DateTime::DateTime()..." << std::endl;
    test_default_constructor();
    std::cout << "Tests passed for DateTime::DateTime()" << std::endl << std::endl;
    return 0;
}
