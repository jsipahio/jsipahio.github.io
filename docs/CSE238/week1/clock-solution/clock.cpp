#include <iostream>
#include "clock.hpp"

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
