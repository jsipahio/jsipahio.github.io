#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <sys/types.h>
#include <string>

// using better name for tm struct
// defined in the sys/types.h and time.h headers 
typedef tm TimeParts;

/**
* DateTime - object oriented representation of date and time
*/
class DateTime {
public:
    DateTime();
    DateTime(TimeParts parts);
    static DateTime now();
    
    time_t operator-(const DateTime &rhs) const;
    DateTime operator+(time_t rhs) const;
    bool operator==(const DateTime &rhs) const;
    
    unsigned int second() const;
    unsigned int minute() const;
    unsigned int hour() const;
    unsigned int day() const;
    unsigned int month() const;
    unsigned int year() const;

    void second(unsigned int s);
    void minute(unsigned int m);
    void hour(unsigned int h);
    void day(unsigned int d);
    void month(unsigned int m);
    void year(unsigned int y);

    std::string toString(std::string format = "%m/%d/%Y %H:%M:%S");
private:
    time_t seconds;
};

#endif
