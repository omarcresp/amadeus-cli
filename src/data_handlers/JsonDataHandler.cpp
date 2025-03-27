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

        // Validate structure
        for (const auto& emp : jsonData["employees"]) {
            if (!emp.contains("name") || !emp.contains("id") || !emp.contains("department") ||
                !emp.contains("salary")) {
                return std::unexpected("Error: Invalid employee structure in JSON");
            }
        }

        return std::unique_ptr<DataHandler>(new JsonDataHandler(jsonData));
    } catch (const std::exception& e) {
        return std::unexpected(string("Error creating JsonDataHandler: ") + e.what());
    }
}

JsonDataHandler::JsonDataHandler(const nlohmann::json& jsonData) {
    m_employees = {};
    m_totalSalaries = 0;

    auto employeesList = jsonData["employees"];

    for (const auto& emp : employeesList) {
        Employee employee;

        employee.name = emp["name"].get<string>();
        employee.id = emp["id"].get<int>();
        employee.department = emp["department"].get<string>();
        employee.salary = emp["salary"].get<double>();

        m_employees.push_back(employee);
        m_totalSalaries += employee.salary;

        if (m_employees.size() == 1 || employee.salary > m_highestIncome.salary) {
            m_highestIncome = employee;
        }
    }

    if (!m_employees.size()) {
        throw new std::invalid_argument("Employees list is empty");
    }
}

JsonDataHandler::~JsonDataHandler() {}

std::expected<void, string> JsonDataHandler::sortWrite(const string& outputPath) {
    if (outputPath.empty()) {
        return std::unexpected("Error: outputPath is empty");
    }

    try {
        std::vector<Employee> sortedEmployees = m_employees;
        std::sort(sortedEmployees.begin(), sortedEmployees.end(),
                  [](const Employee& a, const Employee& b) { return a.id < b.id; });

        nlohmann::json outputJson;
        nlohmann::json employeesArray = nlohmann::json::array();

        for (const auto& emp : sortedEmployees) {
            nlohmann::json employee;
            employee["name"] = emp.name;
            employee["id"] = emp.id;
            employee["department"] = emp.department;
            employee["salary"] = emp.salary;

            employeesArray.push_back(employee);
        }

        outputJson["employees"] = employeesArray;

        std::ofstream outputFile(outputPath);
        if (!outputFile.is_open()) {
            return std::unexpected("Failed to open output file: " + outputPath);
        }

        outputFile << outputJson.dump(2);
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
    double avgSalary = m_totalSalaries / m_employees.size();
    std::println("Average salary: {}\n", avgSalary);
}

}  // namespace amadeus
