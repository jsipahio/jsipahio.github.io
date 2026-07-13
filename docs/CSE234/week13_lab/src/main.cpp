#include <logger.hpp>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Must specify log file\n";
        std::cerr << "Usage:\n";
        std::cerr << "./log logfile";
        return 1;
    }

    std::ofstream log(argv[1], std::ios::app);
    if (log.fail()) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 2;
    }

    Logger logger(log);
    while (true) {
        SeverityLevel level;
        short input;
        std::cout << "Enter severity level:\n";
        std::cout << "1. Information\n";
        std::cout << "2. Warning\n";
        std::cout << "3. Error\n";
        std::cout << ">> ";
        std::cin >> input;
        switch (input) {
            case 1: level = SeverityLevel::INFO; break;
            case 2: level = SeverityLevel::WARNING; break;
            case 3: level = SeverityLevel::ERROR; break;
            default: level = SeverityLevel::INFO;
        }

        std::string message;
        std::cout << "Enter log message:\n";
        std::cout << ">> ";
        std::cin >> message;

        logger.logMessage(message, level);

        char ans;
        std::cout << "Add another log message [y/n]?";
        std::cout << ">> ";
        std::cin >> ans;

        if (ans == 'n' || ans == 'N') {
            break;
        }
    }

    logger.close();

    return 0;
}
