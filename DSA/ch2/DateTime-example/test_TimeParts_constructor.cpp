#include "DateTime.hpp"
#include <cassert>
#include <iostream>

void test_TimeParts_constructor_unix_epoch() {
    // init all fields to 0
    TimeParts timeParts = {};
    // remember that tm_year is relative to 1900
    timeParts.tm_year = 1970 - 1900;
    // 0 is January
    timeParts.tm_mon = 0;
    // but 1 is the first of the month
    timeParts.tm_mday = 1;
    // all parts of the time are 0 for the unix epoch
    timeParts.tm_hour = 0;
    timeParts.tm_min = 0;
    timeParts.tm_sec = 0;
    DateTime dateTime(timeParts);
    assert(dateTime.year() == 1970);
    assert(dateTime.month() == 0);
    assert(dateTime.day() == 1);
    assert(dateTime.hour() == 0);
    assert(dateTime.minute() == 0);
    assert(dateTime.second() == 0);
}

void test_TimeParts_all_zero() {
    // init all fields to 0
    TimeParts timeParts = {};
    // remember that tm_year is relative to 1900
    timeParts.tm_year = 0 - 1900;
    // 0 is January
    timeParts.tm_mon = 0;
    // 1 is the first of the month
    // 0 would roll over, so using 1
    timeParts.tm_mday = 1;
    // all parts of the time are 0 for the unix epoch
    timeParts.tm_hour = 0;
    timeParts.tm_min = 0;
    timeParts.tm_sec = 0;
    DateTime dateTime(timeParts);
    assert(dateTime.year() == 0);
    assert(dateTime.month() == 0);
    assert(dateTime.day() == 1);
    assert(dateTime.hour() == 0);
    assert(dateTime.minute() == 0);
    assert(dateTime.second() == 0);
}

void test_TimeParts_Seinfeld_Finale() {
    TimeParts timeParts = {};
    timeParts.tm_year = 1998 - 1900;
    timeParts.tm_mon = 4;
    timeParts.tm_mday = 14;
    timeParts.tm_hour = 21;
    timeParts.tm_min = 0;
    timeParts.tm_sec = 0;
    DateTime dateTime(timeParts);
    assert(dateTime.year() == 1998);
    assert(dateTime.month() == 4);
    assert(dateTime.day() == 14);
    assert(dateTime.hour() == 21);
    assert(dateTime.minute() == 0);
    assert(dateTime.second() == 0);
}

// the TimeParts struct should automatically
// roll over overflowing times
void test_TimeParts_overflow() {
    TimeParts timeParts = {};
    // aka 1900
    timeParts.tm_year = 0;
    // this advances to Jan 1901
    timeParts.tm_mon = 12;
    // this advances to Feb 1, 1901
    timeParts.tm_mday = 32;
    // this advances to Feb 2, 1901, 00:00:00
    timeParts.tm_hour = 24;
    // this advances to Feb 2, 1901, 01:00:00
    timeParts.tm_min = 60;
    // this advances to Feb 2, 1901, 01:01:00
    timeParts.tm_sec = 60;
    DateTime dateTime(timeParts);
    assert(dateTime.year() == 1901);
    assert(dateTime.month() == 1);
    assert(dateTime.day() == 2);
    assert(dateTime.hour() == 1);
    assert(dateTime.minute() == 1);
    assert(dateTime.second() == 0);
}

// the TimeParts struct should also handle underflow
void test_TimeParts_underflow() {
    TimeParts timeParts = {};
    // start at 1900
    timeParts.tm_year = 0;
    // now should be Dec, 1899
    timeParts.tm_mon = -1;
    // now should be Nov 30, 1899
    timeParts.tm_mday = 0;
    // now should be Nov 29, 1899, 23:59:59 
    timeParts.tm_hour = -1;
    // now should be Nov 29, 1899, 22:59:59
    timeParts.tm_min = -1;
    // now should be Nov 29, 1899, 22:58:59
    timeParts.tm_sec = -1;
    DateTime dateTime(timeParts);
    assert(dateTime.year() == 1899);
    assert(dateTime.month() == 10);
    assert(dateTime.day() == 29);
    assert(dateTime.hour() == 22);
    assert(dateTime.minute() == 58);
    assert(dateTime.second() == 59);
}

int main() {
    std::cout << "Testing DateTime::DateTime(TimeParts)..." << std::endl;
    test_TimeParts_constructor_unix_epoch();
    test_TimeParts_all_zero();
    test_TimeParts_Seinfeld_Finale();
    test_TimeParts_overflow();
    test_TimeParts_underflow();
    std::cout << "Tests passed for DateTime::DateTime(TimeParts)" << std::endl << std::endl;
    return 0;
}
