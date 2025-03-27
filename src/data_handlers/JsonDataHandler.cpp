#include "amadeus/data_handlers/JsonDataHandler.hpp"

#include <algorithm>
#include <exception>
#include <expected>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <print>
#include <stdexcept>

using std::string;

namespace amadeus {

std::expected<std::unique_ptr<DataHandler>, string> JsonDataHandler::create(const string& filePath) {
    try {
        std::ifstream file(filePath);

        if (!file.is_open()) {
            return std::unexpected("Error: Cannot open file: " + filePath);
        }

        nlohmann::json jsonData = nlohmann::json::parse(file);

        if (!jsonData.contains("employees")) {
            return std::unexpected("Error: Missing employees in file");
        }

        return std::make_unique<JsonDataHandler>(jsonData);
    } catch (const std::exception& e) {
        return std::unexpected(string("Error creating JsonDataHandler: ") + e.what());
    }
}

JsonDataHandler::JsonDataHandler(const nlohmann::json& jsonData) {
    auto employeesList = jsonData["employees"];

    const size_t employeeCount = employeesList.size();

    if (!employeeCount) {
        throw std::invalid_argument("Employees list is empty");
    }

    m_employees.reserve(employeeCount);
    m_totalSalaries = 0;
    m_highestIncome.salary = 0;

    for (const auto& emp : employeesList) {
        m_employees.emplace_back(emp["name"].get<string>(), emp["id"].get<int>(), emp["department"].get<string>(),
                                 emp["salary"].get<double>());

        const auto& employee = m_employees.back();
        m_totalSalaries += employee.salary;

        if (employee.salary > m_highestIncome.salary) {
            m_highestIncome = employee;
        }
    }
}

JsonDataHandler::~JsonDataHandler() = default;

std::expected<void, string> JsonDataHandler::sortWrite(const string& outputPath) {
    if (outputPath.empty()) {
        return std::unexpected("Error: outputPath is empty");
    }

    try {
        std::ranges::sort(m_employees, [](const Employee& a, const Employee& b) { return a.id < b.id; });

        nlohmann::json outputJson;
        nlohmann::json employeesArray = nlohmann::json::array();

        for (const auto& emp : m_employees) {
            nlohmann::json employee;
            employee["name"] = emp.name;
            employee["id"] = emp.id;
            employee["department"] = emp.department;
            employee["salary"] = emp.salary;

            employeesArray.push_back(std::move(employee));
        }

        outputJson["employees"] = std::move(employeesArray);

        const std::string jsonStr = outputJson.dump(2);
        std::ofstream outputFile(outputPath);
        if (!outputFile.is_open()) {
            return std::unexpected("Failed to open output file: " + outputPath);
        }

        outputFile << jsonStr;
        outputFile.close();

        if (outputFile.fail()) {
            return std::unexpected("Failed to write JSON to file: " + outputPath);
        }

        return {};
    } catch (const std::exception& e) {
        return std::unexpected(string("Error in sortWrite: ") + e.what());
    }
}

void JsonDataHandler::printMax() {
    std::println("Higher income employee");
    std::println("ID: {}", m_highestIncome.id);
    std::println("Name: {}", m_highestIncome.name);
    std::println("Department: {}", m_highestIncome.department);
    std::println("Salary: {}\n", m_highestIncome.salary);
}

void JsonDataHandler::printAvg() {
    size_t avgSalary = size_t(m_totalSalaries) / m_employees.size();

    std::println("Average salary: {}\n", avgSalary);
}

}  // namespace amadeus
