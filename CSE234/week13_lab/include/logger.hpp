#ifndef INCLUDED_LOGGER_HPP
#define INCLUDED_LOGGER_HPP

#include <fstream>
#include <string>

enum class SeverityLevel {
    INFO,
    WARNING,
    ERROR
};

std::string toString(SeverityLevel level);

class Logger {
public:
    Logger() = delete;
    ~Logger();
    Logger(std::ofstream &logStream): log(logStream) {}
    void logMessage(std::string message, SeverityLevel level = SeverityLevel::INFO);
    void close();
private:
    std::ofstream& log;
};

#endif 