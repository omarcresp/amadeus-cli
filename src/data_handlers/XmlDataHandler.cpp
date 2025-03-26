#include "amadeus/data_handlers/XmlDataHandler.hpp"

#include <iostream>

namespace amadeus {

XmlDataHandler::XmlDataHandler(const std::string& filePath) {
    // TODO: Implement loading from the XML file
    (void)filePath;

    m_employees = {Employee{"John Doe", 1, "Engineering", 75000.0}, Employee{"Jane Smith", 2, "HR", 65000.0},
                   Employee{"Bob Wilson", 3, "Marketing", 70000.0}};
    m_totalSalaries = 210000.0;
    m_highestIncome = m_employees[0];
}

XmlDataHandler::~XmlDataHandler() {}

int XmlDataHandler::sortWrite(const std::string& outputPath) {
    std::cout << "XML handler - sortWrite: pending to implement" << std::endl;
    std::cout << "Output path: " << outputPath << std::endl;

    return true;
}

void XmlDataHandler::printMax() {
    // Assert highestIncome field is defined

    std::cout << "Higher income employe:" << std::endl;
    std::cout << "ID: " << m_highestIncome.id << std::endl;
    std::cout << "Name: " << m_highestIncome.name << std::endl;
    std::cout << "Department: " << m_highestIncome.department << std::endl;
    std::cout << "Salary: " << m_highestIncome.salary << std::endl;
}

void XmlDataHandler::printAvg() {
    double avgSalary = m_totalSalaries / m_employees.size();

    std::cout << "Average salary: " << avgSalary << std::endl;
}

}  // namespace amadeus
