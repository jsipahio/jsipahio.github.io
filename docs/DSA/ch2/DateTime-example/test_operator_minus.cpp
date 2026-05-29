#include "DateTime.hpp"
#include <cassert>
#include <iostream>

void test_subtract_no_difference() {
    DateTime dt1;
    DateTime dt2;
    assert(dt1 - dt2 == dt2 - dt1);
    assert(dt1 - dt2 == 0);
}

void test_subtract_no_difference_not_default() {
    TimeParts parts = {};
    parts.tm_year = 2000 - 1900;
    parts.tm_mon = 3;
    parts.tm_mday = 30;
    parts.tm_hour = 13;
    parts.tm_min = 12;
    parts.tm_sec = 45;
    DateTime dt1(parts);
    DateTime dt2(parts);
    assert(dt1 - dt2 == dt2 - dt1);
    assert(dt1 - dt2 == 0);
}

// I will be leveraging that operator+ is already tested
// before this function. Therefore, I will use it to 
// implement these tests
void test_subtract_one_second_positive() {
    DateTime dt1;
    DateTime dt2;
    dt2 = dt2 + 1;
    assert(dt2 - dt1 == 1);
}

void test_subtract_one_second_negative() {
    DateTime dt1;
    DateTime dt2;
    dt2 = dt2 + 1;
    assert(dt1 - dt2 == -1);
}

void test_subtract_one_minute_positive() {
    DateTime dt1;
    DateTime dt2;
    dt2 = dt2 + 60;
    assert(dt2 - dt1 == 60);
}

void test_subtract_one_minute_negative() {
    DateTime dt1;
    DateTime dt2;
    dt2 = dt2 + 60;
    assert(dt1 - dt2 == -60);
}

// at this point let's assume I test all the other timespans

int main() {
    std::cout << "Testing DateTime::operator-(const DateTime&) const" << std::endl;
    test_subtract_no_difference();
    test_subtract_no_difference_not_default();
    test_subtract_one_second_positive();
    test_subtract_one_second_negative();
    test_subtract_one_minute_positive();
    test_subtract_one_minute_negative();
    std::cout << "Tests passed for DateTime::operator-(const DateTime&) const" << std::endl << std::endl;
}