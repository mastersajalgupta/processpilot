#include "config_parser.hpp"

#include <fstream>
#include <sstream>

bool ConfigParser::load(const std::string& filename) {

    std::ifstream file(filename);

    if (!file) {
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string key;
        std::string value;

        if (std::getline(ss, key, '=') &&
            std::getline(ss, value)) {

            values[key] = value;
        }
    }

    return true;
}

std::string ConfigParser::get(const std::string& key) {

    if (values.find(key) != values.end()) {
        return values[key];
    }

    return "";
}
