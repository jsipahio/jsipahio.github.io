#include <assert.h>
#include <iostream>
#include <string>
#include <utilities.hpp>
#include <vector>

int main() {
    {
        std::string format = "{0}";
        std::vector<std::string> args = {"test"};
        std::string formatted = formatString(format, args);
        assert(formatted == std::string("test"));
    }
    {
        std::string format = "{0} {1}!";
        std::vector<std::string> args = {"Hello", "World"};
        std::string formatted = formatString(format, args);
        assert(formatted == std::string("Hello World!"));
    }
    std::cout << "All formatString(std::string, const std::vector<std::string>&) tests passed\n";

    return 0;
}