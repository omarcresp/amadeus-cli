#include "amadeus/data_handlers/XmlDataHandler.hpp"

#include <iostream>

namespace amadeus {

XmlDataHandler::XmlDataHandler(const std::string& filePath) {
    std::cout << "XML handler constructed with file: " << filePath
              << " - pending to implement loading." << std::endl;
    // TODO: Load employees from XML file
}

XmlDataHandler::~XmlDataHandler() {}

bool XmlDataHandler::sortWrite(const std::string& outputPath) {
    std::cout << "XML handler - sortWrite: pending to implement" << std::endl;
    std::cout << "Output path: " << outputPath << std::endl;
    return true;
}

void XmlDataHandler::printMax() {
    std::cout << "XML handler - printMax: pending to implement" << std::endl;
}

void XmlDataHandler::printAvg() {
    std::cout << "XML handler - printAvg: pending to implement" << std::endl;
}

const std::vector<Employee>& XmlDataHandler::getEmployees() const {
    std::cout << "XML handler - getEmployees: pending to implement" << std::endl;
    return m_employees;
}

}  // namespace amadeus