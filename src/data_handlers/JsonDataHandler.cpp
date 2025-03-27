#include "amadeus/data_handlers/JsonDataHandler.hpp"

#include <expected>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <print>

namespace amadeus {

std::expected<std::unique_ptr<DataHandler>, std::string> JsonDataHandler::create(const std::string& filePath) {
    try {
        std::ifstream file(filePath);

        if (!file.is_open()) {
            return std::unexpected("Error: Cannot open file: " + filePath);
        }

        nlohmann::json jsonData = nlohmann::json::parse(file);

        return std::unique_ptr<DataHandler>(new JsonDataHandler(jsonData));
    } catch (const std::exception& e) {
        return std::unexpected(std::string("Error creating JsonDataHandler: ") + e.what());
    }
}

JsonDataHandler::JsonDataHandler(const nlohmann::json& jsonData) {
    (void)jsonData;  // Silence unused variable warning

    // Keep the existing mock data for now
    m_employees = {Employee{"John Doe", 1, "Engineering", 75000.0}, Employee{"Jane Smith", 2, "HR", 65000.0},
                   Employee{"Bob Wilson", 3, "Marketing", 70000.0}};
    m_totalSalaries = 210000.0;
    m_highestIncome = m_employees[0];
}

JsonDataHandler::~JsonDataHandler() {}

std::expected<void, std::string> JsonDataHandler::sortWrite(const std::string& outputPath) {
    if (outputPath.empty()) {
        return std::unexpected("Error: outputPath is empty");
    }

    std::println("\nJSON handler - sortWrite: pending to implement");
    std::print("Output path: {}", outputPath);

    return {};
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
