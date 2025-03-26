#include "amadeus/data_handlers/JsonDataHandler.hpp"

#include <iostream>

namespace amadeus {

JsonDataHandler::JsonDataHandler(const std::string& filePath) {
    // TODO: Implement loading from the JSON file
    (void)filePath;

    m_employees = {Employee{"John Doe", 1, "Engineering", 75000.0}, Employee{"Jane Smith", 2, "HR", 65000.0},
                   Employee{"Bob Wilson", 3, "Marketing", 70000.0}};
}

JsonDataHandler::~JsonDataHandler() {}

int JsonDataHandler::sortWrite(const std::string& outputPath) {
    std::cout << "JSON handler - sortWrite: pending to implement" << std::endl;
    std::cout << "Output path: " << outputPath << std::endl;

    return 0;
}

int JsonDataHandler::printMax() {
    std::cout << "JSON handler - printMax: pending to implement" << std::endl;

    return 0;
}

int JsonDataHandler::printAvg() {
    std::cout << "JSON handler - printAvg: pending to implement" << std::endl;

    return 0;
}

}  // namespace amadeus
