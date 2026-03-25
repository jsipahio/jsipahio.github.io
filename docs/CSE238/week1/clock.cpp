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

Clock::Clock() {
    seconds = 0;
}

Clock::Clock(size_t second) {
    seconds = second % 86400;
}

Clock::Clock(size_t hour, size_t minute, size_t second) {
    size_t hourSeconds = hour * 3600;
    size_t minuteSeconds = minute * 60;
    seconds = (second + minuteSeconds + hourSeconds) % 86400;
}

void Clock::tick() {
    seconds = (seconds + 1) % 86400;
}

void Clock::display(std::ostream& out, ClockFormat format) {
    size_t hours = seconds / 3600;
    size_t minutes = (seconds % 3600) / 60;
    switch (format) {
        case ClockFormat::MILITARY:
            out << hours << ":" << minutes << ":" << seconds % 60 << std::endl;
            break;
        case ClockFormat::TWELVEHOUR:
            if (hours == 0) {
                out << "12:" << minutes << ":" << seconds % 60 << std::endl;
            }
            else if (hours < 13) {
                out << hours << ":" << minutes << ":" << seconds % 60 << std::endl;
            }
            else {
                out << hours - 12 << ":" << minutes << ":" << seconds % 60 << std::endl;
            }
            break;
        default:
            std::cerr << "Invalid format provided. Abort..." << std::endl;
            exit(1);
    }
}

int main() {
    Clock clock(12, 57, 34);
    clock.display(std::cout, ClockFormat::TWELVEHOUR);
    // advance clock 1 hour
    for (int i = 0; i < 3600; ++i) {
        clock.tick();
    }
    clock.display(std::cout, ClockFormat::TWELVEHOUR);
}
