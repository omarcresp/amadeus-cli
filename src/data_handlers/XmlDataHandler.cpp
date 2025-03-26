#include "amadeus/data_handlers/XmlDataHandler.hpp"

#include <iostream>

namespace amadeus {

XmlDataHandler::XmlDataHandler(const std::string& filePath) {
    // TODO: Implement loading from the XML file
    (void)filePath;

    m_employees = {Employee{"John Doe", 1, "Engineering", 75000.0}, Employee{"Jane Smith", 2, "HR", 65000.0},
                   Employee{"Bob Wilson", 3, "Marketing", 70000.0}};
}

XmlDataHandler::~XmlDataHandler() {}

int XmlDataHandler::sortWrite(const std::string& outputPath) {
    std::cout << "XML handler - sortWrite: pending to implement" << std::endl;
    std::cout << "Output path: " << outputPath << std::endl;

    return true;
}

int XmlDataHandler::printMax() {
    std::cout << "XML handler - printMax: pending to implement" << std::endl;

    return 0;
}

int XmlDataHandler::printAvg() {
    std::cout << "XML handler - printAvg: pending to implement" << std::endl;

    return 0;
}

}  // namespace amadeus
