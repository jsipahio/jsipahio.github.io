#include <utilities.hpp>
#include <string>
#include <vector>

std::string formatString(std::string format, const std::vector<std::string>& argv) {
    std::size_t start = format.find('{');
    
    std::size_t end = (start != std::string::npos) ? format.find('}', start) : std::string::npos;

    while (start != std::string::npos && end != std::string::npos) {
        std::size_t index = std::stoull(format.substr(start + 1, end - start - 1));

        format.erase(start, end - start + 1);
        format.insert(start, argv.at(index));

        std::size_t next_search_pos = start + argv.at(index).length();

        start = format.find('{', next_search_pos);
        end = (start != std::string::npos) ? format.find('}', start) : std::string::npos;
    }

    return format;
}
