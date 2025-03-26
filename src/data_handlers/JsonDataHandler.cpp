#include "amadeus/data_handlers/JsonDataHandler.hpp"

#include <iostream>

namespace amadeus {

JsonDataHandler::JsonDataHandler(const std::string& filePath) {
    std::cout << "JSON handler constructed with file: " << filePath
              << " - pending to implement loading." << std::endl;
    // TODO: Load employees from JSON file
}

JsonDataHandler::~JsonDataHandler() {}

bool JsonDataHandler::sortWrite(const std::string& outputPath) {
    std::cout << "JSON handler - sortWrite: pending to implement" << std::endl;
    std::cout << "Output path: " << outputPath << std::endl;
    return true;
}

void JsonDataHandler::printMax() {
    std::cout << "JSON handler - printMax: pending to implement" << std::endl;
}

void JsonDataHandler::printAvg() {
    std::cout << "JSON handler - printAvg: pending to implement" << std::endl;
}

const std::vector<Employee>& JsonDataHandler::getEmployees() const {
    std::cout << "JSON handler - getEmployees: pending to implement" << std::endl;
    return m_employees;
}

}  // namespace amadeus