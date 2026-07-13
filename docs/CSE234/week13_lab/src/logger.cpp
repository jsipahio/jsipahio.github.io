#include <logger.hpp>
#include <utilities.hpp>

std::string toString(SeverityLevel level) {
    switch (level) {
        case SeverityLevel::INFO: return "INFORMATION";
        case SeverityLevel::WARNING: return "WARNING";
        case SeverityLevel::ERROR: return "ERROR";
    }
}

Logger::~Logger() {
    if (log.is_open()) log.close();
}

void Logger::close() {
    if (log.is_open()) log.close();
}

void Logger::logMessage(std::string message, SeverityLevel level) {
    log << formatString("{0}: {1}", {toString(level), message}) << "\n";
}
