#include <assert.h>
#include <iostream>
#include <logger.hpp>
#include <string>

int main() {
    std::string logfile = "log.log";
    std::ofstream log(logfile);
    if (log.fail()) {
        std::cerr << "failed to open log for writing\n";
        exit(1);
    }
    Logger logger(log);
    logger.logMessage("info", SeverityLevel::INFO);
    logger.logMessage("warning", SeverityLevel::WARNING);
    logger.logMessage("error", SeverityLevel::ERROR);
    logger.close();

    std::ifstream fin(logfile);
    if (fin.fail()) {
        std::cerr << "failed to open log for reading\n";
        exit(2);
    }
    std::string line1, line2, line3;
    std::getline(fin, line1);
    assert(line1 == std::string("INFORMATION: info"));
    std::getline(fin, line2);
    assert(line2 == std::string("WARNING: warning"));
    std::getline(fin, line3);
    assert(line3 == std::string("ERROR: error"));
    fin.close();

    std::cout << "All tests for Logger passed\n";

    return 0;
}
