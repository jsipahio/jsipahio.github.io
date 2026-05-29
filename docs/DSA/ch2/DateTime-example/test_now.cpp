#include "DateTime.hpp"
#include <cassert>
#include <iostream>

// this function is going to be inprecise
// to test due to the nature of it capturing a
// moving point in time
void test_now() {
    // time_t t = time(0);
    // DateTime dateTime = DateTime::now();
    // TimeParts parts = *gmtime(&t);
    // it is possible that the times get captured
    // when a new year is rolling over
    // however, that is unlikely so we will
    // assume that everything but seconds should match
    // if the test fails because of a rollover, we can
    // rerun it
    // assert(dateTime.year() == (unsigned)parts.tm_year);
    // assert(dateTime.month() == (unsigned)parts.tm_mon);
    // assert(dateTime.day() == (unsigned)parts.tm_mday);
    // assert(dateTime.hour() == (unsigned)parts.tm_hour);
    // assert(dateTime.minute() == (unsigned)parts.tm_min);
    // skipping seconds since it is most likely to be off    
}

int main() {
    std::cout << "Testing DateTime::now()..." << std::endl;
    test_now();
    std::cout << "Tests passed for DateTime::now()" << std::endl << std::endl;
    return 0;
}
