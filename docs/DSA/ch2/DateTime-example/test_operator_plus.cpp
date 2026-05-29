#include "DateTime.hpp"
#include <cassert>
#include <iostream>

void test_add_zero_to_epoch() {
    DateTime dt1;
    DateTime dt2 = dt1 + 0;
    assert(dt1 == dt2);
}

void test_add_zero_to_now() {
    DateTime dt1 = DateTime::now();
    DateTime dt2 = dt1 + 0;
    assert(dt1 == dt2);
}

void test_add_one_second_to_epoch() {
    TimeParts refParts = {};
    refParts.tm_year = 1970 - 1900;
    refParts.tm_mon = 0;
    refParts.tm_mday = 1;
    refParts.tm_hour = 0;
    refParts.tm_min = 0;
    refParts.tm_sec = 1;
    DateTime refDT(refParts);
    DateTime testDT;
    testDT = testDT + 1;
    assert(testDT == refDT);
}

void test_add_one_minute_to_epoch() {
    TimeParts refParts = {};
    refParts.tm_year = 1970 - 1900;
    refParts.tm_mon = 0;
    refParts.tm_mday = 1;
    refParts.tm_hour = 0;
    refParts.tm_min = 1;
    refParts.tm_sec = 0;
    DateTime refDT(refParts);
    DateTime testDT;
    testDT = testDT + 60;
    assert(testDT == refDT);
}

void test_add_one_hour_to_epoch() {
    TimeParts refParts = {};
    refParts.tm_year = 1970 - 1900;
    refParts.tm_mon = 0;
    refParts.tm_mday = 1;
    refParts.tm_hour = 1;
    refParts.tm_min = 0;
    refParts.tm_sec = 0;
    DateTime refDT(refParts);
    DateTime testDT;
    testDT = testDT + (60 * 60);
    assert(testDT == refDT);
}

void test_add_one_day_to_epoch() {
    TimeParts refParts = {};
    refParts.tm_year = 1970 - 1900;
    refParts.tm_mon = 0;
    refParts.tm_mday = 2;
    refParts.tm_hour = 0;
    refParts.tm_min = 0;
    refParts.tm_sec = 0;
    DateTime refDT(refParts);
    DateTime testDT;
    testDT = testDT + (60 * 60 * 24);
    assert(testDT == refDT);
}

void test_add_seconds_to_epoch_to_move_from_jan1_to_feb1() {
    TimeParts refParts = {};
    refParts.tm_year = 1970 - 1900;
    refParts.tm_mon = 1;
    refParts.tm_mday = 1;
    refParts.tm_hour = 0;
    refParts.tm_min = 0;
    refParts.tm_sec = 0;
    DateTime refDT(refParts);
    DateTime testDT;
    testDT = testDT + (60 * 60 * 24 * 31);
    assert(testDT == refDT);
}

void test_add_seconds_to_epoch_to_move_from_1970_to_1971() {
    TimeParts refParts = {};
    refParts.tm_year = 1971 - 1900;
    refParts.tm_mon = 0;
    refParts.tm_mday = 1;
    refParts.tm_hour = 0;
    refParts.tm_min = 0;
    refParts.tm_sec = 0;
    DateTime refDT(refParts);
    DateTime testDT;
    // 1970 was not a leap year so use 365 for number of days
    testDT = testDT + (60 * 60 * 24 * 365);
    assert(testDT == refDT);
}

void test_add_negative_second_to_epoch() {
    DateTime refDT;
    TimeParts testParts = {};
    testParts.tm_year = 1970 - 1900;
    testParts.tm_mon = 0;
    testParts.tm_mday = 1;
    testParts.tm_hour = 0;
    testParts.tm_min = 0;
    testParts.tm_sec = 1;
    DateTime testDT(testParts);
    testDT = testDT + -1;
    assert(testDT == refDT);
}

void test_add_negative_minute_to_epoch() {
    DateTime refDT;
    TimeParts testParts = {};
    testParts.tm_year = 1970 - 1900;
    testParts.tm_mon = 0;
    testParts.tm_mday = 1;
    testParts.tm_hour = 0;
    testParts.tm_min = 1;
    testParts.tm_sec = 0;
    DateTime testDT(testParts);
    testDT = testDT + -60;
    assert(testDT == refDT);
}

void test_add_negative_hour_to_epoch() {
    DateTime refDT;
    TimeParts testParts = {};
    testParts.tm_year = 1970 - 1900;
    testParts.tm_mon = 0;
    testParts.tm_mday = 1;
    testParts.tm_hour = 1;
    testParts.tm_min = 0;
    testParts.tm_sec = 0;
    DateTime testDT(testParts);
    testDT = testDT + -3600;
    assert(testDT == refDT);
}

void test_add_negative_day_to_epoch() {
    DateTime refDT;
    TimeParts testParts = {};
    testParts.tm_year = 1970 - 1900;
    testParts.tm_mon = 0;
    testParts.tm_mday = 2;
    testParts.tm_hour = 0;
    testParts.tm_min = 0;
    testParts.tm_sec = 0;
    DateTime testDT(testParts);
    testDT = testDT + -86400;
    assert(testDT == refDT);
}

void test_add_negative_seconds_to_go_from_feb1_to_jan1() {
    DateTime refDT;
    TimeParts testParts = {};
    testParts.tm_year = 1970 - 1900;
    testParts.tm_mon = 1;
    testParts.tm_mday = 1;
    testParts.tm_hour = 0;
    testParts.tm_min = 0;
    testParts.tm_sec = 0;
    DateTime testDT(testParts);
    testDT = testDT + -(86400 * 31);
    assert(testDT == refDT);
}

void test_add_negative_seconds_to_go_from_1971_to_1970() {
    DateTime refDT;
    TimeParts testParts = {};
    testParts.tm_year = 1971 - 1900;
    testParts.tm_mon = 0;
    testParts.tm_mday = 1;
    testParts.tm_hour = 0;
    testParts.tm_min = 0;
    testParts.tm_sec = 0;
    DateTime testDT(testParts);
    testDT = testDT + -(86400 * 365);
    assert(testDT == refDT);
}

int main() {
    std::cout << "Testing DateTime::operator+(time_t) const" << std::endl;
    test_add_zero_to_epoch();
    test_add_zero_to_now();
    test_add_one_second_to_epoch();
    test_add_one_minute_to_epoch();
    test_add_one_hour_to_epoch();
    test_add_one_day_to_epoch();
    test_add_seconds_to_epoch_to_move_from_jan1_to_feb1();
    test_add_seconds_to_epoch_to_move_from_1970_to_1971();
    test_add_negative_second_to_epoch();
    test_add_negative_minute_to_epoch();
    test_add_negative_hour_to_epoch();
    test_add_negative_day_to_epoch();
    test_add_negative_seconds_to_go_from_feb1_to_jan1();
    test_add_negative_seconds_to_go_from_1971_to_1970();
    std::cout << "Tests passed for DateTime::operator+(time_t) const" << std::endl << std::endl;
    return 0;
}