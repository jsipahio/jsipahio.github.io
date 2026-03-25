#include "DateTime.hpp"
#include <cassert>
#include <iostream>

void test_equal_default_ctor() {
    DateTime dt1;
    DateTime dt2;
    assert(dt1 == dt2);
}

void test_equal_same_TimeParts_init() {
    TimeParts timeParts = {};
    timeParts.tm_year = 1970 - 1900;
    timeParts.tm_mon = 0;
    timeParts.tm_mday = 1;
    timeParts.tm_hour = 0;
    timeParts.tm_min = 0;
    timeParts.tm_sec = 0;
    DateTime dt1(timeParts);
    DateTime dt2(timeParts);
    assert(dt1 == dt2);
}

void test_equal_same_time_different_TimeParts_object() {
    TimeParts timeParts1 = {};
    timeParts1.tm_year = 1970 - 1900;
    timeParts1.tm_mon = 0;
    timeParts1.tm_mday = 1;
    timeParts1.tm_hour = 0;
    timeParts1.tm_min = 0;
    timeParts1.tm_sec = 0;
    TimeParts timeParts2 = {};
    timeParts2.tm_year = 1970 - 1900;
    timeParts2.tm_mon = 0;
    timeParts2.tm_mday = 1;
    timeParts2.tm_hour = 0;
    timeParts2.tm_min = 0;
    timeParts2.tm_sec = 0;
    DateTime dt1(timeParts1);
    DateTime dt2(timeParts2);
    assert(dt1 == dt2);
}

void test_same_time_different_values_for_TimeParts_object() {
    TimeParts timeParts1 = {};
    timeParts1.tm_year = 1970 - 1900;
    timeParts1.tm_mon = 0;
    timeParts1.tm_mday = 1;
    timeParts1.tm_hour = 0;
    timeParts1.tm_min = 0;
    timeParts1.tm_sec = 0;
    TimeParts timeParts2 = {};
    timeParts2.tm_year = 1970 - 1900;
    timeParts2.tm_mon = -1;
    timeParts2.tm_mday = 32;
    timeParts2.tm_hour = 0;
    timeParts2.tm_min = 0;
    timeParts2.tm_sec = 0;
    DateTime dt1(timeParts1);
    DateTime dt2(timeParts2);
    assert(dt1 == dt2);
}

void test_not_equal_year() {
    TimeParts timeParts1 = {};
    timeParts1.tm_year = 1970 - 1900;
    timeParts1.tm_mon = 0;
    timeParts1.tm_mday = 1;
    timeParts1.tm_hour = 0;
    timeParts1.tm_min = 0;
    timeParts1.tm_sec = 0;
    TimeParts timeParts2 = {};
    timeParts2.tm_year = 1970;
    timeParts2.tm_mon = 0;
    timeParts2.tm_mday = 1;
    timeParts2.tm_hour = 0;
    timeParts2.tm_min = 0;
    timeParts2.tm_sec = 0;
    DateTime dt1(timeParts1);
    DateTime dt2(timeParts2);
    assert(!(dt1 == dt2));
}

void test_not_equal_month() {
    TimeParts timeParts1 = {};
    timeParts1.tm_year = 1970 - 1900;
    timeParts1.tm_mon = 0;
    timeParts1.tm_mday = 1;
    timeParts1.tm_hour = 0;
    timeParts1.tm_min = 0;
    timeParts1.tm_sec = 0;
    TimeParts timeParts2 = {};
    timeParts2.tm_year = 1970 - 1900;
    timeParts2.tm_mon = 5;
    timeParts2.tm_mday = 1;
    timeParts2.tm_hour = 0;
    timeParts2.tm_min = 0;
    timeParts2.tm_sec = 0;
    DateTime dt1(timeParts1);
    DateTime dt2(timeParts2);
    assert(!(dt1 == dt2));
}

void test_not_equal_day() {
    TimeParts timeParts1 = {};
    timeParts1.tm_year = 1970 - 1900;
    timeParts1.tm_mon = 0;
    timeParts1.tm_mday = 1;
    timeParts1.tm_hour = 0;
    timeParts1.tm_min = 0;
    timeParts1.tm_sec = 0;
    TimeParts timeParts2 = {};
    timeParts2.tm_year = 1970 - 1900;
    timeParts2.tm_mon = 0;
    timeParts2.tm_mday = 24;
    timeParts2.tm_hour = 0;
    timeParts2.tm_min = 0;
    timeParts2.tm_sec = 0;
    DateTime dt1(timeParts1);
    DateTime dt2(timeParts2);
    assert(!(dt1 == dt2));
}

void test_not_equal_hour() {
    TimeParts timeParts1 = {};
    timeParts1.tm_year = 1970 - 1900;
    timeParts1.tm_mon = 0;
    timeParts1.tm_mday = 1;
    timeParts1.tm_hour = 0;
    timeParts1.tm_min = 0;
    timeParts1.tm_sec = 0;
    TimeParts timeParts2 = {};
    timeParts2.tm_year = 1970 - 1900;
    timeParts2.tm_mon = 0;
    timeParts2.tm_mday = 1;
    timeParts2.tm_hour = 12;
    timeParts2.tm_min = 0;
    timeParts2.tm_sec = 0;
    DateTime dt1(timeParts1);
    DateTime dt2(timeParts2);
    assert(!(dt1 == dt2));
}

void test_not_equal_minute() {
    TimeParts timeParts1 = {};
    timeParts1.tm_year = 1970 - 1900;
    timeParts1.tm_mon = 0;
    timeParts1.tm_mday = 1;
    timeParts1.tm_hour = 0;
    timeParts1.tm_min = 0;
    timeParts1.tm_sec = 0;
    TimeParts timeParts2 = {};
    timeParts2.tm_year = 1970 - 1900;
    timeParts2.tm_mon = 0;
    timeParts2.tm_mday = 1;
    timeParts2.tm_hour = 0;
    timeParts2.tm_min = 56;
    timeParts2.tm_sec = 0;
    DateTime dt1(timeParts1);
    DateTime dt2(timeParts2);
    assert(!(dt1 == dt2));
}

void test_not_equal_second() {
    TimeParts timeParts1 = {};
    timeParts1.tm_year = 1970 - 1900;
    timeParts1.tm_mon = 0;
    timeParts1.tm_mday = 1;
    timeParts1.tm_hour = 0;
    timeParts1.tm_min = 0;
    timeParts1.tm_sec = 0;
    TimeParts timeParts2 = {};
    timeParts2.tm_year = 1970 - 1900;
    timeParts2.tm_mon = 0;
    timeParts2.tm_mday = 1;
    timeParts2.tm_hour = 0;
    timeParts2.tm_min = 0;
    timeParts2.tm_sec = 23;
    DateTime dt1(timeParts1);
    DateTime dt2(timeParts2);
    assert(!(dt1 == dt2));
}

int main() {
    std::cout << "Testing bool DateTime::operator==(const DateTime&) const" << std::endl;
    test_equal_default_ctor();
    test_equal_same_TimeParts_init();
    test_equal_same_time_different_TimeParts_object();
    test_same_time_different_values_for_TimeParts_object();
    test_not_equal_year();
    test_not_equal_month();
    test_not_equal_day();
    test_not_equal_hour();
    test_not_equal_minute();
    test_not_equal_second();
    std::cout << "Tests passed for bool DateTime::operator==(const DateTime&) const" << std::endl << std::endl;
    return 0;
}
