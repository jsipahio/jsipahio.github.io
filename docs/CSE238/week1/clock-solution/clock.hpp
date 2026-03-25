#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <iostream>

enum ClockFormat {
    MILITARY,
    TWELVEHOUR
};

class Clock {
public:
    /**
    * Initializes clock to midnight
    */
    Clock();
    /**
    * Initializes clock to seconds from midnight
    * Will rollover if seconds exceed 86399
    * @param second - Number of seconds from midnight
    */
    Clock(size_t second);
    /**
    * Initializes clock to provided time in HH::MM::SS format
    * Will roll over time as needed
    * @param hour - hours from midnight
    * @param minute - minutes after hour
    * @param second - seconds after minute
    */
    Clock(size_t hour, size_t minute, size_t second);
    /**
    * Increments time by one second
    */
    void tick();
    /**
    * Displays time to specified output stream
    * @param out - the output stream to write the time to
    * @param format - the format (MILITARY, TWELVEHOUR) to display the time in
    */
    void display(std::ostream& out, ClockFormat format);
private:
    // 0 microseconds is midnight
    // 86399 is 23:59:59
    size_t seconds;
};

#endif
