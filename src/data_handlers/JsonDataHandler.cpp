#include "amadeus/data_handlers/JsonDataHandler.hpp"

#include <print>

namespace amadeus {

JsonDataHandler::JsonDataHandler(const std::string& filePath) {
    // TODO: Implement loading from the JSON file
    (void)filePath;

    m_employees = {Employee{"John Doe", 1, "Engineering", 75000.0}, Employee{"Jane Smith", 2, "HR", 65000.0},
                   Employee{"Bob Wilson", 3, "Marketing", 70000.0}};
    m_totalSalaries = 210000.0;
    m_highestIncome = m_employees[0];
}

JsonDataHandler::~JsonDataHandler() {}

int JsonDataHandler::sortWrite(const std::string& outputPath) {
    std::println("\nJSON handler - sortWrite: pending to implement");
    std::print("Output path: {}", outputPath);

    return 0;
}

void JsonDataHandler::printMax() {
    // Assert highestIncome field is defined

    std::println("Higher income employee");
    std::println("ID: {}", m_highestIncome.id);
    std::println("Name: {}", m_highestIncome.name);
    std::println("Department: {}", m_highestIncome.department);
    std::println("Salary: {}", m_highestIncome.salary);
}

void JsonDataHandler::printAvg() {
    double avgSalary = m_totalSalaries / m_employees.size();
    std::println("Average salary: {}\n", avgSalary);
}

}  // namespace amadeus
