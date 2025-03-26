#include "amadeus/data_handlers/XmlDataHandler.hpp"

#include <iostream>

namespace amadeus {

XmlDataHandler::XmlDataHandler(const std::string& filePath) {
    // TODO: Implement loading from the XML file
    (void)filePath;

    m_employees = {Employee{"John Doe", 1, "Engineering", 75000.0}, Employee{"Jane Smith", 2, "HR", 65000.0},
                   Employee{"Bob Wilson", 3, "Marketing", 70000.0}};
    m_totalSalaries = 210000.0;
}

XmlDataHandler::~XmlDataHandler() {}

int XmlDataHandler::sortWrite(const std::string& outputPath) {
    std::cout << "XML handler - sortWrite: pending to implement" << std::endl;
    std::cout << "Output path: " << outputPath << std::endl;

    return true;
}

void XmlDataHandler::printMax() {
    std::cout << "XML handler - printMax: pending to implement" << std::endl;
}

void XmlDataHandler::printAvg() {
    double avgSalary = m_totalSalaries / m_employees.size();

    std::cout << "Average salary: " << avgSalary << std::endl;
}

}  // namespace amadeus
