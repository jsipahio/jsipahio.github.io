#include "DateTime.hpp"
#include <cassert>
#include <iostream>

void test_default_format_epoch() {
    DateTime dt;
    std::string dtString = dt.toString();
    assert(dtString == "01/01/1970 00:00:00");
}

void test_default_format_other_time() {
    TimeParts parts = {};
    parts.tm_year = 2025 - 1900;
    parts.tm_mon = 11;
    parts.tm_mday = 19;
    parts.tm_hour = 11;
    parts.tm_min = 2;
    parts.tm_sec = 42;
    DateTime dt(parts);
    std::string dtString = dt.toString();
    assert(dtString == "12/19/2025 11:02:42");
}

void test_am_format() {
    TimeParts parts = {};
    // for this test we don't care about the month, day, or year
    parts.tm_hour = 9;
    parts.tm_min = 34;
    parts.tm_sec = 12;
    DateTime dt(parts);
    std::string dtString = dt.toString("%I:%M:%S %p");
    assert(dtString == "09:34:12 AM");
}

void test_pm_format() {
    TimeParts parts = {};
    // for this test we don't care about the month, day, or year
    parts.tm_hour = 13;
    parts.tm_min = 34;
    parts.tm_sec = 12;
    DateTime dt(parts);
    std::string dtString = dt.toString("%I:%M:%S %p");
    assert(dtString == "01:34:12 PM");
}

void test_day_of_year() {
    TimeParts parts = {};
    // for this test we don't care about the time portion
    parts.tm_year = 100;
    parts.tm_mday = 12;
    parts.tm_mon = 2;
    DateTime dt(parts);
    std::string dtString = dt.toString("%j days of %Y");
    // 31 days in jan
    // 29 days in feb (2000 is a leap year)
    // 12 days so far in march
    // 72 days so far in the year 200
    assert(dtString == "072 days of 2000");
}

void test_iso8601_format() {
    DateTime dt;
    std::string dtString = dt.toString("%FT%T");
    assert(dtString == "1970-01-01T00:00:00");
}

int main() {
    std::cout << "Testing std::string DateTime::toString(std::string format) const" << std::endl;
    test_default_format_epoch();
    test_default_format_other_time();
    test_am_format();
    test_pm_format();
    test_day_of_year();
    test_iso8601_format();
    std::cout << "Tests passed for std::string DateTime::toString(std::string format) const" << std::endl << std::endl;
    return 0;
}