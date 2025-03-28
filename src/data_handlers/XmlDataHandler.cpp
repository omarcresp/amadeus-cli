#include "amadeus/data_handlers/XmlDataHandler.hpp"

#include <algorithm>
#include <expected>
#include <memory>
#include <print>
#include <pugixml.hpp>
#include <string>

using std::string;

namespace amadeus {

std::expected<std::unique_ptr<DataHandler>, string> XmlDataHandler::create(const string& filePath) {
    try {
        pugi::xml_document doc;

        if (auto result = doc.load_file(filePath.c_str()); !result) {
            return std::unexpected(string("Error parsing XML file: ") + result.description());
        }

        if (doc.child("employees").empty()) {
            return std::unexpected(string("Error: Missing employees in file: "));
        }

        if (doc.child("employees").first_child().child("salary").empty()) {
            return std::unexpected(string("Error: Missing employe salary in file: "));
        }

        return std::make_unique<XmlDataHandler>(doc);
    } catch (const std::exception& e) {
        return std::unexpected(string("Error creating XmlDataHandler: ") + e.what());
    }
}

XmlDataHandler::XmlDataHandler(const pugi::xml_document& doc) {
    auto employeesList = doc.child("employees");

    size_t employeeCount = std::distance(employeesList.begin(), employeesList.end());

    if (!employeeCount) {
        throw std::invalid_argument("Employees list is empty");
    }

    m_employees.reserve(employeeCount);
    m_totalSalaries = 0;
    m_highestIncome.salary = 0;

    for (pugi::xml_node employee = employeesList.first_child(); employee; employee = employee.next_sibling()) {
        auto name = employee.child("name").child_value();
        auto id = std::stoi(employee.child("id").child_value());
        auto department = employee.child("department").child_value();
        auto salary = std::stod(employee.child("salary").child_value());

        m_employees.emplace_back(name, id, department, salary);
        m_totalSalaries += salary;

        if (salary > m_highestIncome.salary) {
            m_highestIncome = m_employees.back();
        }
    }
}

XmlDataHandler::~XmlDataHandler() = default;

std::expected<void, string> XmlDataHandler::sortWrite(const string& outputPath) {
    if (outputPath.empty()) {
        return std::unexpected("Error: outputPath is empty");
    }

    try {
        std::ranges::sort(m_employees, [](const Employee& a, const Employee& b) { return a.id < b.id; });

        pugi::xml_document doc;

        doc.append_child(pugi::node_declaration).append_attribute("version") = "1.0";

        pugi::xml_node employees = doc.append_child("employees");

        for (const auto& emp : m_employees) {
            pugi::xml_node employee = employees.append_child("employee");

            employee.append_child("name").text().set(emp.name.c_str());
            employee.append_child("id").text().set(emp.id);
            employee.append_child("department").text().set(emp.department.c_str());
            employee.append_child("salary").text().set(emp.salary);
        }

        if (bool saveResult = doc.save_file(outputPath.c_str()); !saveResult) {
            return std::unexpected("Failed to write XML to file: " + outputPath);
        }

        return {};
    } catch (const std::exception& e) {
        return std::unexpected(string("Error in sortWrite: ") + e.what());
    }
}

void XmlDataHandler::printMax() {
    std::println("Higher income employee");
    std::println("ID: {}", m_highestIncome.id);
    std::println("Name: {}", m_highestIncome.name);
    std::println("Department: {}", m_highestIncome.department);
    std::println("Salary: {}\n", m_highestIncome.salary);
}

void XmlDataHandler::printAvg() {
    size_t avgSalary = size_t(m_totalSalaries) / m_employees.size();

    std::println("Average salary: {}\n", avgSalary);
}

}  // namespace amadeus
