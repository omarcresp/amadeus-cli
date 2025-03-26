#include "amadeus/data_handlers/XmlDataHandler.hpp"

#include <expected>
#include <print>

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

std::expected<void, std::string> XmlDataHandler::sortWrite(const std::string& outputPath) {
    if (outputPath.empty()) {
        return std::unexpected("Error: outputPath is empty");
    }

    std::println("\nXML handler - sortWrite: pending to implement");
    std::print("Output path: {}", outputPath);

    return {};
}

void XmlDataHandler::printMax() {
    // Assert highestIncome field is defined

    std::println("Higher income employee");
    std::println("ID: {}", m_highestIncome.id);
    std::println("Name: {}", m_highestIncome.name);
    std::println("Department: {}", m_highestIncome.department);
    std::println("Salary: {}", m_highestIncome.salary);
}

void XmlDataHandler::printAvg() {
    double avgSalary = m_totalSalaries / m_employees.size();
    std::println("Average salary: {}\n", avgSalary);
}

}  // namespace amadeus
