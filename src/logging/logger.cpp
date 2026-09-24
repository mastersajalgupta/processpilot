#include "logger.hpp"

#include <fstream>
#include <ctime>

void Logger::log(const std::string& message) {

    std::ofstream file("processpilot.log", std::ios::app);

    if (!file) {
        return;
    }

    std::time_t now = std::time(nullptr);

    file << std::ctime(&now);
    file << message << "\n";
}
