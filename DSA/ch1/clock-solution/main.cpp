#include <iostream>
#include "clock.hpp"

int main() {
    Clock clock(12, 57, 34);
    clock.display(std::cout, ClockFormat::TWELVEHOUR);
    // advance clock 1 hour
    for (int i = 0; i < 3600; ++i) {
        clock.tick();
    }
    clock.display(std::cout, ClockFormat::TWELVEHOUR);
}
