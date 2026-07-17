#include <iostream>
#include <ctime>
#include "DateTime.hpp"

DateTime::DateTime() {
    seconds = 0;
}

DateTime::DateTime(TimeParts parts) {
    time_t secondsSinceEpoch = timegm(&parts);
    seconds = secondsSinceEpoch;
}

DateTime DateTime::now() {
    // this gets the system time from 
    // the C time.h library
    time_t t = time(0);
    TimeParts parts = *gmtime(&t);
    return DateTime(parts);
}

time_t DateTime::operator-(const DateTime &rhs) const {
    return seconds - rhs.seconds;
}

DateTime DateTime::operator+(time_t rhs) const {
    time_t t = seconds + rhs;
    TimeParts parts = *gmtime(&t);
    return DateTime(parts);
}

bool DateTime::operator==(const DateTime& rhs) const {
    return seconds == rhs.seconds;
}

unsigned int DateTime::second() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_sec;
}

unsigned int DateTime::minute() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_min;
}

unsigned int DateTime::hour() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_hour;
}

unsigned int DateTime::day() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_mday;
}

unsigned int DateTime::month() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_mon;
}

unsigned int DateTime::year() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    // the tm_year is relative to 1900
    // for some reason
    return 1900 + timeParts->tm_year;
}

void DateTime::second(unsigned int s) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_sec = s;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::minute(unsigned int m) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_min = m;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::hour(unsigned int h) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_hour = h;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::day(unsigned int d) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_mday = d;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::month(unsigned int m) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_mon = m;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::year(unsigned int y) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_year = y;
    t = mktime(timeParts);
    seconds = t;
}

std::string DateTime::toString(std::string format) {
    // if someone creates a date format longer than 1024
    // characters, that is their own fault...
    char dateTime[1024];
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    strftime(dateTime, 1023, format.c_str(), timeParts);
    return std::string(dateTime); 
}
